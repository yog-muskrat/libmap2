#ifndef MAPTOOLS_H
#define MAPTOOLS_H

#include <QPoint>
#include "structs.h"

#include "gis.h"

/*!
 * \brief Набор вспомогательных функций для работы с картой.
 */
namespace MapTools
{
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
	Coord planeToGeo(HMAP mapHnd, const CoordPlane &coordPlane);

	/*!
	 * \brief Преобразует координаты из градусов в метры.
	 */
	CoordPlane geoToPlane(HMAP mapHnd, const Coord &coord);

	/*!
	 * \brief Преобразует координаты из метров в пиксели.
	 */
	QPoint planeToPicture(HMAP mapHnd, const CoordPlane &coord);

	/*!
	 * \brief Преобразует координаты из градусов в пиксели.
	 */
	QPoint geoToPicture(HMAP mapHnd, const Coord &coord);

	/*!
	 * \brief Преобразует координаты из пикселей в метры.
	 */
	CoordPlane pictureToPlane(HMAP mapHnd, const QPoint &point);

	double bearing(const CoordPlane &pointFrom, const CoordPlane &pointTo);
}

#endif // MAPTOOLS_H
