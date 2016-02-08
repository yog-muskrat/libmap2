#ifndef MAPFORMULARGROUP_H
#define MAPFORMULARGROUP_H

#include "map2/mapstructs.h"
#include "map2/groups/mapgroup.h"

#include <QMap>
#include <QList>
#include <QColor>

namespace Map2
{
class MapVectorObject;
class MapTextObject;

class MapFormularGroup : public MapGroup
{
public:
	MapFormularGroup(Map2::MapVectorObject *parent, QColor borderColor = QColor(Qt::black));
	~MapFormularGroup();

	virtual MapGroup::Type type() const { return MapGroup::MG_Formular; }

	virtual bool addChild(MapObject *child);
	virtual void setChildrenVisible(bool visible);

	QPoint offset() const { return mOffset; }
	void setOffset(const QPoint &offset);

	double borderWidthPx() const { return mBorderWidthPx; }
	void setBorderWidthPx(double value);

	double paddingPx() const { return mPaddingPx; }
	void setPaddingPx(double value);

	double spacingPx() const { return mSpacingPx; }
	void setSpacingPx(double value);

protected:
	virtual void updateChildrenDisplayCoordinates();
	virtual void restoreInitialChildrenCoordinates();

private:
	void updateBorderCoords(const QRectF newRect);
	void createBorderObject();
	MapVectorObject * vectorParent();

	double mBorderWidthPx;
	double mPaddingPx;
	double mSpacingPx;

	/// Временное решение. В последствии нужно добавить в сам MapObject понятия "Реальная координата" и "Отображаемая координата".
	QMap<MapObject*, CoordPlane> mInitialCoordinates;
	QMap<MapObject*, MapTextObject*> mObjectsLabels;

	QPoint mOffset; /// Сдвиг формуляра относительно родительского объекта, px.
	QColor mBorderColor; /// Цвет рамки формуляра
	HOBJ hObj; /// Дескриптор объекта-рамки.
};
}
#endif // MAPFORMULARGROUP_H
