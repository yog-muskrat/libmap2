#ifndef MAPRECTZOOMACTION
#define MAPRECTZOOMACTION

#include "actions/mapaction.h"

namespace Map2
{

/*!
 * \brief Класс действия по приближению участка карты.
 */
class MapRectZoomAction : public MapAction
{
public:
	explicit MapRectZoomAction(Map2::MapView *view);
	~MapRectZoomAction() {}

	virtual Map2::MapToolBar::Tools type() { return MapToolBar::RectZoom; }
	virtual bool processMousePressEvent(QMouseEvent *mouseEvent);
	virtual bool processMouseReleaseEvent(QMouseEvent *mouseEvent);
	virtual bool processMouseMoveEvent(QMouseEvent *mouseEvent);

private:
	bool mIsDragged;
	QPoint mDragStartPoint;
};
}

#endif // MAPRECTZOOMACTION
