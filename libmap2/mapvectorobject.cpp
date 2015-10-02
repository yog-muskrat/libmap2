#include "mapvectorobject.h"
#include "maplayer.h"
#include "maptools.h"

#include "qmath.h"
#include <QDebug>

MapVectorObject::MapVectorObject(long rscCode, MapLayer *layer)
	: MapObject(MO_Vector, layer), mRotation(0), mCoords( CoordPlane() )
{
	mapRegisterObject(mObjHandle, rscCode, LOCAL_VECTOR);
	mapAppendPointPlane(mObjHandle, 0, 0);
	mapAppendPointPlane(mObjHandle, 0, 0);
	mapCommitObject(mObjHandle );
}


void MapVectorObject::setCoordinates(Coord coord)
{
	if(!mObjHandle > 0)
	{
		return;
	}

	double b =  MapTools::degreeToRad( coord.lat );
	double l = MapTools::degreeToRad( coord.lng );

	mapUpdatePointGeo(mObjHandle, b, l, 1);
	mapUpdatePointGeo(mObjHandle, b, l, 2);
	mapCommitObject(mObjHandle);
}

void MapVectorObject::setCoordinates(CoordPlane coord)
{
	if(mCoords == coord)
	{
		return;
	}

	DOUBLEPOINT delta;

	delta.x = mCoords.x - coord.x;
	delta.y = mCoords.y - coord.y;

	mCoords = coord;

	mapRelocateObjectPlane(mObjHandle, &delta);
	mapCommitObject(mObjHandle);
}

Coord MapVectorObject::coordinatesGeo()
{
	return Coord();
}

CoordPlane MapVectorObject::coordinatesPlane()
{
	mCoords;
}

double MapVectorObject::planeX()
{
	mCoords.x;
}

double MapVectorObject::planeY()
{
	mCoords.y;
}

double MapVectorObject::lat()
{
	Q_ASSERT(mapLayer());

	double x = mCoords.x;
	double y = mCoords.y;

	mapPlaneToGeo(mapLayer()->mapHandle(), &x, &y);

	return MapTools::radToDegree( x );
}

double MapVectorObject::lng()
{
	Q_ASSERT(mapLayer());

	double x = mCoords.x;
	double y = mCoords.y;

	mapPlaneToGeo(mapLayer()->mapHandle(), &x, &y);

	return MapTools::radToDegree( y );
}

void MapVectorObject::setRotation(double degree)
{
	if(degree == mRotation)
	{
		return;
	}

	DOUBLEPOINT point;
	point.x = mapXPlane(mObjHandle);
	point.y = mapYPlane(mObjHandle);

	double delta = MapTools::degreeToRad( degree - mRotation );

	mapRotateObject(mObjHandle, &point , &delta);
}
