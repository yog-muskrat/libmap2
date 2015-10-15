#include "structs.h"
#include "maphelper.h"

CoordPlane Coord::toPlane(HMAP mapHnd) const
{
	return MapHelper::geoToPlane(mapHnd, Coord(lat, lng));
}


CoordPlane CoordPlane::operator +(const CoordPlane &right)
{
	CoordPlane coord( *this);
	coord.x += right.x;
	coord.y += right.y;
	return coord;
}

CoordPlane &CoordPlane::operator +=(const CoordPlane &other)
{
	this->x += other.x;
	this->y += other.y;
	return *this;
}

CoordPlane CoordPlane::operator-(const CoordPlane &right)
{
	CoordPlane coord( *this);
	coord.x -= right.x;
	coord.y -= right.y;
	return coord;
}

CoordPlane &CoordPlane::operator-=(const CoordPlane &other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}

Coord CoordPlane::toGeo(HMAP mapHnd) const
{
	return MapHelper::planeToGeo(mapHnd, CoordPlane(x, y));
}
