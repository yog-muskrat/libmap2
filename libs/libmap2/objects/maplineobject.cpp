#include "objects/maplineobject.h"
#include "maplayer.h"
#include "maphelper.h"
#include "mapview.h"

#include "gis.h"

#include <QDebug>
#include <qmath.h>

using namespace Map2;

MapLineObject::MapLineObject(long rscCode, Map2::MapLayer *layer, const QList<CoordPlane> &coords) :
	MapObject(MO_Line, layer, rscCode)
{
	mapRegisterObject( handle(), mRscCode, LOCAL_LINE);
	addPoints(coords);
	///TODO: Разобраться, почему без нижеследующего вызова функции commit() объекты отображаются на карте через раз.
	commit();
}

void MapLineObject::addPoint(const Map2::CoordPlane &coord)
{
	mapAppendPointPlane(handle(), coord.x, coord.y);
	mCoords << coord;
	commit();
}

void MapLineObject::addPoint(const Map2::Coord &coord)
{
	Q_ASSERT(mapLayer());

	Map2::MapHelper *helper = mapLayer()->mapView()->helper();

	addPoint(helper->geoToPlane(coord));
}

void MapLineObject::addPoints(const QList<Map2::CoordPlane> &coords)
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
}

void MapLineObject::addPoints(const QList<Map2::Coord> &coords)
{
	Q_ASSERT(mapLayer());

	Map2::MapHelper *helper = mapLayer()->mapView()->helper();

	QList<CoordPlane> planeCoords;

	foreach(const Coord &c, coords)
	{
		planeCoords << helper->geoToPlane( c );
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

double MapLineObject::length() const
{
	return mapPerimeter( handle() );
}

QString MapLineObject::lengthText() const
{
	double perimetr = length();

	QString s = QString::number( perimetr, 'f', 0 );
	int len = s.length();

	if(len < 4)
	{
		return QString("%0 м").arg( perimetr, 0, 'f', 0 );
	}
	else if( len < 7)
	{
		return QString("%0 км").arg( perimetr/1000., 0, 'f', 1 );
	}
	else if( len < 10)
	{
		return QString("%0 тыс. км").arg( perimetr/1000000., 0, 'f', 2 );
	}
	else if(len < 13)
	{
		return QString("%0 млн. км").arg( perimetr/1000000000., 0, 'f', 2 );
	}

	return QString("%0 м").arg( perimetr, 0, 'f', 0 );
}

void MapLineObject::setRscCode(long rscCode)
{
	if(mRscCode == rscCode)
	{
		return;
	}

	mRscCode = rscCode;

	mapDeleteObject( handle() );
	commit();

	mObjHandle = mapCreateSiteObject(mapLayer()->mapHandle(), mapLayer()->siteHandle(), 1, IDFLOAT2 );
	mapRegisterObject(handle(), mRscCode, LOCAL_LINE);
	addPoints(mCoords);
}
