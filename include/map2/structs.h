#ifndef STRUCTS
#define STRUCTS

#include <QVariant>

/*!
 * \brief Координата в формате "градусы+десятая часть"
 */
struct Coord
{
	double lat;
	double lng;

	Coord() : lat(0), lng(0) {}
	Coord(double lat, double lng) : lat(lat), lng(lng) {}
	Coord(const Coord &other) : lat(other.lat), lng(other.lng) {}

	QString toString() { return QString("Ш:%0 Д:%1").arg(lat, 0, 'f').arg(lng, 0, 'f'); }
};

/*!
 * \brief Координаты в метрах на местности.
 */
struct CoordPlane
{
	double x;
	double y;

	CoordPlane() : x(0), y(0) {}
	CoordPlane(double x, double y) : x(x), y(y) {}
	CoordPlane(const CoordPlane &other) : x(other.x), y(other.y) {}

	QString toString() { return QString("X:%0 Y:%1").arg(x, 0, 'f').arg(y, 0, 'f'); }
};

Q_DECLARE_METATYPE(Coord)
Q_DECLARE_METATYPE(CoordPlane)

#endif // STRUCTS

