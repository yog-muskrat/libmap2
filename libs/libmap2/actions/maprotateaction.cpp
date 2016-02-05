#include "actions/maprotateaction.h"
#include "objects/mapobject.h"
#include "objects/mapvectorobject.h"

#include <qmath.h>

using namespace Map2;

MapRotateAction::MapRotateAction(Map2::MapView *view) : MapAction(view), mIsDragged(false), pObject(0)
{

}

bool MapRotateAction::processMousePressEvent(QMouseEvent *mouseEvent)
{
	QList<MapObject*> objects = pView->objectsAtPoint(mouseEvent->pos(), 5);
	if(objects.isEmpty())
	{
		return true;
	}

	pObject = 0;
	foreach (MapObject *o, objects)
	{
		if(o->type() == MapObject::MO_Vector)
		{
			pObject = o;
			break;
		}
	}

	if(!pObject)
	{
		return true;
	}

	mIsDragged = true;
	mDragStartPoint = mouseEvent->pos();

	return false;
}

bool MapRotateAction::processMouseMoveEvent(QMouseEvent *mouseEvent)
{
	if(pObject && mIsDragged)
	{
		QLineF line(mDragStartPoint, mouseEvent->pos());

		// В Qt ноль справа от начала координат, а угл измеряется против часовой стрелки.
		qreal angle = fmod( (-line.angle() + 90. + 360.), 360.);

		MapVectorObject *obj = dynamic_cast<MapVectorObject*>(pObject);
		if(obj)
		{
			obj->setRotation(angle);
		}
	}

	return true;
}

bool MapRotateAction::processMouseReleaseEvent(QMouseEvent *mouseEvent)
{
	Q_UNUSED(mouseEvent);

	if(pObject)
	{
		pObject = 0;
		mIsDragged = false;
		mDragStartPoint = QPoint();
	}
	return pObject;
}

