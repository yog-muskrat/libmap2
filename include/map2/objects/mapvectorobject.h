#ifndef MAPVECTOROBJECT_H
#define MAPVECTOROBJECT_H

#include "mapobject.h"
#include "map2/mapstructs.h"

#include <QString>

namespace Map2
{

class MapVectorObject : public MapObject
{
public:
	MapVectorObject(long code = -1, Map2::MapLayer * layer = 0);

	void setCoordinates(Map2::Coord coord);
	void setCoordinates(Map2::CoordPlane coord);
	Map2::Coord coordinatesGeo() const;
	Map2::CoordPlane coordinatesPlane() const;
	double planeX() const;
	double planeY() const;
	double lat() const;
	double lng() const;

	virtual QRectF sizePix() const;

	double rotation() const { return mRotation; }
	void setRotation(double degree);

	virtual void setRscCode(long code);
	virtual void setName(QString name);

private:
	double mRotation;
};
}
#endif // MAPVECTOROBJECT_H
