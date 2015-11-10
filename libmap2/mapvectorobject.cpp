#include "mapvectorobject.h"
#include "maplayer.h"
#include "maphelper.h"

#include "qmath.h"
#include <QDebug>
#include <qline.h>

MapVectorObject::MapVectorObject(long rscCode, MapLayer *layer)
	: MapObject(MO_Vector, layer), mRotation(0), mCoord( CoordPlane() )
{
	mapAppendPointPlane(handle(), 0, 0);
	mapAppendPointPlane(handle(), 0, 0);
	mapRegisterObject(handle(), rscCode, LOCAL_VECTOR);

	commit();

	setRotation(0);

	commit();
}

void MapVectorObject::setCoordinates(Coord coord)
{
	if(handle() <= 0)
	{
		return;
	}

	setCoordinates(coord.toPlane( mapLayer()->mapHandle() ));
}

void MapVectorObject::setCoordinates(CoordPlane coord)
{
	if(mCoord == coord)
	{
		return;
	}

	mCoord = coord;

	updateMetric(1, mCoord);
	setRotation( rotation() );
}

Coord MapVectorObject::coordinatesGeo()
{
	return mCoord.toGeo( mapLayer()->mapHandle() );
}

CoordPlane MapVectorObject::coordinatesPlane()
{
	return mCoord;
}

double MapVectorObject::planeX()
{
	return mCoord.x;
}

double MapVectorObject::planeY()
{
	return mCoord.y;
}

double MapVectorObject::lat()
{
	return mCoord.toGeo( mapLayer()->mapHandle() ).lat;
}

double MapVectorObject::lng()
{
	return mCoord.toGeo( mapLayer()->mapHandle() ).lng;
}

void MapVectorObject::setRotation(double degree)
{
	mRotation = degree;

	QPointF firstPoint = mCoord.toPointF();

	QLineF line( firstPoint.y(), firstPoint.x(), firstPoint.y() + 1000, firstPoint.x() );
	qreal lineAngle = fmod(-mRotation + 90. + 360., 360.);
	line.setAngle( -lineAngle );
	updateMetric(2, CoordPlane( line.p2().y(), line.p2().x() ) );

	commit();
}
