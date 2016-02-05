#include "actions/mapdeleteaction.h"
#include "mapview.h"
#include "objects/mapobject.h"

#include <QMessageBox>

using namespace Map2;

bool MapDeleteAction::processMouseMoveEvent(QMouseEvent *mouseEvent)
{
	QList<MapObject*> objects = pView->objectsAtPoint(mouseEvent->pos(), 5);

	if(objects.isEmpty())
	{
		pView->setCursor(QCursor(Qt::ArrowCursor));
	}
	else
	{
		pView->setCursor(QCursor(Qt::PointingHandCursor));
	}

	return true;
}

bool MapDeleteAction::processMouseClickEvent(QMouseEvent *mouseEvent)
{
	if(mouseEvent->button() == Qt::LeftButton)
	{
		QList<MapObject*> objects = pView->objectsAtPoint(mouseEvent->pos(), 5);

		if(!objects.isEmpty())
		{
			MapObject *obj = objects.first();

			QString name = obj->name();

			int btn = QMessageBox::question(pView,
											"Удаление объекта",
											QString("Объект %0 будет удален. Продолжить?").arg(name),
											QMessageBox::Yes,
											QMessageBox::No);
			if(btn == QMessageBox::Yes)
			{
				obj->remove();
			}
		}
	}

	return true;
}
