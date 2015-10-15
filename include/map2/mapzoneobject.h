#ifndef MAPZONEOBJECT_H
#define MAPZONEOBJECT_H

#include "structs.h"
#include "mapobject.h"

#include <QList>

class MapZoneObject : public MapObject
{
public:
	MapZoneObject(long exCode, QList<CoordPlane> coords = QList<CoordPlane>(), MapLayer *layer = 0);

	void addPoint(CoordPlane coord);
	void addPoint(Coord coord);
	void addPoints(QList<CoordPlane> coords);
	void addPoints(QList<Coord> coords);

	void clear();

	/*!
	 * \brief Возвращает протяженность линии в метрах.
	 */
	double length();

	/*!
	 * \brief Замыкает зону.
	 * Если последняя координата не совпадает с первой, то в конец списка координат будет добавлена копия первой.
	 */
	void closeZone();

private:
	QList<CoordPlane> mCoords;
};

#endif // MAPZONEOBJECT_H
