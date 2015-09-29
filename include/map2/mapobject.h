#ifndef MAPOBJECT_H
#define MAPOBJECT_H

#include "structs.h"

#include "gis/mapapi.h"
#include "gis/maptype.h"

class MapLayer;

class MapObject
{
public:
	enum Type
	{
		MO_Vector,
		MO_Line,
		MO_Zone
	};

	MapObject(Type t, MapLayer *layer = 0);
	~MapObject();

	Type type() const {return mType;}
	HOBJ handle() const {return mObjHandle;}

	void setMapLayer(MapLayer *layer);
	MapLayer* mapLayer() {return pLayer;}

protected:
	Type mType;
	HOBJ mObjHandle;
	MapLayer *pLayer;
};

#endif // MAPOBJECT_H
