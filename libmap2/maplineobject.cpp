#include "maplineobject.h"
#include "maplayer.h"

#include <QDebug>
#include <qmath.h>

MapLineObject::MapLineObject(long exCode, MapLayer *layer, QList<Coord> coords) : MapObject(MO_Line, layer)
{
	mapRegisterObject( handle(), exCode, LOCAL_LINE);
	addPoints(coords);
}

void MapLineObject::addPoint(CoordPlane coord)
{
	mapAppendPointPlane(handle(), coord.x, coord.y);
	mCoords << coord;
	commit();
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

QString MapLineObject::lengthText()
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
