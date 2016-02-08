#include "objects/mapcommlineobject.h"
#include "maphelper.h"
#include "mapview.h"
#include "maplayer.h"

#include "gis.h"

#include <qmath.h>
#include <QDebug>

Map2::MapCommlineObject::MapCommlineObject(const Map2::Coord &from, const Map2::Coord &to, Map2::MapLayer *layer) :
	MapObject(MapObject::MO_Commline, layer),
	mFrom(from),
	mTo(to),
	mColor(Qt::blue),
	mArrowStyle(AS_BothArrows),
	mLineWidth(1),
	hFromHandle(0),
	hToHandle(0)
{
	redraw();
}

Map2::MapCommlineObject::~MapCommlineObject()
{
}

void Map2::MapCommlineObject::setArrowStyle(const ArrowStyle &arrowStyle)
{
	mArrowStyle = arrowStyle;
	redraw();
}

void Map2::MapCommlineObject::setLineWidth(double value)
{
	mLineWidth = value;
	redraw();
}

void Map2::MapCommlineObject::setTo(const Map2::Coord &to)
{
	mTo = to;
	redraw();
}

void Map2::MapCommlineObject::setFrom(const Map2::Coord &from)
{
	mFrom = from;
	redraw();
}

void Map2::MapCommlineObject::setColor(const QColor &color)
{
	mColor = color;
	redraw();
}

void Map2::MapCommlineObject::clearArrows()
{
	if(hFromHandle > 0)
	{
		mapDeleteObject(hFromHandle);
		mapClearObject(hFromHandle);
		hFromHandle = 0;
	}

	if(hToHandle > 0)
	{
		mapDeleteObject(hToHandle);
		mapClearObject(hToHandle);
		hToHandle = 0;
	}
}

void Map2::MapCommlineObject::redraw()
{
	if(!mapLayer())
	{
		return;
	}

	Map2::MapHelper *helper = mapLayer()->mapView()->helper();

	mapClearDraw( handle() );
	clearArrows();

	qDebug()<<mapPointCount(handle(), 0);
	for(int i = 0 ; i < mapPointCount(handle(), 0); ++i)
	{
		mapDeletePointPlane(handle(), i+1);
	}
	qDebug()<<mapPointCount(handle(), 0);

	IMGLINE parmLine;
	memset(&parmLine, 0x0, sizeof(IMGLINE));
	parmLine.Thick = (ulong)helper->px2mkm( mLineWidth );
	parmLine.Color = RGB(mColor.red(), mColor.green(), mColor.blue());

	mapAppendDraw(handle(), IMG_LINE, (char*)&parmLine);

	CoordPlane from = helper->geoToPlane( mFrom );
	CoordPlane to = helper->geoToPlane(mTo);

	QList<CoordPlane> arcCoords = drawArcs();

	foreach(const CoordPlane &coord, arcCoords)
	{
		mapAppendPointPlane(handle(), coord.x, coord.y);
	}

	if(mArrowStyle == AS_StartArrow || mArrowStyle == AS_BothArrows)
	{
		double azimuth = helper->bearing(arcCoords[0], arcCoords[1]);
		hFromHandle = addArrow(from, -azimuth - 180);
	}

	if(mArrowStyle == AS_EndArrow || mArrowStyle == AS_BothArrows)
	{
		int count = arcCoords.count();
		double azimuth = helper->bearing(arcCoords[count-2], arcCoords[count-1]);
		hToHandle = addArrow(to, -azimuth );
	}

	commit();
}

