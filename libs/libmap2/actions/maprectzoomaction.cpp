#include "actions/maprectzoomaction.h"

#include "mapcanvas.h"

using namespace Map2;

MapRectZoomAction::MapRectZoomAction(Map2::MapView *view)
	: MapAction(view), mIsDragged(false)
{

}

bool MapRectZoomAction::processMousePressEvent(QMouseEvent *mouseEvent)
{
	if(mouseEvent->button() == Qt::LeftButton)
	{
		mIsDragged = true;
		mDragStartPoint = mouseEvent->pos();

		pView->canvas()->setZoomRect( QRect(mouseEvent->pos(), mouseEvent->pos()));
		pView->canvas()->setCursor( QCursor(Qt::SizeFDiagCursor) );
	}

	return true;
}

bool MapRectZoomAction::processMouseMoveEvent(QMouseEvent *mouseEvent)
{
	if(mIsDragged)
	{
		QRect rect = pView->canvas()->zoomRect();
		if(mouseEvent->x() > rect.x())
		{
			rect.setRight(mouseEvent->x());
		}
		else
		{
			rect.setLeft(mouseEvent->x());
		}

		if(mouseEvent->y() > rect.y())
		{
			rect.setBottom(mouseEvent->y());
		}
		else
		{
			rect.setTop(mouseEvent->y());
		}
		pView->canvas()->setZoomRect(rect);
		pView->canvas()->setCursor( QCursor(Qt::SizeFDiagCursor) );
	}
	else
	{
		pView->canvas()->setCursor( QCursor(Qt::CrossCursor) );
	}

	return true;
}

bool MapRectZoomAction::processMouseReleaseEvent(QMouseEvent *mouseEvent)
{
	if(mouseEvent->button() == Qt::LeftButton)
	{
		pView->zoomToRect( pView->canvas()->zoomRect() );
		pView->canvas()->setZoomRect(QRect(0,0,0,0));
		pView->canvas()->setCursor( QCursor(Qt::CrossCursor) );
		mIsDragged = false;
		return false;
	}
	return true;
}
