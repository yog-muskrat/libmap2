#ifndef MAPLINEOBJECT_H
#define MAPLINEOBJECT_H

#include "mapobject.h"
#include "mapstructs.h"

#include <QList>
#include <QPolygonF>

namespace Map2
{

class MapLineObject : public MapObject
{
public:
	MapLineObject(const QString &rscKey, const QList<Map2::Coord> &coords = QList<Coord>(), Map2::MapLayer *layer = 0);
	MapLineObject(const QString &rscKey, const QList<Map2::CoordPlane> &coords = QList<CoordPlane>(), Map2::MapLayer *layer = 0);

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

	void setRscKey(const QString &rscKey);

	/*!
	 * \brief Возвращает полигон, точки которого соответствуют прямоугольным координатам объекта.
	 */
	QPolygonF planePolygon() const;
	QPolygonF picturePolygon() const;

private:
	QList<Coord> mCoords;
	QString mRscKey;
	HOBJ hObj;

	// MapObject interface
public:
	virtual Coord coordinateGeo() const;
	virtual void moveBy(double dxPlane, double dyPlane);
	virtual QRectF sizePix() const;

protected:
	virtual void repaint();
	virtual QList<HOBJ*> mapHandles();
};
}
#endif // MAPLINEOBJECT_H
