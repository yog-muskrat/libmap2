#ifndef MAPNOACTION
#define MAPNOACTION

#include "actions/mapaction.h"
namespace Map2
{
class MapFormularGroup;

class MapNoAction : public MapAction
{
public:
	explicit MapNoAction(Map2::MapView *view);

	virtual Map2::MapToolBar::Tools type() { return MapToolBar::None; }

	///TODO: Здесь реализовано перетаскивание формуляров.
	/// Это временная мера, нужно придумать решение поизящнее.
	virtual bool processMousePressEvent(QMouseEvent *e);
	virtual bool processMouseMoveEvent(QMouseEvent *e);
	virtual bool processMouseReleaseEvent(QMouseEvent *e);

private:
	MapFormularGroup *pFormular;
	QPoint mInitialPoint;
};
}
#endif // MAPNOACTION
