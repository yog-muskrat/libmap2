#ifndef MAPHELPER_H
#define MAPHELPER_H

#include <QPoint>
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

private:
	HMAP mMapHnd;
	double mMkmInPx; /// Разрешение экрана микрон/пиксель.
};

}
#endif // MAPHELPER_H
