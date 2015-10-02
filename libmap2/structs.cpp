#include "structs.h"
#include "maptools.h"

CoordPlane Coord::toPlane(HMAP mapHnd) const
{
	return MapTools::geoToPlane(mapHnd, Coord(lat, lng));
}


Coord CoordPlane::toGeo(HMAP mapHnd) const
{
	return MapTools::planeToGeo(mapHnd, CoordPlane(x, y));
}
