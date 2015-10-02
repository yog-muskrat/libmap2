#ifndef MAPTOOLS_H
#define MAPTOOLS_H

#include <QPoint>
#include "structs.h"

#include "gis.h"

class MapTools
{
public:
	static double radToDegree(const double &rad);
	static double degreeToRad(const double &degree);

	static Coord planeToGeo(HMAP mapHnd, const CoordPlane &coordPlane);
	static CoordPlane geoToPlane(HMAP mapHnd, const Coord &coord);
	static QPoint planeToPicture(HMAP mapHnd, const CoordPlane &coord);
	static QPoint geoToPicture(HMAP mapHnd, const Coord &coord);
private:
	MapTools(){}
};

#endif // MAPTOOLS_H
