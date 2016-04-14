#include "objects/maplineobject.h"
#include "maplayer.h"
#include "maphelper.h"
#include "mapview.h"
#include "rscviewer.h"

#include "gis.h"

#include <QDebug>
#include <qmath.h>
#include <QTextCodec>

using namespace Map2;

MapLineObject::MapLineObject(const QString &rscKey, const QList<Coord> &coords, Map2::MapLayer *layer) :
	MapObject(MO_Line, layer), mRscKey(rscKey), hObj(0)
{
	if(layer)
	{
		hObj = mapCreateSiteObject(mapLayer()->mapHandle(), mapLayer()->siteHandle());
		mapRegisterObjectByKey( hObj, RscViewer::codec()->fromUnicode(mRscKey).data());
		addPoints(coords);

		show();
	}
	else
	{
		mCoords = coords;
	}
}

void MapLineObject::addPoint(const Map2::Coord &coord)
{
	mCoords << coord;

	if(!mapLayer())
	{
		return;
	}

	Q_ASSERT(hObj);

	Map2::MapHelper *helper = mapLayer()->mapView()->helper();

	CoordPlane cp = helper->geoToPlane(coord);

	mapAppendPointPlane(hObj, cp.x, cp.y);
	commit();
}

void MapLineObject::addPoint(const Map2::CoordPlane &coord)
{
	if(!mapLayer())
	{
		return;
	}

	Map2::MapHelper *helper = mapLayer()->mapView()->helper();
	addPoint(helper->planeToGeo(coord));
}

void MapLineObject::addPoints(const QList<Map2::Coord> &coords)
{
	mCoords += coords;

	if(!mapLayer())
	{
		return;
	}

	Q_ASSERT(hObj);

	Map2::MapHelper *helper = mapLayer()->mapView()->helper();

	foreach(const Coord &c, coords)
	{
		CoordPlane cp = helper->geoToPlane(c);
		mapAppendPointPlane(hObj, cp.x, cp.y);
	}

	commit();
}

void MapLineObject::addPoints(const QList<Map2::CoordPlane> &coords)
{
	if(!mapLayer())
	{
		qDebug()<<"*** LINE OBJECT: Невозможно обработать прямоугольную координату, пока объект не добавлен в слой.";
		return;
	}

	Map2::MapHelper *helper = mapLayer()->mapView()->helper();

	QList<Coord> coordsGeo;

	foreach(const CoordPlane &c, coords)
	{
		coordsGeo << helper->planeToGeo(c);
	}

	addPoints(coordsGeo);
}

void MapLineObject::clear()
{
	mCoords.clear();

	if(!helper())
	{
		return;
	}

	helper()->clearMetrics(hObj);

	commit();
}

double MapLineObject::length() const
{
	if(!mapLayer())
	{
		return 0;
	}

	Q_ASSERT(hObj);

	return mapPerimeter( hObj );
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

void MapLineObject::setRscKey(const QString &rscKey)
{
	if(mRscKey == rscKey)
	{
		return;
	}

	mRscKey = rscKey;

	refresh();
}

QPolygonF MapLineObject::planePolygon() const
{
	if(!mapLayer())
	{
		return QPolygonF();
	}

	return helper()->metricsToPlanePolygon(hObj);
}

QPolygonF MapLineObject::picturePolygon() const
{
	if(!mapLayer())
	{
		return QPolygonF();
	}

	return helper()->metricsToPicturePolygon(hObj);
}

void MapLineObject::repaint()
{
	if(!mapLayer())
	{
		return;
	}

	removeFromMap();

	hObj = mapCreateSiteObject(mapLayer()->mapHandle(), mapLayer()->siteHandle());
	mapRegisterObjectByKey( hObj, RscViewer::codec()->fromUnicode(mRscKey).data());

	foreach(Coord c, mCoords)
	{
		Map2::CoordPlane cp = helper()->geoToPlane(c);
		mapAppendPointPlane(hObj, cp.x, cp.y);
	}

	commit();
}

Coord Map2::MapLineObject::coordinateGeo() const
{
	if(!mapLayer())
	{
		return Coord();
	}

	return helper()->objectCenter(hObj);
}

void Map2::MapLineObject::moveBy(double dxPlane, double dyPlane)
{
	if(!mapLayer())
	{
		qDebug()<<"*** LINE OBJECT: Невозможно обработать прямоугольную координату, пока объект не добавлен в слой";
		return;
	}

	DOUBLEPOINT dp;
	dp.x = dxPlane;
	dp.y = dyPlane;

	mapRelocateObjectPlane(hObj, &dp);

	mCoords = helper()->objectGeoCoordinates( hObj );

	commit();
}

QRectF Map2::MapLineObject::sizePix() const
{
	QRectF rect = picturePolygon().boundingRect();
	rect.setX(0);
	rect.setY(0);

	return rect;
}

QList<HOBJ*> MapLineObject::mapHandles()
{
	return QList<HOBJ*>() << &hObj;
}
