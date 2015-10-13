#include "maptextobject.h"

#include <QTextCodec>

MapTextObject::MapTextObject(MapLayer *layer, QString text, CoordPlane coord, int exCode)
	: MapObject(MO_Text, layer), mText(text), mCoord(coord)
{
	// 1373
	mapAppendPointPlane(handle(), 0, 0);
	mapRegisterObject(handle(), exCode, LOCAL_TITLE);
	commit();
}
QString MapTextObject::text() const
{
	return mText;
}

void MapTextObject::setText(const QString &text)
{
	mText = text;

	QTextCodec *tc = QTextCodec::codecForName("koi8-r");

	mapPutText(handle(), tc->fromUnicode(mText).constData(), 0);
	commit();
}

void MapTextObject::setCoordinate(const CoordPlane &coord)
{
	mCoord = coord;

	mapUpdatePointPlane(handle(), coord.x, coord.y, 1);
	commit();
}


