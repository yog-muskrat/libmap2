#include "objects/mapcommlineobject.h"
#include "maphelper.h"
#include "mapview.h"
#include "maplayer.h"
#include "rscviewer.h"

#include "gis.h"

#include <QDebug>
#include <qmath.h>
#include <QTextCodec>

using namespace Map2;

Map2::MapCommlineObject::MapCommlineObject(const Map2::Coord &from, const Map2::Coord &to, Map2::MapLayer *layer) :
	MapObject(MapObject::MO_Commline, layer),
	mFrom(from),
	mTo(to),
	mColor(Qt::blue),
	mArrowStyle(AS_BothArrows),
	mLineWidth(3),
	hBody(0),
	hToHandle(0),
	hFromHandle(0)
{
	if(pLayer)
	{
		refresh();
	}
}

Map2::MapCommlineObject::~MapCommlineObject()
{
	clearHandles();
}

void Map2::MapCommlineObject::setArrowStyle(const ArrowStyle &arrowStyle)
{
	mArrowStyle = arrowStyle;
	refresh();
}

void Map2::MapCommlineObject::setLineWidth(double value)
{
	mLineWidth = value;
	refresh();
}

void MapCommlineObject::addAssignment(const MapCommlineObject::Assignment &a)
{
	int index = mAssignments.count();

	mAssignments[a] = addAssignmentObject(a, index);
	refresh();
}

void MapCommlineObject::removeAssignment(int index)
{
	if(index < 0 || index >= mAssignments.count())
	{
		return;
	}

	mAssignments.remove( mAssignments.keys().at(index) );
	refresh();
}

void MapCommlineObject::clearAssignments()
{
	mAssignments.clear();
	refresh();
}

void Map2::MapCommlineObject::setTo(const Map2::Coord &to)
{
	mTo = to;
	refresh();
}

void Map2::MapCommlineObject::setFrom(const Map2::Coord &from)
{
	mFrom = from;
	refresh();
}

void Map2::MapCommlineObject::setColor(const QColor &color)
{
	mColor = color;
	refresh();
}

void Map2::MapCommlineObject::repaint()
{
	if(!mapLayer())
	{
		return;
	}

	removeFromMap();

	hBody = mapCreateSiteObject(mapLayer()->mapHandle(), mapLayer()->siteHandle());

	IMGLINE parmLine;
	memset(&parmLine, 0x0, sizeof(IMGLINE));
	parmLine.Thick = (ulong)helper()->px2mkm( mLineWidth );
	parmLine.Color = RGB(mColor.red(), mColor.green(), mColor.blue());

	mapAppendDraw(hBody, IMG_LINE, (char*)&parmLine);

	CoordPlane from = helper()->geoToPlane( mFrom );
	CoordPlane to = helper()->geoToPlane(mTo);

	QPolygonF arcCoords = drawArcs();

	if(mArrowStyle == AS_StartArrow || mArrowStyle == AS_BothArrows)
	{
		QLineF line(arcCoords[1], arcCoords[0]);
		double angle = line.angle();
		hFromHandle = addArrow(from, angle-90);

		line.setLength( line.length() - mLineWidth);
		arcCoords.replace(0, line.p2());
	}

	if(mArrowStyle == AS_EndArrow || mArrowStyle == AS_BothArrows)
	{
		int count = arcCoords.count();
		QLineF line(arcCoords[count-2], arcCoords[count-1]);

		double angle = line.angle();
		hToHandle = addArrow(to, angle -90);

		line.setLength( line.length() - mLineWidth);
		arcCoords.replace(count-1, line.p2());
	}

	mArcCoords = arcCoords;

	foreach(const QPointF &coord, arcCoords)
	{
		CoordPlane p = helper()->pictureToPlane(coord.toPoint());

		mapAppendPointPlane(hBody, p.x, p.y);
	}

	updateAssignmentObjects();

	commit();
}

