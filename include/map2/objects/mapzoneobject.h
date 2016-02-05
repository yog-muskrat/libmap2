#ifndef MAPZONEOBJECT_H
#define MAPZONEOBJECT_H

#include "mapstructs.h"
#include "mapobject.h"

#include <QList>

namespace Map2 {

class MapZoneObject : public MapObject
{
public:
	MapZoneObject(long rscCode, QList<Map2::CoordPlane> coords = QList<Map2::CoordPlane>(), Map2::MapLayer *layer = 0);

	void addPoint(Map2::CoordPlane coord);
	void addPoint(Map2::Coord coord);
	void addPoints(QList<Map2::CoordPlane> coords);
	void addPoints(QList<Map2::Coord> coords);

	QList<Map2::CoordPlane> points() const {return mCoords;}

	void clear();

	/*!
	 * \brief Возвращает протяженность линии в метрах.
	 */
	double length() const;

	/*!
	 * \brief Замыкает зону.
	 * Если последняя координата не совпадает с первой, то в конец списка координат будет добавлена копия первой.
	 */
	void closeZone() const;

	virtual void setRscCode(long rscCode);

private:
	void clearPoints();
	void appendPoints();

	QList<CoordPlane> mCoords;
};
}
#endif // MAPZONEOBJECT_H
