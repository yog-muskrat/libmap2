#ifndef MAPLINEOBJECTACTION
#define MAPLINEOBJECTACTION

#include "actions/mapaction.h"

namespace Map2
{
class MapLineObject;

/*!
 * \brief Класс действия по рисованию объекта-линии
 */
class MapLineObjectAction : public MapAction
{
public:
	explicit MapLineObjectAction(Map2::MapView *view);
	~MapLineObjectAction();

	virtual void setEnabled(const bool enabled);
	virtual Map2::MapToolBar::Tools type() { return MapToolBar::AddLineObject; }
	virtual bool processMouseClickEvent(QMouseEvent *mouseEvent);
	virtual bool processMouseDblClickEvent(QMouseEvent *mouseEvent);

private:
	MapLineObject *pObject;
};
}
#endif // MAPLINEOBJECTACTION
