#ifndef MAPACTION
#define MAPACTION

#include "widgets/maptoolbar.h"
#include "mapview.h"

#include <QMouseEvent>

namespace Map2
{

/*!
 * \brief Базовый класс для объектов-действий над картой.
 */
class MapAction
{
public:
	explicit MapAction(Map2::MapView *view) : pView(view) {}

	virtual MapToolBar::Tools type() = 0;

	virtual void setEnabled(const bool = true){}

	virtual bool processMousePressEvent(QMouseEvent *) {return true;}
	virtual bool processMouseMoveEvent(QMouseEvent *) {return true;}
	virtual bool processMouseReleaseEvent(QMouseEvent *) {return true;}
	virtual bool processMouseClickEvent(QMouseEvent *) {return true;}
	virtual bool processMouseDblClickEvent(QMouseEvent *) {return true;}

protected:
	MapView *pView;

};
}
#endif // MAPACTION
