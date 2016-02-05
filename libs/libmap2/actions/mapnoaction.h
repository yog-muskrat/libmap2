#ifndef MAPNOACTION
#define MAPNOACTION

#include "actions/mapaction.h"
namespace Map2
{

class MapNoAction : public MapAction
{
public:
	explicit MapNoAction(Map2::MapView *view);

	virtual Map2::MapToolBar::Tools type() { return MapToolBar::None; }
};
}
#endif // MAPNOACTION
