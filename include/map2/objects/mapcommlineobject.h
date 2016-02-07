#ifndef MAPCOMMLINEOBJECT_H
#define MAPCOMMLINEOBJECT_H

#include "map2/objects/mapobject.h"

#include <QColor>

namespace Map2
{
class MapCommlineObject : public MapObject
{
public:
	enum ArrowStyle
	{
		AS_NoArrows,
		AS_StartArrow,
		AS_EndArrow,
		AS_BothArrows
	};

	MapCommlineObject(const Map2::Coord &from, const Map2::Coord &to, Map2::MapLayer * layer = 0);
	~MapCommlineObject();

	// MapObject interface
	virtual void setRscCode(long rscCode) {}

	QColor color() const;
	void setColor(const QColor &color);

	Map2::Coord from() const;
	void setFrom(const Map2::Coord &from);

	Map2::Coord to() const;
	void setTo(const Map2::Coord &to);

	Map2::MapCommlineObject::ArrowStyle arrowStyle() const;
	void setArrowStyle(const Map2::MapCommlineObject::ArrowStyle &arrowStyle);

private:
	Coord mFrom;
	Coord mTo;
	QColor mColor;
	ArrowStyle mArrowStyle;
};
}

#endif // MAPCOMMLINEOBJECT_H
