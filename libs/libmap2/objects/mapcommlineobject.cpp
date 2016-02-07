#include "objects/mapcommlineobject.h"

Map2::MapCommlineObject::MapCommlineObject(const Map2::Coord &from, const Map2::Coord &to, Map2::MapLayer *layer) :
	MapObject(MapObject::MO_Commline, layer),
	mFrom(from),
	mTo(to),
	mColor(Qt::blue),
	mArrowStyle(AS_BothArrows)
{

}

Map2::MapCommlineObject::~MapCommlineObject()
{

}

Map2::MapCommlineObject::ArrowStyle Map2::MapCommlineObject::arrowStyle() const
{
	return mArrowStyle;
}

void Map2::MapCommlineObject::setArrowStyle(const ArrowStyle &arrowStyle)
{
	mArrowStyle = arrowStyle;
}

Map2::Coord Map2::MapCommlineObject::to() const
{
	return mTo;
}

void Map2::MapCommlineObject::setTo(const Map2::Coord &to)
{
	mTo = to;
}

Map2::Coord Map2::MapCommlineObject::from() const
{
	return mFrom;
}

void Map2::MapCommlineObject::setFrom(const Map2::Coord &from)
{
	mFrom = from;
}

QColor Map2::MapCommlineObject::color() const
{
	return mColor;
}

void Map2::MapCommlineObject::setColor(const QColor &color)
{
	mColor = color;
}


