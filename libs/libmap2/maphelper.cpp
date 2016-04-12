#include "maphelper.h"

#include "gis.h"

#include <QLineF>
#include <qmath.h>

using namespace Map2;

double MapHelper::radToDegree(const double &rad)
{
	return rad * 180. / M_PI;
}

double MapHelper::degreeToRad(const double &degree)
{
	return degree * M_PI / 180.;
}

Coord MapHelper::planeToGeo(const Map2::CoordPlane &coordPlane) const
{
	double lat = coordPlane.x;
	double lng = coordPlane.y;

	mapPlaneToGeo(mMapHnd, &lat, &lng);

	lat = radToDegree(lat);
	lng = radToDegree(lng);

	return Coord(lat, lng);
}

CoordPlane MapHelper::geoToPlane(const Map2::Coord &coord) const
{
	double x = degreeToRad( coord.lat );
	double y = degreeToRad( coord.lng );

	mapGeoToPlane(mMapHnd, &x, &y);

	return CoordPlane(x, y);
}

QPoint MapHelper::planeToPicture(const Map2::CoordPlane &coord) const
{
	double x = coord.x;
	double y = coord.y;

	mapPlaneToPicture(mMapHnd, &x, &y);

	return QPoint(x, y);
}

QPoint MapHelper::geoToPicture(const Map2::Coord &coord) const
{
	CoordPlane coordPlane = geoToPlane(coord);

	return planeToPicture(coordPlane);
}

CoordPlane MapHelper::pictureToPlane(const QPoint &point) const
{
	double x = point.x();
	double y = point.y();

	mapPictureToPlane(mMapHnd, &x, &y);

	return CoordPlane(x, y);
}

double MapHelper::bearing(const CoordPlane &pointFrom, const Map2::CoordPlane &pointTo) const
{
	QLineF line(pointFrom.y, pointFrom.x, pointTo.y, pointTo.x);

	// Необходимо прибавить 90 градусов, т.к. в Qt ноль находится на востоке, а не на севере.
	return line.angle() + 90;
}

Coord MapHelper::pictureToGeo(const QPoint &point) const
{
	CoordPlane coordPlane = pictureToPlane(point);
	return planeToGeo(coordPlane );
}

qreal MapHelper::distance(Coord c1, Coord c2) const
{
	CoordPlane cp1 = geoToPlane(c1);
	CoordPlane cp2 = geoToPlane(c2);

	return distance(cp1, cp2);
}

qreal MapHelper::distance(CoordPlane c1, CoordPlane c2) const
{
	DOUBLEPOINT from;
	from.x = c1.x;
	from.y = c1.y;

	DOUBLEPOINT to;
	to.x = c2.x;
	to.y = c2.y;

	return mapDistance(&from, &to);
}

qreal MapHelper::distancePx(Coord c1, Coord c2) const
{
	QPoint p1 = geoToPicture(c1);
	QPoint p2 = geoToPicture(c2);

	return QLineF( QPointF(p1), QPointF(p2)).length();
}

Coord MapHelper::center(const Coord &coord1, const Coord &coord2) const
{
	CoordPlane coordPlane1 = geoToPlane(coord1);
	CoordPlane coordPlane2 = geoToPlane(coord2);

	CoordPlane coordCenter;
	coordCenter.x = coordPlane1.x + (coordPlane2.x - coordPlane1.x)/2;
	coordCenter.y = coordPlane1.y + (coordPlane2.y - coordPlane1.y)/2;

	return planeToGeo(coordCenter);
}

double MapHelper::mkm2px(double mkm) const
{
	return mkm /mMkmInPx;
}

double MapHelper::px2mkm(double pix) const
{
	return pix * mMkmInPx;
}

bool MapHelper::clearMetrics(HOBJ hObj) const
{
	if(hObj <= 0)
	{
		return false;
	}

	for(int i = mapPointCount(hObj, 0); i > 0; --i)
	{
		mapDeletePointPlane(hObj, i);
	}

	return true;
}

void MapHelper::clearHandle(HOBJ *hObj)
{
	if(! hObj || *hObj <=0)
	{
		return;
	}

	HOBJ h = *hObj;

	mapFreeObject(h);
	*hObj = 0;
}

bool MapHelper::commitByOrder(HOBJ hObj)
{
	if(hObj <= 0)
	{
		return false;
	}

	return mapCommitObjectByOrder(hObj) !=0;
}

bool MapHelper::removeObject(HOBJ hObj)
{
	if(hObj <= 0)
	{
		return false;
	}

	return mapDeleteObject(hObj) != 0;
}

bool MapHelper::commitObject(HOBJ hObj)
{
	if(hObj <= 0)
	{
		return false;
	}

	return mapCommitObject(hObj) != 0;
}

long MapHelper::objectMapKey(HOBJ hObj) const
{
	if(hObj <= 0)
	{
		return 0;
	}

	return mapObjectKey(hObj);
}

void MapHelper::setSelected(HOBJ hObj, QColor c) const
{
	if(hObj <= 0)
	{
		return;
	}

	QString color = QString::number( RGB(c.red(), c.green(), c.blue()) );

	mapAppendSemantic(hObj, 31002, color.toLocal8Bit().data(), 255);
}

void MapHelper::addObjectToSelection(HSELECT select, HOBJ hObj) const
{
	if(hObj <=0 )
	{
		return;
	}

	int list = mapGetListNumber( hObj );
	int key = mapObjectKey( hObj );

	mapSelectSampleByList(select, list, key);
}

void MapHelper::removeObjectFromSelection(HSELECT select, HOBJ hObj) const
{
	if(hObj <=0 )
	{
		return;
	}

	int list = mapGetListNumber( hObj );
	int key = mapObjectKey( hObj );

	mapInvertSample(select);
	mapSelectSampleByList(select, list, key);
	mapInvertSample(select);
}

QPolygonF MapHelper::metricsToPlanePolygon(HOBJ hObj) const
{
	QPolygonF polygon;

	if(hObj <= 0)
	{
		return polygon;
	}

	for(int i = mapPointCount(hObj, 0); i > 0; --i)
	{
		double x = mapXPlane(hObj, i);
		double y = mapYPlane(hObj, i);

		polygon << QPointF(x, y);
	}

	return polygon;
}

QPolygonF MapHelper::metricsToPicturePolygon(HOBJ hObj) const
{
	QPolygonF planePolygon = metricsToPlanePolygon(hObj);
	QPolygonF picturePolygon;

	foreach(QPointF plane, planePolygon)
	{
		double x = plane.x();
		double y = plane.y();
		mapPlaneToPicture(hObj, &x, &y);

		picturePolygon << QPointF(x, y);
	}

	return picturePolygon;
}

QList<Coord> MapHelper::objectGeoCoordinates(HOBJ hObj) const
{
	QList<Coord> result;

	for(int i = mapPointCount(hObj, 0); i > 0; --i)
	{
		double x = mapXPlane(hObj, i);
		double y = mapYPlane(hObj, i);

		result << planeToGeo( CoordPlane(x, y));
	}

	return result;
}
