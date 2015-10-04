#ifndef MAPLINEOBJECT_H
#define MAPLINEOBJECT_H

#include "mapobject.h"
#include "structs.h"

#include <QList>

class MapLineObject : public MapObject
{
public:
	MapLineObject(long exCode, QList<Coord> coords = QList<Coord>(), MapLayer *layer = 0);
};

#endif // MAPLINEOBJECT_H
