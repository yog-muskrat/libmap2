#ifndef MAPLINEOBJECT_H
#define MAPLINEOBJECT_H

#include "mapobject.h"
#include "structs.h"

#include <QList>

class MapLineObject : public MapObject
{
public:
	MapLineObject(long exCode, MapLayer *layer = 0, QList<Coord> coords = QList<Coord>());

	void addPoint(CoordPlane coord);
	void addPoint(Coord coord);
	void addPoints(QList<CoordPlane> coords);
	void addPoints(QList<Coord> coords);

	void clear();

	double length();

private:
	QList<CoordPlane> mCoords;

	HOBJ mTextHandle;
};

#endif // MAPLINEOBJECT_H
