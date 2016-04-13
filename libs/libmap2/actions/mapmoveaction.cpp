#include "actions/mapmoveaction.h"

#include "objects/mapobject.h"
#include "maphelper.h"
#include "mapcanvas.h"

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
//			pObj->setSelected(true);
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

		pObj->moveBy(delta.x, delta.y);

		mOldCoord = newCoord;

		pView->setCursor( QCursor(Qt::ClosedHandCursor) );
	}
	return true;
}

bool MapMoveAction::processMouseReleaseEvent(QMouseEvent *mouseEvent)
{
	if(mouseEvent->button() == Qt::LeftButton && pObj)
	{
//		pObj->setSelected(false);
		pObj = 0;
		return false;
	}

	return true;
}
