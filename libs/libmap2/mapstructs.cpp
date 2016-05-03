#include "mapstructs.h"
#include "maphelper.h"

#include "gis.h"

#include <qmath.h>

using namespace Map2;

CoordPlane CoordPlane::operator +(const Map2::CoordPlane &right)
{
	CoordPlane coord( *this);
	coord.x += right.x;
	coord.y += right.y;
	return coord;
}

CoordPlane &CoordPlane::operator +=(const Map2::CoordPlane &other)
{
	this->x += other.x;
	this->y += other.y;
	return *this;
}

CoordPlane CoordPlane::operator-(const Map2::CoordPlane &right)
{
	CoordPlane coord( *this);
	coord.x -= right.x;
	coord.y -= right.y;
	return coord;
}

CoordPlane &CoordPlane::operator-=(const Map2::CoordPlane &other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}

bool Coord::isValid() const
{
	if(lat == 0 && lng == 0)
	{
		return false;
	}
	else if(lat < -90.)
	{
		return false;
	}
	else if(lat > 90.)
	{
		return false;
	}
	else if(lng < -360)
	{
		return false;
	}
	else if(lng > 360)
	{
		return false;
	}

	return true;

//	return lat != 0 && lng != 0 && lat <= 90. && lat >= -90 && lng <= 360 && lng >= -360;
}

Coord Coord::fromDegreeWithMinutes(const double &lat, const double &lng)
{
	double latInt = 0.;
	double lngInt = 0.;

	double latFract = modf(lat, &latInt);
	double lngFract = modf(lng, &lngInt);

	double newLat = latInt + latFract * 100. / 60.;
	double newLng = lngInt + lngFract * 100. / 60.;

	return Coord(newLat, newLng);
}
