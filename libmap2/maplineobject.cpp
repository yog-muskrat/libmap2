#include "maplineobject.h"
#include "maplayer.h"

MapLineObject::MapLineObject(long exCode, QList<Coord> coords, MapLayer *layer) : MapObject(MO_Zone, layer)
{
}
