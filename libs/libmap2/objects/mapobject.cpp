#include "objects/mapobject.h"
#include "maplayer.h"
#include "mapview.h"

#include "gis.h"

#include <QDebug>
#include <QTextCodec>

using namespace Map2;

MapObject::MapObject(Map2::MapObject::Type t, Map2::MapLayer *layer, long rscCode):
	mType(t),
	mObjHandle(-1),
	pLayer(layer),
	mMapKey(-1),
	mSelected(false),
	mRscCode(rscCode),
	mHidden(false)
{
	mObjHandle = mapCreateSiteObject(mapLayer()->mapHandle(), mapLayer()->siteHandle(), 1, IDFLOAT2 );
	commit();

	layer->addObject(this);
}

MapObject::~MapObject()
{
	if(handle() >0 )
	{
		unbindMetrics();
		mapCommitObject(handle());
		mapFreeObject(handle());
		mObjHandle = 0;
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

	if(b)
	{
		QColor c(Qt::yellow);
		QString color = QString::number( RGB(c.red(), c.green(), c.blue()) );
		qDebug()<<"Add semantic"<<mapAppendSemantic(handle(), 31002, color.toLocal8Bit().data(), 255);
	}
	else
	{
		mapAppendSemantic(handle(), 31002, 0, 255);
		mapRedefineObject(handle());
	}

	HSELECT hselect = mapLayer()->mapView()->selectContext();

	mapSelectObject(hselect, mapKey(), (mSelected ? 1 : 0) );

	commit();
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

void MapObject::setMapLayer(Map2::MapLayer *layer)
{
	if(layer == pLayer)
	{
		return;
	}

	if(pLayer)
	{
		pLayer->takeObject(this);
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

	unbindMetrics();
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
		if(!mb.object || !mb.object->handle())
		{
			continue;
		}

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
	if(!handle())
	{
		return;
	}
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
	}

	return mMapKey;
}

void MapObject::setParameter(QString parameter, QVariant value)
{
	mParameters[parameter] = value;
}

QVariant MapObject::parameter(QString parameter) const
{
	return mParameters[parameter];
}

void MapObject::hide()
{
	setHidden(true);
}

void MapObject::show()
{
	setHidden(false);
}

void MapObject::setHidden(bool hidden)
{
	if(mHidden == hidden)
	{
		return;
	}

	mHidden = hidden;

	if(!mapLayer())
	{
		return;
	}

	HSELECT select = mapLayer()->selectHandle();
	int list = mapGetListNumber( handle() );
	int key = mapKey();

	if(mHidden)
	{
		mapInvertSample(select);
		mapSelectSampleByList(select, list, key);
		mapInvertSample(select);
	}
	else
	{
		mapSelectSampleByList(select, list, key);
	}

	mapSetSiteViewSelect(mapLayer()->mapHandle(), mapLayer()->siteHandle(), select);

	mapLayer()->objectChangedNotify(this);
}
