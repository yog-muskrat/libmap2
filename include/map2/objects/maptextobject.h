#ifndef MAPTEXTOBJECT_H
#define MAPTEXTOBJECT_H

#include "mapobject.h"
#include "mapstructs.h"

#include <QColor>

namespace Map2
{

class MapLayer;

class MapTextObject : public MapObject
{
public:
	MapTextObject(Map2::MapLayer *layer, QString text = "", Map2::CoordPlane coord = Map2::CoordPlane(), int fontHeightMm = 4, QColor color = QColor(Qt::black));

	QString text() const;
	void setText(const QString &text);

	void setCoordinate(const Map2::CoordPlane &coord);

	QColor color() const { return mColor; }
	void setColor(const QColor &value);

	int fontHeightMm() const { return mFontHeightMm; }
	void setFontHeightMm(int value);

	virtual void setRscCode(long){}

	virtual QRectF sizePix() const;

private:
	void updateDraw();

	QString mText;
	CoordPlane mCoord;
	int mFontHeightMm;
	QColor mColor;
};
}
#endif // MAPTEXTOBJECT_H
