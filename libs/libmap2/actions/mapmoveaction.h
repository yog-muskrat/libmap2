#ifndef MAPMOVEACTION
#define MAPMOVEACTION

#include "actions/mapaction.h"

namespace Map2
{

/*!
 * \brief Класс действия по перемещению объекта/
 */
class MapMoveAction : public MapAction
{
public:
	explicit MapMoveAction(Map2::MapView *view);

	virtual Map2::MapToolBar::Tools type() { return MapToolBar::MoveObject; }

	virtual bool processMousePressEvent(QMouseEvent *mouseEvent);
	virtual bool processMouseMoveEvent(QMouseEvent *mouseEvent);
	virtual bool processMouseReleaseEvent(QMouseEvent *mouseEvent);

private:
	bool mIsDragged;
	QPoint mDragStartPoint;
};
}
#endif // MAPMOVEACTION
