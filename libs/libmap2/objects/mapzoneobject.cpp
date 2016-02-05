#include "objects/mapzoneobject.h"
#include "mapview.h"
#include "maplayer.h"
#include "maphelper.h"

#include "gis.h"

#include <QDebug>

using namespace Map2;

MapZoneObject::MapZoneObject(long rscCode, QList<Map2::CoordPlane> coords, Map2::MapLayer *layer)
	: MapObject(MO_Zone, layer, rscCode)
{
	mapRegisterObject( handle(), mRscCode, LOCAL_SQUARE);
	addPoints(coords);
}

void MapZoneObject::addPoint(Map2::CoordPlane coord)
{
	Q_ASSERT(mapLayer());
	mapAppendPointPlane(handle(), coord.x, coord.y);

	clearPoints();

	mCoords << coord;

	appendPoints();
}

void MapZoneObject::addPoint(Map2::Coord coord)
{
	Q_ASSERT(mapLayer());

	Map2::MapHelper *helper = mapLayer()->mapView()->helper();

	addPoint( helper->geoToPlane( coord ) );
}

void MapZoneObject::addPoints(QList<Map2::CoordPlane> coords)
{
	Q_ASSERT(mapLayer());

	if(coords.isEmpty())
	{
		return;
	}

	clearPoints();

	foreach(const CoordPlane &c, coords)
	{
		mCoords << c;
	}

	appendPoints();

	commit();
}

void MapZoneObject::addPoints(QList<Map2::Coord> coords)
{
	Q_ASSERT(mapLayer());

	Map2::MapHelper *helper = mapLayer()->mapView()->helper();

	QList<CoordPlane> planeCoords;

	foreach(const Coord &c, coords)
	{
		planeCoords <<  helper->geoToPlane( c );
	}

	addPoints(planeCoords);
}

void MapZoneObject::clear()
{
	clearPoints();
	mCoords.clear();
}

double MapZoneObject::length() const
{
	return mapPerimeter( handle() );
}

void MapZoneObject::closeZone() const
{
	mapAbrige(handle(), 0.1);
}

void MapZoneObject::setRscCode(long rscCode)
{
	if(mRscCode == rscCode)
	{
		return;
	}

	mRscCode = rscCode;

	mapDeleteObject( handle() );
	commit();

	mObjHandle = mapCreateSiteObject(mapLayer()->mapHandle(), mapLayer()->siteHandle(), 1, IDFLOAT2 );

	mapRegisterObject( handle(), mRscCode, LOCAL_SQUARE);
	addPoints(mCoords);
}

void MapZoneObject::clearPoints()
{
	for(int i = mapPointCount( handle(), 0); i >0 ; --i)
	{
		mapDeletePointPlane(handle(), i);
	}
	commit();
}

void MapZoneObject::appendPoints()
{
	int i = 1;
	foreach(CoordPlane cp, mCoords)
	{
		++i;
		mapAppendPointPlane(handle(), cp.x, cp.y);
	}

	commit();
}
