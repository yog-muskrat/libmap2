#ifndef STRUCTS
#define STRUCTS

#include <QPoint>
#include <QDebug>
#include <QVariant>

#ifndef MAPTYPE_H
typedef long int HMAP;
typedef long int HOBJ;
typedef long int HRSC;
typedef long int HSITE;
typedef long int HSELECT;
#endif

namespace Map2
{

struct CoordPlane;

/*!
 * \brief Координата в формате "градусы + десятая часть"
 * Корректные координаты должны находиться в пределах значений [-90, 90] для широты и [-360, 360] для долготы.
 */
struct Coord
{
	double lat;
	double lng;

	Coord() : lat(0), lng(0) {}
	Coord(double lat, double lng) : lat(lat), lng(lng) {}
	Coord(const Map2::Coord &other) : lat(other.lat), lng(other.lng) {}

	bool isValid() const;

	QString toString() const { return QString("Ш:%0 Д:%1").arg(lat, 0, 'f').arg(lng, 0, 'f'); }

	/*!
	 * \brief Пересчитывает координаты из градусов с минутами.
	 */
	static Coord fromDegreeWithMinutes(const double &lat, const double &lng);
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
	CoordPlane(const Map2::CoordPlane &other) : x(other.x), y(other.y) {}
	explicit CoordPlane( const QPointF &point) : x(point.y()), y( point.x()) {}

	QPointF toPointF(){ return QPointF(x, y); }

	QString toString() const { return QString("X:%0 Y:%1").arg(x, 0, 'f').arg(y, 0, 'f'); }
	bool operator ==(const Map2::CoordPlane &other) const { return other.x == x && other.y == y;}

	CoordPlane operator+(const Map2::CoordPlane &right);
	CoordPlane& operator+=(const Map2::CoordPlane &other);

	CoordPlane operator-(const Map2::CoordPlane &right);
	CoordPlane& operator-=(const Map2::CoordPlane &other);

};

}

inline bool operator==(const Map2::Coord &c1, const Map2::Coord &c2)
{
	return c1.lat == c2.lat && c1.lng == c2.lng;
}

inline uint qHash(const Map2::Coord &coord)
{
	return qHash(coord.toString());
}

Q_DECLARE_METATYPE(Map2::Coord)
Q_DECLARE_METATYPE(Map2::CoordPlane)

#endif // STRUCTS

