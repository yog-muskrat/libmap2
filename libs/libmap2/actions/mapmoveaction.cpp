#include "actions/mapmoveaction.h"

#include "objects/mapobject.h"
#include "maphelper.h"
#include "mapcanvas.h"

using namespace Map2;

MapMoveAction::MapMoveAction(Map2::MapView *view) : MapAction(view), mIsDragged(false)
{

}

bool MapMoveAction::processMousePressEvent(QMouseEvent *mouseEvent)
{
	if(mouseEvent->button() == Qt::LeftButton)
	{
		QList<MapObject*> objects = pView->objectsAtPoint(mouseEvent->pos(), 5);

		if(!objects.isEmpty())
		{
			mIsDragged = true;
			mDragStartPoint = mouseEvent->pos();

			MapObject *obj = objects.first();
			obj->setSelected();

			if(!mouseEvent->modifiers().testFlag( Qt::ControlModifier ))
			{
				pView->clearSelection();
			}
			pView->addObjectToSelection( obj );
		}
		else
		{
			pView->clearSelection();
		}
	}
	return true;
}

bool MapMoveAction::processMouseMoveEvent(QMouseEvent *mouseEvent)
{
	if(mIsDragged)
	{
		if(!pView->selectedObjects().isEmpty() && mouseEvent->buttons().testFlag( Qt::LeftButton ))
		{
			CoordPlane oldCoord = pView->helper()->pictureToPlane(mDragStartPoint);
			CoordPlane newCoord = pView->helper()->pictureToPlane(mouseEvent->pos());

			CoordPlane delta = oldCoord - newCoord;

			foreach(MapObject *o, pView->selectedObjects())
			{
				o->moveBy(delta.x, delta.y);
			}

			mDragStartPoint = mouseEvent->pos();

			pView->setCursor( QCursor(Qt::ClosedHandCursor) );
		}
	}
	else
	{
		if(!pView->objectsAtPoint(mouseEvent->pos(), 5).isEmpty())
		{
			if(mouseEvent->modifiers().testFlag( Qt::ControlModifier))
			{
				pView->setCursor( QCursor(Qt::ArrowCursor) );
			}
			else
			{
				pView->setCursor( QCursor(Qt::OpenHandCursor) );
			}
		}
		else
		{
			pView->setCursor( QCursor(Qt::ArrowCursor) );
		}
	}
	return true;
}

bool MapMoveAction::processMouseReleaseEvent(QMouseEvent *mouseEvent)
{
	if(mouseEvent->button() == Qt::LeftButton)
	{
		if(pView->objectsAtPoint(mouseEvent->pos()).isEmpty(), 5)
		{
			pView->setCursor( QCursor(Qt::ArrowCursor) );
		}
		else
		{
			pView->setCursor( QCursor(Qt::OpenHandCursor) );
		}

		mIsDragged = false;
		return false;
	}

	return true;
}
