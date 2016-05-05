#ifndef MAPVECTOROBJECTACTION
#define MAPVECTOROBJECTACTION

#include "actions/mapaction.h"

namespace Map2
{

class MapVectorObjectAction : public MapAction
{
public:
	explicit MapVectorObjectAction(Map2::MapView *view);
	~MapVectorObjectAction() {}

	virtual Map2::MapToolBar::Tools type() { return MapToolBar::AddVectorObject; }
	virtual bool processMouseDblClickEvent(QMouseEvent *mouseEvent);
};
}

#endif // MAPVECTOROBJECTACTION
