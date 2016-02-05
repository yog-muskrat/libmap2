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

Coord MapHelper::planeToGeo(const Map2::CoordPlane &coordPlane)
{
	double lat = coordPlane.x;
	double lng = coordPlane.y;

	mapPlaneToGeo(mMapHnd, &lat, &lng);

	lat = radToDegree(lat);
	lng = radToDegree(lng);

	return Coord(lat, lng);
}

CoordPlane MapHelper::geoToPlane(const Map2::Coord &coord)
{
	double x = degreeToRad( coord.lat );
	double y = degreeToRad( coord.lng );

	mapGeoToPlane(mMapHnd, &x, &y);

	return CoordPlane(x, y);
}

QPoint MapHelper::planeToPicture(const Map2::CoordPlane &coord)
{
	double x = coord.x;
	double y = coord.y;

	mapPlaneToPicture(mMapHnd, &x, &y);

	return QPoint(x, y);
}

QPoint MapHelper::geoToPicture(const Map2::Coord &coord)
{
	CoordPlane coordPlane = geoToPlane(coord);

	return planeToPicture(coordPlane);
}

CoordPlane MapHelper::pictureToPlane(const QPoint &point)
{
	double x = point.x();
	double y = point.y();

	mapPictureToPlane(mMapHnd, &x, &y);

	return CoordPlane(x, y);
}

double MapHelper::bearing(const CoordPlane &pointFrom, const Map2::CoordPlane &pointTo)
{
	QLineF line(pointFrom.y, pointFrom.x, pointTo.y, pointTo.x);

	// Необходимо прибавить 90 градусов, т.к. в Qt ноль находится на востоке, а не на севере.
	return line.angle() + 90;
}

Coord MapHelper::pictureToGeo(const QPoint &point)
{
	CoordPlane coordPlane = pictureToPlane(point);
	return planeToGeo(coordPlane );
}

Coord MapHelper::center(const Coord &coord1, const Coord &coord2)
{
	CoordPlane coordPlane1 = geoToPlane(coord1);
	CoordPlane coordPlane2 = geoToPlane(coord2);

	CoordPlane coordCenter;
	coordCenter.x = coordPlane1.x + (coordPlane2.x - coordPlane1.x)/2;
	coordCenter.y = coordPlane1.y + (coordPlane2.y - coordPlane1.y)/2;

	return planeToGeo(coordCenter);
}

double MapHelper::mkm2pix(double mkm)
{
	return mkm /mMkmInPx;
}

double MapHelper::pix2mkm(double pix)
{
	return pix * mMkmInPx;
}
