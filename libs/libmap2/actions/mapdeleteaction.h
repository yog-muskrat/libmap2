#ifndef MAPDELETEACTION
#define MAPDELETEACTION

#include "actions/mapaction.h"

namespace Map2
{

/*!
 * \brief Класс действия по удалению объекта карты.
 */
class MapDeleteAction : public MapAction
{
public:
	explicit MapDeleteAction(Map2::MapView *view) : MapAction(view) {}
	~MapDeleteAction() {}

	virtual Map2::MapToolBar::Tools type() {return MapToolBar::DeleteObject;}

	virtual bool processMouseMoveEvent(QMouseEvent *mouseEvent);
	virtual bool processMouseClickEvent(QMouseEvent *mouseEvent);
};
}

#endif // MAPDELETEACTION
