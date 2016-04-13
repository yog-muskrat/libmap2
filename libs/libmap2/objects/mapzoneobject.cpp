#include "objects/mapzoneobject.h"
#include "mapview.h"
#include "maplayer.h"
#include "maphelper.h"
#include "rscviewer.h"

#include "gis.h"

#include <QDebug>
#include <QTextCodec>

using namespace Map2;

MapZoneObject::MapZoneObject(const QString &rscKey, QList<Coord> coords, MapLayer *layer)
	: MapObject(MO_Zone, layer), mCoords(coords), mRscKey(rscKey), hObj(0)
{
	if(layer)
	{
		hObj = mapCreateSiteObject(mapLayer()->mapHandle(), mapLayer()->siteHandle());
		mapRegisterObjectByKey( hObj, RscViewer::codec()->fromUnicode(mRscKey).data());
		addPoints(coords);
	}
	else
	{
		mCoords = coords;
	}
}

void MapZoneObject::addPoint(Map2::Coord coord)
{
	mCoords << coord;

	if(!mapLayer())
	{
		return;
	}

	updateCoordinates();

//	Q_ASSERT(hObj);

//	CoordPlane cp = helper()->geoToPlane(coord);

//	mapAppendPointPlane(hObj, cp.x, cp.y);

//	commit();
}

void MapZoneObject::addPoint(Map2::CoordPlane coord)
{
	if(!mapLayer())
	{
		qDebug()<<"*** ZONE OBJECT: Невозможно обработать прямоугольную координату, пока объект не добавлен на карту.";
		return;
	}

	addPoint( helper()->planeToGeo( coord ) );
}

void MapZoneObject::addPoints(QList<Map2::Coord> coords)
{
	mCoords += coords;

	if(!mapLayer())
	{
		return;
	}

	updateCoordinates();

//	Q_ASSERT(hObj);

//	foreach(const Coord &c, coords)
//	{
//		CoordPlane cp = helper()->geoToPlane(c);
//		mapAppendPointPlane(hObj, cp.x, cp.y);
//	}

//	commit();
}

void MapZoneObject::addPoints(QList<Map2::CoordPlane> coords)
{
	if(!mapLayer())
	{
		qDebug()<<"*** ZONE OBJECT: Невозможно обработать прямоугольную координату, пока объект не добавлен на карту.";
		return;
	}

	QList<Coord> geoCoords;

	foreach(const CoordPlane &c, coords)
	{
		geoCoords <<  helper()->planeToGeo( c );
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

	hObj = mapCreateSiteObject(mapLayer()->mapHandle(), mapLayer()->siteHandle());
	mapRegisterObjectByKey( hObj, RscViewer::codec()->fromUnicode(mRscKey).data());

	updateCoordinates();

//	foreach(Coord c, mCoords)
//	{
//		Map2::CoordPlane cp = helper()->geoToPlane(c);
//		mapAppendPointPlane(hObj, cp.x, cp.y);
//	}

//	commit();
}

Coord Map2::MapZoneObject::coordinateGeo() const
{
	if(!mapLayer())
	{
		return Coord();
	}
	return helper()->objectCenter(hObj);
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

	mCoords = helper()->objectGeoCoordinates( hObj );

	commit();
}

void MapZoneObject::updateCoordinates()
{
	helper()->clearMetrics(hObj);

	foreach(const Coord &c, mCoords)
	{
		Map2::CoordPlane cp = helper()->geoToPlane(c);
		mapAppendPointPlane(hObj, cp.x, cp.y);
	}

	commit();
}

QList<HOBJ *> Map2::MapZoneObject::mapHandles()
{
	return QList<HOBJ*>() << &hObj;
}
