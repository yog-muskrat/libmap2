#include "maphelper.h"

#include <QLineF>
#include <qmath.h>

double MapHelper::radToDegree(const double &rad)
{
	return rad * 180. / M_PI;
}

double MapHelper::degreeToRad(const double &degree)
{
	return degree * M_PI / 180.;
}

Coord MapHelper::planeToGeo(HMAP mapHnd, const CoordPlane &coordPlane)
{
	double lat = coordPlane.x;
	double lng = coordPlane.y;

	mapPlaneToGeo(mapHnd, &lat, &lng);

	lat = radToDegree(lat);
	lng = radToDegree(lng);

	return Coord(lat, lng);
}

CoordPlane MapHelper::geoToPlane(HMAP mapHnd, const Coord &coord)
{
	double x = degreeToRad( coord.lat );
	double y = degreeToRad( coord.lng );

	mapGeoToPlane(mapHnd, &x, &y);

	return CoordPlane(x, y);
}

QPoint MapHelper::planeToPicture(HMAP mapHnd, const CoordPlane &coord)
{
	double x = coord.x;
	double y = coord.y;

	mapPlaneToPicture(mapHnd, &x, &y);

	return QPoint(x, y);
}

QPoint MapHelper::geoToPicture(HMAP mapHnd, const Coord &coord)
{
	CoordPlane coordPlane = geoToPlane(mapHnd, coord);

	return planeToPicture( mapHnd, coordPlane );
}

CoordPlane MapHelper::pictureToPlane(HMAP mapHnd, const QPoint &point)
{
	double x = point.x();
	double y = point.y();

	mapPictureToPlane(mapHnd, &x, &y);

	return CoordPlane(x, y);
}


double MapHelper::bearing(const CoordPlane &pointFrom, const CoordPlane &pointTo)
{
	QLineF line(pointFrom.y, pointFrom.x, pointTo.y, pointTo.x);

	// Необходимо прибавить 90 градусов, т.к. в Qt ноль находится на востоке, а не на севере.
	return line.angle() + 90;
}


Coord MapHelper::pictureToGeo(HMAP mapHnd, const QPoint &point)
{
	CoordPlane coordPlane = MapHelper::pictureToPlane(mapHnd, point);
	return MapHelper::planeToGeo( mapHnd, coordPlane );
}
