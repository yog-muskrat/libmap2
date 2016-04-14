#ifndef MAPHELPER_H
#define MAPHELPER_H

#include <QColor>
#include <QPoint>
#include <QPolygonF>

#include "mapstructs.h"

namespace Map2
{

/*!
 * \brief Набор вспомогательных функций для работы с картой.
 */
class MapHelper
{
public:
	MapHelper(HMAP hMap, double mkmInPix = 300.) : mMapHnd(hMap), mMkmInPx(mkmInPix){}
	~MapHelper(){mMapHnd = 0;}

	/*!
	 * \brief Переводит радианы в градусы.
	 */
	static double radToDegree(const double &rad);

	/*!
	 * \brief Переводит градусы в радианы.
	 */
	static double degreeToRad(const double &degree);

	/*!
	 * \brief Преобразует координаты из метров в градусы.
	 */
	Coord planeToGeo(const Map2::CoordPlane &coordPlane) const;

	/*!
	 * \brief Преобразует координаты из градусов в метры.
	 */
	CoordPlane geoToPlane(const Map2::Coord &coord) const;

	/*!
	 * \brief Преобразует координаты из метров в пиксели.
	 */
	QPoint planeToPicture(const Map2::CoordPlane &coord) const;

	/*!
	 * \brief Преобразует координаты из градусов в пиксели.
	 */
	QPoint geoToPicture(const Map2::Coord &coord) const;

	/*!
	 * \brief Преобразует координаты из пикселей в метры.
	 */
	CoordPlane pictureToPlane(const QPoint &point) const;

	/*!
	 * \brief Преобразует координаты из пикселей в градусы.
	 */
	Coord pictureToGeo(const QPoint &point) const;

	/*!
	 * \brief Возвращает расстояние между двумя точками в метрах
	 */
	qreal distance(Map2::Coord c1, Map2::Coord c2) const;
	qreal distance(Map2::CoordPlane c1, Map2::CoordPlane c2) const;

	qreal distancePx(Map2::Coord c1, Map2::Coord c2) const;

	double bearing(const Map2::CoordPlane &pointFrom, const Map2::CoordPlane &pointTo) const;

	Coord center(const Coord &coord1, const Coord &coord2) const;

	/*!
	 * \brief Преобразует микроны в пиксели
	 */
	double mkm2px(double mkm) const;

	/*!
	 * \brief Преобразует пиксели в микроны
	 */
	double px2mkm(double pix) const;

	void setMkmInPxRatio(double mkmInPx) {mMkmInPx = mkmInPx;}

	static bool clearMetrics(HOBJ hObj);
	static void clearHandle(HOBJ *hObj);
	static bool commitByOrder(HOBJ hObj);
	static bool removeObject(HOBJ hObj);
	static bool commitObject(HOBJ hObj);
	static long objectMapKey(HOBJ hObj);
	static void setSelected(HOBJ hObj, QColor c = QColor(Qt::yellow) );
	static void addObjectToSelection(HSELECT select, HOBJ obj);
	static void removeObjectFromSelection(HSELECT select, HOBJ hObj);

	Coord objectCenter(HOBJ hObj);

	static QPolygonF metricsToPlanePolygon(HOBJ hObj);
	static QPolygonF metricsToPicturePolygon(HOBJ hObj);
	QList<Coord> objectGeoCoordinates(HOBJ hObj) const;

private:
	HMAP mMapHnd;
	double mMkmInPx; /// Разрешение экрана микрон/пиксель.
};

}
#endif // MAPHELPER_H
