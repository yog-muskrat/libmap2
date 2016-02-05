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
	double radToDegree(const double &rad);

	/*!
	 * \brief Переводит градусы в радианы.
	 */
	double degreeToRad(const double &degree);

	/*!
	 * \brief Преобразует координаты из метров в градусы.
	 */
	Coord planeToGeo(const Map2::CoordPlane &coordPlane);

	/*!
	 * \brief Преобразует координаты из градусов в метры.
	 */
	CoordPlane geoToPlane(const Map2::Coord &coord);

	/*!
	 * \brief Преобразует координаты из метров в пиксели.
	 */
	QPoint planeToPicture(const Map2::CoordPlane &coord);

	/*!
	 * \brief Преобразует координаты из градусов в пиксели.
	 */
	QPoint geoToPicture(const Map2::Coord &coord);

	/*!
	 * \brief Преобразует координаты из пикселей в метры.
	 */
	CoordPlane pictureToPlane(const QPoint &point);

	/*!
	 * \brief Преобразует координаты из пикселей в градусы.
	 */
	Coord pictureToGeo(const QPoint &point);

	double bearing(const Map2::CoordPlane &pointFrom, const Map2::CoordPlane &pointTo);

	Coord center(const Coord &coord1, const Coord &coord2);

	/*!
	 * \brief Преобразует микроны в пиксели
	 */
	double mkm2pix(double mkm);

	/*!
	 * \brief Преобразует пиксели в микроны
	 */
	double pix2mkm(double pix);

private:
	HMAP mMapHnd;
	double mMkmInPx; /// Разрешение экрана микрон/пиксель.
};

}
#endif // MAPHELPER_H
