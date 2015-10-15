#ifndef MAPLINEOBJECT_H
#define MAPLINEOBJECT_H

#include "mapobject.h"
#include "structs.h"

#include <QList>

class MapLineObject : public MapObject
{
public:
	MapLineObject(long exCode, MapLayer *layer = 0, QList<CoordPlane> coords = QList<CoordPlane>());

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
	 * \brief Возвращает протяженность линии в текстовом виде.
	 * Значение будет приведено к максимально компактному виду (м, км, тыс. км и т.д.)
	 */
	QString lengthText();

private:
	QList<CoordPlane> mCoords;
};

#endif // MAPLINEOBJECT_H
