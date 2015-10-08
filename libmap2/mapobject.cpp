#include "mapobject.h"
#include "maplayer.h"
#include "mapview.h"

#include <QDebug>

MapObject::MapObject(Type t, MapLayer *layer): mType(t), mObjHandle(-1), pLayer(layer), mMapKey(-1), mSelected(false), tmp(0)
{
	mObjHandle = mapCreateSiteObject(mapLayer()->mapHandle(), mapLayer()->siteHandle(), 1, IDFLOAT2 );
	commit();

	layer->addObject(this);
}

MapObject::~MapObject()
{
	if(handle() >0 )
	{
		mapCommitObject(handle());
		mapFreeObject(handle());
	}
}

void MapObject::remove()
{
	Q_ASSERT(handle() > 0);

	if(mapLayer())
	{
		mapLayer()->removeObject(this);
	}
	else
	{
		removeFromMap();
	}
}

void MapObject::center()
{
	Q_ASSERT(handle() > 0 && mapLayer() );

	mapLayer()->mapView()->setCenter( coordinate() );
}

void MapObject::setSelected(bool b)
{
	mSelected = b;

	if(!mapLayer())
	{
		return;
	}

	HSELECT hselect = mapLayer()->mapView()->selectContext();

	mapSelectObject(hselect, mapKey(), (mSelected ? 1 : 0) );
}

CoordPlane MapObject::coordinate() {
	double x = mapXPlane( handle() );
	double y = mapYPlane( handle() );

	return CoordPlane(x, y);
}

void MapObject::moveBy(double dxPlane, double dyPlane)
{
	for(int  i = 1; i <= mapPointCount(handle(), 0); i++)
	{
		double x = mapXPlane(handle(), i) - dxPlane;
		double y = mapYPlane(handle(), i) - dyPlane;
		updateMetric(i, CoordPlane(x, y));
	}

	commit();
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
	commit();
	mMapKey = 0;
}

void MapObject::commit()
{
	mapCommitObject(handle());

	if(mapLayer())
	{
		mapLayer()->objectChangedNotify(this);
	}
}

void MapObject::addMetricBinding(MetricBinding binding, int targetMetric)
{
	if(mObjectsBindings.contains(targetMetric, binding))
	{
		return;
	}

	mObjectsBindings.insertMulti(targetMetric, binding);

	double x = mapXPlane( handle(), targetMetric);
	double y = mapYPlane( handle(), targetMetric);

	updateMetric(targetMetric, CoordPlane(x,y));
}

void MapObject::removeMetricBinding(MetricBinding binding, int targetMetric)
{
	mObjectsBindings.remove(targetMetric, binding);
}

void MapObject::removeFromMap()
{
	Q_ASSERT(handle() > 0);

	mapDeleteObject( handle() );
	mapCommitObject( handle() );
	mapFreeObject( handle() );

	mObjHandle = 0;
	mMapKey = 0;
}

void MapObject::setName(QString name)
{
	mName = name;

	pLayer->objectChangedNotify(this);
}

void MapObject::bindMetric(int metricNumber, MapObject *targetObject, int targetMetricNumber)
{
	unbindMetric(metricNumber);

	MetricBinding mb;
	mb.object = targetObject;
	mb.metricNumber = targetMetricNumber;

	targetObject->addMetricBinding(MetricBinding(this, metricNumber), targetMetricNumber);
	mMetricsBindings[metricNumber] = mb;
}

void MapObject::unbindMetric(int metricNumber)
{
	if(mMetricsBindings.contains(metricNumber))
	{
		MetricBinding mb = mMetricsBindings.take( metricNumber );
		mb.object->removeMetricBinding( MetricBinding(this, metricNumber), mb.metricNumber);
	}
}

void MapObject::unbindMetrics()
{
	foreach(int i, mMetricsBindings.keys())
	{
		MetricBinding &mb = mMetricsBindings[i];
		mb.object->removeMetricBinding( MetricBinding(this, i), mb.metricNumber);
	}

	mMetricsBindings.clear();
}

void MapObject::updateMetric(int metricNumber, CoordPlane coord)
{
	if(!mMetricsBindings.contains(metricNumber))
	{
		mapUpdatePointPlane(handle(), coord.x, coord.y, metricNumber);
	}

	foreach(const MetricBinding &mb, mObjectsBindings.values(metricNumber))
	{
		mb.object->updateBindedMetric(mb.metricNumber, coord);
	}
}

void MapObject::updateBindedMetric(int metricNumber, CoordPlane coord)
{
	mapUpdatePointPlane(handle(), coord.x, coord.y, metricNumber);

	foreach(const MetricBinding &mb, mObjectsBindings.values(metricNumber))
	{
		mb.object->updateBindedMetric(mb.metricNumber, coord);
	}

	commit();
}

long MapObject::mapKey()
{
	if(mMapKey <= 0)
	{
		mMapKey = mapObjectKey( handle() );
		qDebug()<<"Handle="<<handle()<<"key="<<mMapKey;
	}

	return mMapKey;
}
