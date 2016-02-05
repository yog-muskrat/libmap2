#ifndef MAPZONEOBJECTACTION
#define MAPZONEOBJECTACTION

#include "actions/mapaction.h"

namespace Map2
{
class MapZoneObject;

/*!
 * \brief Класс действия по рисованию площадного объекта.
 */
class MapZoneObjectAction : public MapAction
{
public:
	explicit MapZoneObjectAction(Map2::MapView *view);
	~MapZoneObjectAction();

	virtual void setEnabled(const bool enabled);
	virtual Map2::MapToolBar::Tools type() { return MapToolBar::AddZoneObject; }
	virtual bool processMouseClickEvent(QMouseEvent *mouseEvent);
	virtual bool processMouseDblClickEvent(QMouseEvent *mouseEvent);

private:
	MapZoneObject *pObject;
};
}

#endif // MAPZONEOBJECTACTION
