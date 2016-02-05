#include "objects/mapvectorobject.h"
#include "maplayer.h"
#include "maphelper.h"
#include "mapview.h"

#include "gis.h"

#include <qmath.h>
#include <QDebug>
#include <QLineF>
#include <QRect>
#include <QTextCodec>

using namespace Map2;

MapVectorObject::MapVectorObject(long code, Map2::MapLayer *layer)
	: MapObject(MO_Vector, layer, code), mRotation(0)
{
	mapAppendPointPlane(handle(), 0, 0);
	mapAppendPointPlane(handle(), 0, 0);
	mapRegisterObject(handle(), rscCode(), LOCAL_VECTOR);
	commit();
}

void MapVectorObject::setCoordinates(Map2::Coord coord)
{
	if(!mapLayer())
	{
		qDebug()<<"*** MapVectorObject: Невозможно обработать координату, пока объект не добавлен в слой";
		return;
	}

	Map2::MapHelper *helper = mapLayer()->mapView()->helper();

	setCoordinates( helper->geoToPlane( coord ) );
}

void MapVectorObject::setCoordinates(Map2::CoordPlane coord)
{
	if(coordinatesPlane() == coord)
	{
		return;
	}

	updateMetric(1, coord);
	setRotation( rotation() );
}

Map2::Coord MapVectorObject::coordinatesGeo() const
{
	if(!mapLayer())
	{
		qDebug()<<"*** MapVectorObject: Невозможно обработать координату, пока объект не добавлен в слой";
		return Map2::Coord();
	}

	Map2::MapHelper *helper = mapLayer()->mapView()->helper();

	return helper->planeToGeo( coordinatesPlane() );
}

Map2::CoordPlane MapVectorObject::coordinatesPlane() const
{
	double x = mapXPlane( handle(), 1);
	double y = mapYPlane( handle(), 1);

	return CoordPlane(x, y);
}

double MapVectorObject::planeX() const
{
	return coordinatesPlane().x;
}

double MapVectorObject::planeY() const
{
	return coordinatesPlane().y;
}

double MapVectorObject::lat() const
{
	if(!mapLayer())
	{
		qDebug()<<"*** MapVectorObject: Невозможно обработать координату, пока объект не добавлен в слой";
		return 0;
	}

	Map2::MapHelper *helper = mapLayer()->mapView()->helper();

	return helper->planeToGeo( coordinatesPlane() ).lat;
}

double MapVectorObject::lng() const
{
	if(!mapLayer())
	{
		qDebug()<<"*** MapVectorObject: Невозможно обработать координату, пока объект не добавлен в слой";
		return 0;
	}

	Map2::MapHelper *helper = mapLayer()->mapView()->helper();

	return helper->planeToGeo( coordinatesPlane() ).lng;
}

QRectF MapVectorObject::sizePix() const
{
	if(!mapLayer())
	{
		qDebug()<<"*** MapVectorObject: Невозможно расчитать развер, пока объект не добавлен в слой";
		return QRect();
	}

	Map2::MapHelper *helper = mapLayer()->mapView()->helper();

	HRSC hRsc = mapGetRscIdent(mapLayer()->mapHandle(), mapLayer()->siteHandle());
	int rscInCode = mapGetRscObjectCodeByNumber(hRsc, rscCode(), LOCAL_VECTOR);

	IMAGESIZE imagesize;
	mapGetRscImageSize(hRsc, rscInCode, &imagesize);

	double x = helper->mkm2pix( imagesize.DeltaH );
	double y = helper->mkm2pix( imagesize.DeltaV );
	double w = helper->mkm2pix( imagesize.HorizontalSize );
	double h = helper->mkm2pix( imagesize.VerticalSize );

	return QRectF(x, y, w, h);
}

void MapVectorObject::setRotation(double degree)
{
	mRotation = degree;

	QPointF firstPoint = coordinatesPlane().toPointF();

	QLineF line( firstPoint.y(), firstPoint.x(), firstPoint.y() + 100, firstPoint.x() );
	qreal lineAngle = fmod(-mRotation + 90. + 360., 360.);
	line.setAngle( -lineAngle );
	updateMetric(2, CoordPlane( line.p2().y(), line.p2().x() ) );

	commit();
}

void MapVectorObject::setRscCode(long code)
{
	if(mRscCode == code || code <= 0)
	{
		return;
	}

	mRscCode = code;

	CoordPlane coord = coordinatesPlane();

	mapDeleteObject( handle() );
	mapCommitObject( handle() );
	mapFreeObject( handle() );

	mObjHandle = mapCreateSiteObject(mapLayer()->mapHandle(), mapLayer()->siteHandle(), 1, IDFLOAT2 );
	mapAppendPointPlane(handle(), 0, 0);
	mapAppendPointPlane(handle(), 0, 0);
	mapRegisterObject(handle(), rscCode(), LOCAL_VECTOR);
	setCoordinates( coord );
}

void MapVectorObject::setName(QString name)
{
	if(name == mName)
	{
		return;
	}

	MapObject::setName(name);

	if(name.isEmpty())
	{
		int number = mapSemanticNumber(handle(), 33334);
		if(number > 0)
		{
			number<<mapDeleteSemantic(handle(), number);
		}
	}
	else
	{
		QTextCodec *tc = QTextCodec::codecForName("koi8-r");
		mapAppendSemantic( handle(), 33334, tc->fromUnicode(name).data(), 100);
	}
	commit();
}
