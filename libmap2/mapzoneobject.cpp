#include "mapzoneobject.h"
#include "maplayer.h"

#include <QDebug>

MapZoneObject::MapZoneObject(long exCode, QList<CoordPlane> coords, MapLayer *layer) : MapObject(MO_Zone, layer)
{
	mapRegisterObject( handle(), exCode, LOCAL_SQUARE);
	addPoints(coords);
}

void MapZoneObject::addPoint(CoordPlane coord)
{
	Q_ASSERT(mapLayer());
	int i = mapAppendPointPlane(handle(), coord.x, coord.y);
	mCoords << coord;
	qDebug()<<"Point added!"<<i;
	commit();
}

void MapZoneObject::addPoint(Coord coord)
{
	Q_ASSERT(mapLayer());
	addPoint(coord.toPlane(mapLayer()->mapHandle()));
}

void MapZoneObject::addPoints(QList<CoordPlane> coords)
{
	Q_ASSERT(mapLayer());

	if(coords.isEmpty())
	{
		return;
	}

	foreach(const CoordPlane &c, coords)
	{
		mapAppendPointPlane(handle(), c.x, c.y);
		mCoords << c;
	}

	commit();
}

void MapZoneObject::addPoints(QList<Coord> coords)
{
	Q_ASSERT(mapLayer());

	QList<CoordPlane> planeCoords;

	foreach(const Coord &c, coords)
	{
		planeCoords << c.toPlane(mapLayer()->mapHandle() );
	}

	addPoints(planeCoords);
}

void MapZoneObject::clear()
{
	for(int i = mCoords.count(); i > 0; --i)
	{
		mapDeletePointPlane(handle(), i);
	}
	mCoords.clear();

	commit();
}

double MapZoneObject::length()
{
	return mapPerimeter( handle() );
}

void MapZoneObject::closeZone()
{
	int i = mapAbrige(handle(), 0.1);
	qDebug()<<"Zone closing..."<<i;
}
