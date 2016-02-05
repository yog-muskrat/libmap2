#ifndef MAPROTATEACTION
#define MAPROTATEACTION

#include "actions/mapaction.h"

namespace Map2
{

class MapObject;

class MapRotateAction : public MapAction
{
public:
	explicit MapRotateAction(Map2::MapView *view);

	virtual Map2::MapToolBar::Tools type() { return MapToolBar::RotateObject; }
	virtual bool processMousePressEvent(QMouseEvent *mouseEvent);
	virtual bool processMouseMoveEvent(QMouseEvent *mouseEvent);
	virtual bool processMouseReleaseEvent(QMouseEvent *mouseEvent);

private:
	bool mIsDragged;
	QPoint mDragStartPoint;
	MapObject *pObject;
};
}
#endif // MAPROTATEACTION
