#include "mapobject.h"
#include "maplayer.h"
#include "mapview.h"

MapObject::MapObject(Type t, MapLayer *layer): mType(t), mObjHandle(-1), pLayer(layer)
{
	mObjHandle = mapCreateSiteObject(mapLayer()->mapHandle(), mapLayer()->siteHandle(), 1, IDFLOAT2 );

	layer->addObject(this);
}

MapObject::~MapObject()
{
	Q_ASSERT(handle() > 0);

	mapCommitObject(handle());
	mapFreeObject(handle());
}

void MapObject::remove()
{
	Q_ASSERT(handle() > 0);

	mapDeleteObject( handle() );
	mapCommitObject( handle() );
	mapFreeObject( handle() );
}

void MapObject::center()
{
	Q_ASSERT(handle() > 0 && mapLayer() );

	mapLayer()->mapView()->setCenter( coordinate() );
}

CoordPlane MapObject::coordinate() const {
	double x = mapXPlane( handle() );
	double y = mapYPlane( handle() );

	return CoordPlane(x, y);
}

QString MapObject::typeName() const
{
	if(mType == MO_Vector)
	{
		return "Одиночный";
	}
	else if(mType == MO_Line)
	{
		return "Линия";
	}
	else if(mType == MO_Zone)
	{
		return "Зона";
	}

	return "";
}

void MapObject::setMapLayer(MapLayer *layer)
{
	if(layer == pLayer)
	{
		return;
	}

	pLayer = layer;
	pLayer->addObject( this );
	mapChangeObjectMap(handle(), layer->mapHandle(), layer->siteHandle());
	mapCommitObject(handle());
}

void MapObject::setName(QString name)
{
	mName = name;
}