QList<Map2::CoordPlane> Map2::MapCommlineObject::drawArcs()
{
	Q_ASSERT( mapLayer() );
	Map2::MapHelper *helper = mapLayer()->mapView()->helper();

	QPointF from = helper->geoToPicture(mFrom);
	QPointF to = helper->geoToPicture(mTo);

	QLineF line(from, to);

	qreal l = line.length();
	qreal angle = line.angle();
	line.setAngle(0);
	qreal radius = 3 * l;

	QPointF p1(from.x(), from.y() + l / 20.);
	QPointF p2(from.x() + l, from.y() - l / 20. );

	QPolygonF polygon1 = drawArc(line.p1(), p2, radius);

	QPolygonF polygon2 = drawArc(p1, line.p2(), radius);

	QPolygonF polygon;

	foreach(const QPointF &p, polygon1)
	{
		if(p.x() < line.p1().x() + l * 2. / 3.)
		{
			polygon << p;
		}
	}

	foreach(const QPointF &p, polygon2)
	{
		if(p.x() > line.p1().x() + l / 3.)
		{
			polygon << p;
		}
	}

	QTransform transform = QTransform().translate(line.p1().x(), line.p1().y()).rotate(-angle).translate(-line.p1().x(), -line.p1().y());
	polygon = transform.map(polygon);

	QList<CoordPlane> result;
	foreach(const QPointF &p, polygon)
	{
		result << helper->pictureToPlane(p.toPoint());
	}

	return result;
}

QPolygonF Map2::MapCommlineObject::drawArc(QPointF from, QPointF to, qreal radius)
{
	QLineF line(from, to);

	QPointF center = line.pointAt(0.5);

	qreal length = qSqrt(qPow(radius, 2) - qPow(line.length()/2.0, 2));

	QLineF radialLine(center, from);
	radialLine.setLength(length);
	radialLine.setAngle( line.normalVector().angle() - 180);

	center = radialLine.p2();

	qDebug()<< QLineF(center, from).angle()<<QLineF(center, to).angle();

	qreal angleTo = QLineF(center, to).angle();

	radialLine.setPoints(center, from);

	QPolygonF result;
	while(radialLine.angle() > angleTo)
	{
		qDebug()<<"Adding point for angle"<<radialLine.angle();
		result << radialLine.p2();
		radialLine.setAngle( radialLine.angle() - 1);
	}
	result << to;
	return result;
}

HMAP Map2::MapCommlineObject::addArrow(Map2::CoordPlane pointCoord, double azimuth) const
{
	Q_ASSERT( mapLayer() );

	Map2::MapHelper *helper = mapLayer()->mapView()->helper();

	QPointF fromPicture = helper->geoToPicture( mFrom );
	QPointF toPicture = helper->geoToPicture( mTo );

	qreal lengthPx = QLineF(fromPicture, toPicture).length();
	qreal arrowLength = lengthPx / 20.;

	/// Сначала рисуется стрелка смотрящая на 0 (т.е. прямо вверх).

	QPointF arrowPoint= helper->planeToPicture(pointCoord);

	QPointF arrowLeftPoint;
	arrowLeftPoint.setY( arrowPoint.y() + arrowLength );
	arrowLeftPoint.setX(arrowPoint.x() - qTan(helper->degreeToRad(10))*arrowLength );

	QPointF arrowRightPoint;
	arrowRightPoint.setY( arrowPoint.y() + arrowLength );
	arrowRightPoint.setX(arrowPoint.x() + qTan(helper->degreeToRad(10))*arrowLength );

	HMAP hmap = mapCreateSiteObject(mapLayer()->mapHandle(), mapLayer()->siteHandle());

	IMGSQUARE parmLine;
	memset(&parmLine, 0x0, sizeof(IMGSQUARE));
	parmLine.Color = RGB(mColor.red(), mColor.green(), mColor.blue());

	mapAppendDraw(hmap, IMG_SQUARE, (char*)&parmLine);

	QList<CoordPlane> result;
	result << helper->pictureToPlane( arrowPoint.toPoint() );
	result << helper->pictureToPlane( arrowLeftPoint.toPoint() );
	result << helper->pictureToPlane( arrowRightPoint.toPoint() );
	result << result.first(); /// Замкнуть

	foreach(const CoordPlane &coord, result)
	{
		mapAppendPointPlane(hmap, coord.x, coord.y);
	}

	DOUBLEPOINT rotatePoint;
	rotatePoint.x = result.first().x;
	rotatePoint.y = result.first().y;

	double azimuthRad = helper->degreeToRad(azimuth);

	mapRotateObject(hmap, &rotatePoint, &azimuthRad);

	mapCommitObject(hmap);

	return hmap;
}
