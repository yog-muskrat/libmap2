#include "objects/mapzoneobject.h"
#include "mapview.h"
#include "maplayer.h"
#include "maphelper.h"
#include "rscviewer.h"

#include "gis.h"

#include <QDebug>
#include <QTextCodec>

using namespace Map2;

MapZoneObject::MapZoneObject(const QString &rscKey, QList<Map2::CoordPlane> coords, Map2::MapLayer *layer)
	: MapObject(MO_Zone, layer), mRscKey(rscKey), hObj(0)
{
	addPoints(coords);
}

MapZoneObject::MapZoneObject(const QString &rscKey, QList<Coord> coords, MapLayer *layer)
	: MapObject(MO_Zone, layer), mCoords(coords), mRscKey(rscKey), hObj(0)
{

}

void MapZoneObject::addPoint(Map2::Coord coord)
{
	mCoords << coord;

	if(!mapLayer())
	{
		return;
	}

	updateMetrics();
	commit();
}

void MapZoneObject::addPoint(Map2::CoordPlane coord)
{
	if(!mapLayer())
	{
		qDebug()<<"*** ZONE OBJECT: Невозможно обработать прямоугольную координату, пока объект не добавлен на карту.";
		return;
	}

	Map2::MapHelper *helper = mapLayer()->mapView()->helper();
	addPoint( helper->planeToGeo( coord ) );
}

void MapZoneObject::addPoints(QList<Map2::Coord> coords)
{
	foreach(const Coord &c, coords)
	{
		mCoords << c;
	}

	if(!mapLayer())
	{
		return;
	}

	updateMetrics();
	commit();
}

void MapZoneObject::addPoints(QList<Map2::CoordPlane> coords)
{
	if(!mapLayer())
	{
		qDebug()<<"*** ZONE OBJECT: Невозможно обработать прямоугольную координату, пока объект не добавлен на карту.";
		return;
	}

	Map2::MapHelper *helper = mapLayer()->mapView()->helper();

	QList<Coord> geoCoords;

	foreach(const CoordPlane &c, coords)
	{
		geoCoords <<  helper->planeToGeo( c );
	}

	addPoints(geoCoords);
}

double MapZoneObject::length() const
{
	if(!mapLayer())
	{
		return -1;
	}

	return mapPerimeter( hObj );
}

void MapZoneObject::closeZone() const
{
	if(!mapLayer())
	{
		return;
	}

	mapAbrige(hObj, 0.1);
}

void MapZoneObject::setRscKey(const QString &rscKey)
{
	if(mRscKey == rscKey)
	{
		return;
	}

	mRscKey = rscKey;

	refresh();
}

QPolygonF MapZoneObject::toPicturePolygon() const
{
	if(!helper())
	{
		return QPolygonF();
	}

	return helper()->metricsToPicturePolygon( hObj );
}

QPolygonF MapZoneObject::toPlanePolygon() const
{
	if(!helper())
	{
		return QPolygonF();
	}

	return helper()->metricsToPlanePolygon( hObj );
}

void MapZoneObject::repaint()
{
	if(!mapLayer())
	{
		return;
	}

	removeFromMap();

	if(mRscKey.isEmpty())
	{
		return;
	}

	hObj = mapCreateSiteObject(mapLayer()->mapHandle(), mapLayer()->siteHandle());
	mapRegisterObjectByKey( hObj, RscViewer::codec()->fromUnicode(mRscKey).data());

	updateMetrics();

	commit();
}

void MapZoneObject::updateMetrics()
{
	Q_ASSERT(mapLayer());

	helper()->clearMetrics(hObj);

	foreach(Coord c, mCoords)
	{
		Map2::CoordPlane cp = helper()->geoToPlane(c);
		mapAppendPointPlane(hObj, cp.x, cp.y);
	}
}

Coord Map2::MapZoneObject::coordinateGeo() const
{
	if(!mapLayer())
	{
		return Coord();
	}

	QPointF polygonCenter = toPlanePolygon().boundingRect().center();

	return helper()->planeToGeo( CoordPlane(polygonCenter) );
}

void Map2::MapZoneObject::moveBy(double dxPlane, double dyPlane)
{
	if(!mapLayer())
	{
		return;
	}

	DOUBLEPOINT dp;
	dp.x = dxPlane;
	dp.y = dyPlane;

	mapRelocateObjectPlane(hObj, &dp);

	mCoords.clear();

	for(int i = 0; i < mapPointCount(hObj, 0); ++i)
	{
		double x = mapXPlane(hObj, i+1);
		double y = mapYPlane(hObj, i+1);

		CoordPlane cp(x, y);
		mCoords << helper()->planeToGeo(cp);
	}

	commit();
}

QList<HOBJ *> Map2::MapZoneObject::mapHandles()
{
	return QList<HOBJ*>() << &hObj;
}
