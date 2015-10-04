#include "structs.h"
#include "maptools.h"

CoordPlane Coord::toPlane(HMAP mapHnd) const
{
	return MapTools::geoToPlane(mapHnd, Coord(lat, lng));
}


CoordPlane CoordPlane::operator +(const CoordPlane &right)
{
	x += right.x;
	y += right.y;
	return *this;
}

CoordPlane &CoordPlane::operator +=(const CoordPlane &other)
{
	this->x += other.x;
	this->y += other.y;
	return *this;
}

Coord CoordPlane::toGeo(HMAP mapHnd) const
{
	return MapTools::planeToGeo(mapHnd, CoordPlane(x, y));
}
