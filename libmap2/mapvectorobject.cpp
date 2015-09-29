#include "mapvectorobject.h"
#include "maplayer.h"

#include "qmath.h"
#include <QDebug>

MapVectorObject::MapVectorObject(long rscCode, MapLayer *layer) : MapObject(MO_Vector, layer)
{
	mObjHandle = mapCreateSiteObject(mapLayer()->mapHandle(), mapLayer()->siteHandle(), 1, IDFLOAT2 );

	mapRegisterObject(mObjHandle, rscCode, LOCAL_VECTOR);
	mapAppendPointPlane(mObjHandle, 0, 0);
	mapAppendPointPlane(mObjHandle, 0, 100);
	mapCommitObject(mObjHandle );
//	mapFreeObject(mObjHandle);
}


void MapVectorObject::setCoordinates(Coord coord)
{
	if(!mObjHandle > 0)
	{
		return;
	}

	double b = coord.lat * M_PI / 180.;
	double l = coord.lng * M_PI / 180.;

	mapUpdatePointGeo(mObjHandle, b, l, 1);
	mapUpdatePointGeo(mObjHandle, b, l, 2);
	mapCommitObject(mObjHandle);
}

void MapVectorObject::setCoordinates(CoordPlane coord)
{
}

Coord MapVectorObject::coordinatesGeo()
{
	return Coord();
}

CoordPlane MapVectorObject::coordinatesPlane()
{
	return CoordPlane();
}

double MapVectorObject::planeX()
{
	return -1.;
}

double MapVectorObject::planeY()
{
	return -1.;
}

double MapVectorObject::lat()
{
	return -1.;
}

double MapVectorObject::lng()
{
	return -1.;
}

double MapVectorObject::rotation() const
{

}

void MapVectorObject::setRotation(double degree)
{

}
