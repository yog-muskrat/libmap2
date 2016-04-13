#ifndef MAPZONEOBJECT_H
#define MAPZONEOBJECT_H

#include "map2/mapstructs.h"
#include "map2/objects/mapobject.h"

#include <QList>
#include <QPolygon>

namespace Map2 {

class MapZoneObject : public MapObject
{
public:
	MapZoneObject(const QString &rscKey, QList<Map2::Coord> coords = QList<Map2::Coord>(), Map2::MapLayer *layer = 0);

	void addPoint(Map2::Coord coord);
	void addPoint(Map2::CoordPlane coord);
	void addPoints(QList<Map2::Coord> coords);
	void addPoints(QList<Map2::CoordPlane> coords);

	QList<Map2::Coord> points() const {return mCoords;}

	/*!
	 * \brief Возвращает протяженность линии в метрах.
	 */
	double length() const;

	/*!
	 * \brief Замыкает зону.
	 * Если последняя координата не совпадает с первой, то в конец списка координат будет добавлена копия первой.
	 */
	void closeZone() const;

	void setRscKey(const QString &rscKey);

	QPolygonF toPicturePolygon() const;
	QPolygonF toPlanePolygon() const;

private:
	QList<Coord> mCoords;
	QString mRscKey;
	HOBJ hObj;

	// MapObject interface
public:
	virtual Coord coordinateGeo() const;
	virtual void moveBy(double dxPlane, double dyPlane);

protected:
	void updateCoordinates();

	virtual void repaint();
	virtual QList<HOBJ *> mapHandles();
};
}
#endif // MAPZONEOBJECT_H
