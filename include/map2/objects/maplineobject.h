#ifndef MAPLINEOBJECT_H
#define MAPLINEOBJECT_H

#include "mapobject.h"
#include "mapstructs.h"

#include <QList>

namespace Map2
{

class MapLineObject : public MapObject
{
public:
	MapLineObject(long rscCode, Map2::MapLayer *layer = 0, const QList<Map2::CoordPlane> &coords = QList<CoordPlane>());

	void addPoint(const CoordPlane &coord);
	void addPoint(const Coord &coord);
	void addPoints(const QList<CoordPlane> &coords);
	void addPoints(const QList<Coord> &coords);

	void clear();

	/*!
	 * \brief Возвращает протяженность линии в метрах.
	 */
	double length() const;

	/*!
	 * \brief Возвращает протяженность линии в текстовом виде.
	 * Значение будет приведено к максимально компактному виду (м, км, тыс. км и т.д.)
	 */
	QString lengthText() const;

	virtual void setRscCode(long rscCode);

private:
	QList<CoordPlane> mCoords;
};
}
#endif // MAPLINEOBJECT_H
