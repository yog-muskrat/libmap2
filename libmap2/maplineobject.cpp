#include "maplineobject.h"
#include "maplayer.h"

#include <QDebug>

MapLineObject::MapLineObject(long exCode, MapLayer *layer, QList<Coord> coords) : MapObject(MO_Line, layer)
{
	mapRegisterObject( handle(), exCode, LOCAL_LINE);

	mTextHandle = mapCreateSiteObject(layer->mapHandle(), layer->siteHandle(), IDFLOAT2, 1);
	mapRegisterObject(mTextHandle, 1373, LOCAL_TITLE);
	mapPutText(mTextHandle, "0", 0);
	mapAppendPointPlane(mTextHandle, 0, 0);
	mapCommitObject(mTextHandle);

	addPoints(coords);
}

void MapLineObject::addPoint(CoordPlane coord)
{
	mapAppendPointPlane(handle(), coord.x, coord.y);
	mCoords << coord;

	commit();

	mapPutText(mTextHandle, QString("%0m").arg( length() ).toLocal8Bit().constData() , 0);
	mapUpdatePointPlane(mTextHandle, coord.x, coord.y, 1);
	mapCommitObject(mTextHandle);
}

void MapLineObject::addPoint(Coord coord)
{
	Q_ASSERT(mapLayer());

	addPoint(coord.toPlane(mapLayer()->mapHandle()));
}

void MapLineObject::addPoints(QList<CoordPlane> coords)
{
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

	mapPutText(mTextHandle, QString("%0м").arg( length() ).toLocal8Bit().constData() , 0);
	mapUpdatePointPlane(mTextHandle, mCoords.last().x, mCoords.last().y, 1);
	mapCommitObject(mTextHandle);
}

void MapLineObject::addPoints(QList<Coord> coords)
{
	Q_ASSERT(mapLayer());

	QList<CoordPlane> planeCoords;

	foreach(const Coord &c, coords)
	{
		planeCoords << c.toPlane(mapLayer()->mapHandle() );
	}

	addPoints(planeCoords);
}

void MapLineObject::clear()
{
	for(int i = mCoords.count(); i > 0; --i)
	{
		mapDeletePointPlane(handle(), i);
	}
	mCoords.clear();

	commit();
}

double MapLineObject::length()
{
	return mapPerimeter( handle() );
}
