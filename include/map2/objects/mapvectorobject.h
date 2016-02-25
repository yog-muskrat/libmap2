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
	MapVectorObject(const QString &rscKey, Map2::MapLayer * layer = 0);

	void setCoordinates(Map2::Coord coord);
	void setCoordinates(Map2::CoordPlane coord);

	double rotation() const { return mRotation; }
	void setRotation(double degree);

	void setRscKey(const QString &key);
	virtual void setName(QString name);

private:
	double mRotation;
	QString mRscKey;
	Coord mCoordinate;
	HOBJ hObj;

	// MapObject interface
public:
	virtual QRectF sizePix() const;
	virtual Coord coordinateGeo() const {return mCoordinate;}
	virtual void moveBy(double dxPlane, double dyPlane);

protected:
	virtual void repaint();
	virtual QList<HOBJ *> mapHandles();
};
}
#endif // MAPVECTOROBJECT_H
