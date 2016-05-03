#include "actions/mapnoaction.h"

#include "objects/maplineobject.h"
#include "groups/mapformulargroup.h"

#include <QDebug>

using namespace Map2;

MapNoAction::MapNoAction(Map2::MapView *view) : MapAction(view), pFormular(0)
{

}

bool Map2::MapNoAction::processMousePressEvent(QMouseEvent *e)
{
	if(!e->button() == Qt::LeftButton)
	{
		return true;
	}

	QList<MapObject*> objs = pView->objectsAtPoint(e->pos());

	foreach(MapObject *obj, objs)
	{
		if(obj->parentGroup() && obj->parentGroup()->type() == MapGroup::MG_Formular)
		{
			pFormular = dynamic_cast<MapFormularGroup*>(obj->parentGroup());
			mInitialPoint = e->pos();
			return false;
		}
	}

	return true;
}

bool Map2::MapNoAction::processMouseMoveEvent(QMouseEvent *e)
{
	if(e->buttons().testFlag(Qt::LeftButton) && pFormular)
	{

		QPoint delta = e->pos() - mInitialPoint;
		pFormular->moveBy(delta);
		mInitialPoint = e->pos();

		return false;
	}

	return true;
}

bool Map2::MapNoAction::processMouseReleaseEvent(QMouseEvent *e)
{
	if(e->button() == Qt::LeftButton)
	{
		pFormular = 0;
		return false;
	}

	return true;
}
