#ifndef MAPZONEOBJECT_H
#define MAPZONEOBJECT_H

#include "structs.h"
#include "mapobject.h"

#include <QList>

class MapZoneObject : public MapObject
{
public:
	MapZoneObject(long exCode, QList<Coord> coords = QList<Coord>(), MapLayer *layer = 0);
};

#endif // MAPZONEOBJECT_H
