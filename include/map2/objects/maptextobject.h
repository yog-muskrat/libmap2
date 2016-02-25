#ifndef MAPTEXTOBJECT_H
#define MAPTEXTOBJECT_H

#include "map2/objects/mapobject.h"
#include "map2/mapstructs.h"

#include <QColor>

namespace Map2
{

class MapLayer;

class MapTextObject : public MapObject
{
public:
	MapTextObject(QString text = "", Map2::CoordPlane coord = Map2::CoordPlane(), int fontHeightMm = 4, QColor color = QColor(Qt::black), Map2::MapLayer *layer = 0);
	MapTextObject(QString text = "", Map2::Coord coord = Map2::Coord(), int fontHeightMm = 4, QColor color = QColor(Qt::black), Map2::MapLayer *layer = 0);

	QString text() const;
	void setText(const QString &text);

	void setCoordinatePlane(const Map2::CoordPlane &coord);
	void setCoordinateGeo(const Map2::Coord &coord);

	QColor color() const { return mColor; }
	void setColor(const QColor &value);

	int fontHeightMm() const { return mFontHeightMm; }
	void setFontHeightMm(int value);

	virtual QRectF sizePix() const;

private:
	void updateDraw();

	QString mText;
	Coord mCoord;
	int mFontHeightMm;
	QColor mColor;

	HOBJ hObj;

	// MapObject interface
public:
	virtual Coord coordinateGeo() const {return mCoord;}
	virtual void moveBy(double dxPlane, double dyPlane);

protected:
	virtual void repaint();
	virtual QList<HOBJ *> mapHandles();
};
}
#endif // MAPTEXTOBJECT_H
