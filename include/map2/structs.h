#ifndef STRUCTS
#define STRUCTS

#include <QPoint>
#include <QVariant>

#include "gis.h"

struct CoordPlane;

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

	QString toString() const { return QString("Ш:%0 Д:%1").arg(lat, 0, 'f').arg(lng, 0, 'f'); }
	bool operator ==(const Coord &other) const { return other.lat == lat && other.lng == lng;}

	CoordPlane toPlane(HMAP mapHnd) const;
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


	CoordPlane( const QPointF &point) : x(point.y()), y( point.x()) {}

	QPointF toPointF(){ return QPointF(x, y); }

	QString toString() const { return QString("X:%0 Y:%1").arg(x, 0, 'f').arg(y, 0, 'f'); }
	bool operator ==(const CoordPlane &other) const { return other.x == x && other.y == y;}

	CoordPlane operator+(const CoordPlane &right);
	CoordPlane& operator+=(const CoordPlane &other);

	CoordPlane operator-(const CoordPlane &right);
	CoordPlane& operator-=(const CoordPlane &other);

	Coord toGeo(HMAP mapHnd) const;
};

Q_DECLARE_METATYPE(Coord)
Q_DECLARE_METATYPE(CoordPlane)

#endif // STRUCTS

