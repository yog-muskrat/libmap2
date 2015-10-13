#ifndef MAPTEXTOBJECT_H
#define MAPTEXTOBJECT_H

#include "mapobject.h"
#include "structs.h"

#include "gis.h"

class MapLayer;

class MapTextObject : public MapObject
{
public:
	MapTextObject(MapLayer *layer, QString text = "", CoordPlane coord = CoordPlane(), int exCode = 0);

	QString text() const;
	void setText(const QString &text);

	void setCoordinate(const CoordPlane &coord);

private:
	QString mText;
	CoordPlane mCoord;
};

#endif // MAPTEXTOBJECT_H
