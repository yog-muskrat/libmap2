#include "mapobject.h"
#include "maplayer.h"

MapObject::MapObject(Type t, MapLayer *layer): mType(t), mObjHandle(-1), pLayer(layer)
{

}

MapObject::~MapObject()
{
	if(mObjHandle > 0)
	{
		mapDeleteObject(mObjHandle);
		mapCommitObject(mObjHandle);
		mapFreeObject(mObjHandle);
	}

	if(pLayer)
	{
		pLayer->removeObject(this);
	}
}

void MapObject::setMapLayer(MapLayer *layer)
{
	if(pLayer)
	{
		/// Перенести объект(ы) со старого слоя.
	}
}