QPolygonF Map2::MapCommlineObject::drawArcs()
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

	QPolygonF section1;

	QPolygonF section2;

	QPolygonF section3;

	foreach(const QPointF &p, drawArc(line.p1(), p2, radius))
	{
		if(p.x() < line.p1().x() + l * 2. / 3.)
		{
			section1 << p;
		}
	}

	foreach(const QPointF &p, drawArc(p1, line.p2(), radius))
	{
		if(p.x() > line.p1().x() + l / 3.)
		{
			section3 << p;
		}
	}

	foreach(const QPointF &p, drawArc(section3.first(), section1.last(), radius))
	{
		section3.prepend(p);
	}

	QPolygonF polygon = section1 + section2 + section3;

	QTransform transform = QTransform().translate(line.p1().x(), line.p1().y()).rotate(-angle).translate(-line.p1().x(), -line.p1().y());
	polygon = transform.map(polygon);

	return polygon;
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


	qreal angleTo = QLineF(center, to).angle();

	radialLine.setPoints(center, from);

	QPolygonF result;
	while(radialLine.angle() > angleTo)
	{
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

	HMAP hobj = mapCreateSiteObject(mapLayer()->mapHandle(), mapLayer()->siteHandle());

	IMGSQUARE parmLine;
	memset(&parmLine, 0x0, sizeof(IMGSQUARE));
	parmLine.Color = RGB(mColor.red(), mColor.green(), mColor.blue());

	mapAppendDraw(hobj, IMG_SQUARE, (char*)&parmLine);

	QList<CoordPlane> result;
	result << helper->pictureToPlane( arrowPoint.toPoint() );
	result << helper->pictureToPlane( arrowLeftPoint.toPoint() );
	result << helper->pictureToPlane( arrowRightPoint.toPoint() );
	result << result.first(); /// Замкнуть

	foreach(const CoordPlane &coord, result)
	{
		mapAppendPointPlane(hobj, coord.x, coord.y);
	}

	DOUBLEPOINT rotatePoint;
	rotatePoint.x = result.first().x;
	rotatePoint.y = result.first().y;

	double azimuthRad = helper->degreeToRad(azimuth);

	mapRotateObject(hobj, &rotatePoint, &azimuthRad);

	helper->commitObject( hobj );

	return hobj;
}

HMAP MapCommlineObject::addAssignmentObject(const MapCommlineObject::Assignment &a, int index)
{
	Map2::MapHelper *helper = mapLayer()->mapView()->helper();

	HOBJ hObj = mapCreateSiteObject(mapLayer()->mapHandle(), mapLayer()->siteHandle());

	QTextCodec *tc = RscViewer::codec();
	mapRegisterObjectByKey(hObj, tc->fromUnicode("под_ср_рэб"));

	QPointF point = mArcCoords.at( (index + 1) * 2);

	CoordPlane first = helper->pictureToPlane( point.toPoint() );
	CoordPlane second = helper->pictureToPlane( point.toPoint() );

	mapAppendPointPlane(hObj, first.x, first.y);
	mapAppendPointPlane(hObj, second.x, second.y);

	mapAppendSemantic(hObj, 33334, tc->fromUnicode( a.name ), a.name.length() );
	mapAppendSemantic(hObj, 46, tc->fromUnicode( a.caption ), a.caption.length() );

	mapCommitObject(hObj);

	helper->addObjectToSelection(mapLayer()->selectHandle(), hObj);
	mapSetSiteViewSelect(mapLayer()->mapHandle(), mapLayer()->siteHandle(), mapLayer()->selectHandle());

	return hObj;
}

void MapCommlineObject::updateAssignmentObjects() const
{
	Map2::MapHelper *helper = mapLayer()->mapView()->helper();

	for(int i = 0; i < mAssignments.count(); ++i)
	{
		HOBJ hObj = mAssignments.values().at(i);

		int coordNumber = (i+1) * 2;

		QPointF point1 = mArcCoords.at(coordNumber);

		QLineF line(point1, point1 + QPointF(1,1));
		line.setLength(300);
		line.setAngle( QLineF(mArcCoords[coordNumber-1], mArcCoords[coordNumber+1]).normalVector().angle());

		CoordPlane first = helper->pictureToPlane( line.p1().toPoint() );
		CoordPlane second = helper->pictureToPlane( line.p2().toPoint() );

		mapUpdatePointPlane(hObj, first.x, first.y, 1);
		mapUpdatePointPlane(hObj, second.x, second.y, 2);

		int ok = mapCommitObject(hObj);
	}
}

void Map2::MapCommlineObject::moveBy(double dxPlane, double dyPlane)
{
	if(!mapLayer())
	{
		qDebug()<<"*** ЛИНИЯ СВЯЗИ: Невозможно обработать прямоугольную координату, пока объект не добавлен на карту.";
		return;
	}

	MapHelper *helper = mapLayer()->mapView()->helper();

	CoordPlane cpFrom = helper->geoToPlane(mFrom) + CoordPlane(dxPlane, dyPlane);
	CoordPlane cpTo = helper->geoToPlane(mTo) + CoordPlane(dxPlane, dyPlane);

	mFrom = helper->planeToGeo(cpFrom);
	mTo = helper->planeToGeo(cpTo);

	refresh();
}

QList<HOBJ*> Map2::MapCommlineObject::mapHandles()
{
	return QList<HOBJ*>() << &hFromHandle << &hToHandle << &hBody;
}


bool MapCommlineObject::Assignment::operator<(const MapCommlineObject::Assignment &other) const
{
	return this->name < other.name;
}
