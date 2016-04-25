#include "objects/mapvectorobject.h"
#include "mapview.h"
#include "maplayer.h"
#include "maphelper.h"
#include "rscviewer.h"

#include "gis.h"

#include <QRect>
#include <QDebug>
#include <QLineF>
#include <qmath.h>
#include <QTextCodec>

using namespace Map2;


MapVectorObject::MapVectorObject(const QString &rscKey, MapLayer *layer) :
	MapObject(MO_Vector, layer),
	mRotation(0),
	mRscKey(rscKey),
	hObj(0),
	mUseRotation(false)
{
	if(pLayer)
	{
		hObj = mapCreateSiteObject(mapLayer()->mapHandle(), mapLayer()->siteHandle());
		mapRegisterObjectByKey(hObj, RscViewer::codec()->fromUnicode(mRscKey).data());

		mapAppendPointPlane(hObj, 0, 0);
		mapAppendPointPlane(hObj, 0, 0);

		commit();

		show();
	}
}

void MapVectorObject::setCoordinates(Map2::Coord coord)
{
	if(mCoordinate == coord)
	{
		return;
	}

	mCoordinate = coord;

	if(!mapLayer())
	{
		return;
	}

	if(!helper())
	{
		qDebug()<<"*** MAPOBJECT: Невозможно задать координаты объекта, т.к. MapHelper недоступен.";
		return;
	}
	CoordPlane cp = helper()->geoToPlane(mCoordinate);

	mapUpdatePointPlane(hObj, cp.x, cp.y, 1);

	setRotation( rotation() );
}

void MapVectorObject::setCoordinates(Map2::CoordPlane coord)
{
	if(!mapLayer())
	{
		qDebug()<<"*** MAPOBJECT: Невозможно задать прямоугольные координаты, пока объект не добавлен на карту.";
		return;
	}

	Map2::MapHelper *helper = mapLayer()->mapView()->helper();
	setCoordinates( helper->planeToGeo( coord ) );
}

QRectF MapVectorObject::sizePix() const
{
	if(!mapLayer())
	{
		return QRect();
	}

	Map2::MapHelper *helper = mapLayer()->mapView()->helper();

	HRSC hRsc = mapGetRscIdent(mapLayer()->mapHandle(), mapLayer()->siteHandle());
	int rscInCode = mapGetRscObjectKeyIncode(hRsc, RscViewer::codec()->fromUnicode(mRscKey).data());

	IMAGESIZE imagesize;
	mapGetRscImageSize(hRsc, rscInCode, &imagesize);

	double x = helper->mkm2px( imagesize.DeltaH );
	double y = helper->mkm2px( imagesize.DeltaV );
	double w = helper->mkm2px( imagesize.HorizontalSize );
	double h = helper->mkm2px( imagesize.VerticalSize );

	return QRectF(x, y, w, h);
}

void MapVectorObject::setRotation(double degree)
{
	mRotation = degree;

	QPointF firstPoint = coordinatePlane().toPointF();

	if(mUseRotation)
	{
		QLineF line( firstPoint.y(), firstPoint.x(), firstPoint.y() + 100, firstPoint.x() );
		qreal lineAngle = fmod(-mRotation + 90. + 360., 360.);
		line.setAngle( -lineAngle );

		CoordPlane cp(line.p2().y(), line.p2().x() );
		mapUpdatePointPlane(hObj, cp.x, cp.y, 2);
	}
	else
	{
		double x = mapXPlane(hObj);
		double y = mapYPlane(hObj);
		mapUpdatePointPlane(hObj, x, y, 2);
	}

	commit();
}

void MapVectorObject::setRotationUse(bool use)
{
	mUseRotation = use;

	setRotation(mRotation);
}

void MapVectorObject::setRscKey(const QString &key)
{
	if(mRscKey == key)
	{
		return;
	}

	mRscKey = key;
	refresh();
}

void MapVectorObject::setName(QString name)
{
	if(!mapLayer())
	{
		MapObject::setName(name);
		return;
	}

	mName = name;

	setNameVisible( isNameVisible() );
}

void MapVectorObject::setNameVisible(bool visible)
{
	mNameVisible = visible;

	if(visible)
	{
		QTextCodec *tc = RscViewer::codec();
		mapAppendSemantic( hObj, 33334, tc->fromUnicode(name()).data(), name().size());
	}
	else
	{
		int number = mapSemanticNumber(hObj, 33334);
		if(number > 0)
		{
			mapDeleteSemantic(hObj, number);
		}
	}

	commit();
}

void MapVectorObject::repaint()
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
	mapRegisterObjectByKey(hObj, RscViewer::codec()->fromUnicode(mRscKey).data());

	CoordPlane coord = coordinatePlane();

	mapAppendPointPlane(hObj, coord.x, coord.y);
	mapAppendPointPlane(hObj, coord.x, coord.y);

	setRotation(mRotation);

	commit();
}

void Map2::MapVectorObject::moveBy(double dxPlane, double dyPlane)
{
	if(!mapLayer())
	{
		return;
	}

	DOUBLEPOINT dp;
	dp.x = dxPlane;
	dp.y = dyPlane;

	mapRelocateObjectPlane(hObj, &dp);

	mCoordinate = helper()->objectGeoCoordinates( hObj ).first();

	commit();
}

QList<HOBJ *> Map2::MapVectorObject::mapHandles()
{
	return QList<HOBJ*>() << &hObj;
}
