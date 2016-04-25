#ifndef MAPFORMULARGROUP_H
#define MAPFORMULARGROUP_H

#include "map2/mapstructs.h"
#include "map2/groups/mapgroup.h"

#include <QMap>
#include <QList>
#include <QRectF>
#include <QColor>

namespace Map2
{
class MapLayer;
class MapTextObject;
class MapVectorObject;

class MapFormularGroup : public MapGroup
{
public:
	MapFormularGroup(Map2::MapVectorObject *parent, QColor borderColor = QColor(Qt::black));
	~MapFormularGroup();

	virtual Map2::MapGroup::Type type() const { return MapGroup::MG_Formular; }

	virtual bool addChild(MapObject *child);
	virtual void setChildrenVisible(bool visible);

	void moveBy(const QPoint &offset);

	double borderWidthPx() const { return mBorderWidthPx; }
	void setBorderWidthPx(double value);

	double paddingPx() const { return mPaddingPx; }
	void setPaddingPx(double value);

	double spacingPx() const { return mSpacingPx; }
	void setSpacingPx(double value);

	Map2::Coord formularCoordinate() const;
	void setFormularCoordinate(Map2::Coord coord);

protected:
	virtual void updateChildrenDisplayCoordinates();

private:
	void restoreInitialChildrenCoordinates();

	void arrangeChildren();
	void updateBorderCoords();
	void updateStrutCoords();

	void createBorderObject();
	MapVectorObject * vectorParent();
	HOBJ createText(MapLayer *layer, Coord coordinate, const QString &text);
	QRectF textRect(HOBJ hobj) const;

	double mBorderWidthPx;
	double mPaddingPx;
	double mSpacingPx;

	/// Временное решение. В последствии нужно добавить в сам MapObject понятия "Реальная координата" и "Отображаемая координата".
	QMap<MapObject*, Coord> mInitialCoordinates;
	QMap<MapObject*, HOBJ> mObjectsLabels;

	Qt::Alignment formularAlignment() const;
	CoordPlane mBottomLeft;
	CoordPlane mBottomRight;
	CoordPlane mTopLeft;
	CoordPlane mTopRight;
//	QRect mRect;

	Coord mFormularCoord;

	QColor mBorderColor; /// Цвет рамки формуляра
	HOBJ rectHobj; /// Дескриптор объекта-рамки.
	HOBJ strutHobj; /// Дескриптор выносной линии.
};
}
#endif // MAPFORMULARGROUP_H
