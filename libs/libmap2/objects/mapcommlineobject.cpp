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
	mLineWidth(5),
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
	for(int i = 0 ; i < mapPointCount(handle(), 0); ++i)
	{
		mapDeletePointPlane(handle(), i+1);
	}

	IMGLINE parmLine;
	memset(&parmLine, 0x0, sizeof(IMGLINE));
	parmLine.Thick = (ulong)helper->px2mkm( mLineWidth );
	parmLine.Color = RGB(mColor.red(), mColor.green(), mColor.blue());

	mapAppendDraw(handle(), IMG_LINE, (char*)&parmLine);

	CoordPlane from = helper->geoToPlane( mFrom );
	CoordPlane to = helper->geoToPlane(mTo);

	mapAppendPointPlane( handle(), from.x, from.y);
	mapAppendPointPlane( handle(), to.x, to.y);

	double azimuth = helper->bearing(from, to);

	if(mArrowStyle == AS_StartArrow || mArrowStyle == AS_BothArrows)
	{

		hFromHandle = addArrow(from, -azimuth - 180);
	}

	if(mArrowStyle == AS_EndArrow || mArrowStyle == AS_BothArrows)
	{

		hToHandle = addArrow(to, -azimuth );
	}

	commit();
}

void Map2::MapCommlineObject::drawArc()
{
	Q_ASSERT( mapLayer() );
	Map2::MapHelper *helper = mapLayer()->mapView()->helper();

	QPointF fromPicture = helper->geoToPicture( mFrom );
	QPointF toPicture = helper->geoToPicture( mTo );
	QLineF line(fromPicture, toPicture);
	qreal angle = line.angle();
	qreal l = line.length();
	qreal radius = l * 3;

	qreal base = qSqrt( qPow(radius, 2) - qPow(l/2., 2));

	QPointF middle = line.pointAt(0.5);

	QLineF line2(middle,middle);
	line2.setLength(base);
	line2.setAngle(angle - 90);

	QPointF center =line2.p2();
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
