#include "actions/mapmoveaction.h"

#include "groups/mapformulargroup.h"

#include "objects/mapobject.h"
#include "maphelper.h"
#include "mapcanvas.h"

#include <QDebug>

using namespace Map2;

MapMoveAction::MapMoveAction(Map2::MapView *view) : MapAction(view), pObj(0)
{

}

bool MapMoveAction::processMousePressEvent(QMouseEvent *mouseEvent)
{
	if(mouseEvent->button() == Qt::LeftButton)
	{
		QList<MapObject*> objects = pView->objectsAtPoint(mouseEvent->pos(), 5);

		if(!objects.isEmpty())
		{
			mOldCoord = pView->helper()->pictureToPlane(mouseEvent->pos());

			pObj = objects.first();
		}
	}
	return true;
}

bool MapMoveAction::processMouseMoveEvent(QMouseEvent *mouseEvent)
{
	if(pObj && mouseEvent->buttons().testFlag( Qt::LeftButton ))
	{
		CoordPlane newCoord = pView->helper()->pictureToPlane(mouseEvent->pos());
		CoordPlane delta = newCoord - mOldCoord;

		if(!pObj->parentGroup() || pObj->parentGroup()->type() == MapGroup::MG_Simple)
		{
			pObj->moveBy(delta.x, delta.y);
		}

		mOldCoord = newCoord;

		pView->setCursor( QCursor(Qt::ClosedHandCursor) );
	}
	return true;
}

bool MapMoveAction::processMouseReleaseEvent(QMouseEvent *mouseEvent)
{
	if(mouseEvent->button() == Qt::LeftButton && pObj)
	{
		pObj = 0;
		return false;
	}

	return true;
}
