#include "actions/maplineobjectaction.h"

#include "maplayer.h"
#include "rscviewer.h"
#include "maphelper.h"
#include "mapcanvas.h"
#include "objects/maplineobject.h"

#include "QMessageBox"

using namespace Map2;

MapLineObjectAction::MapLineObjectAction(Map2::MapView *view)
	: MapAction(view), pObject(0)
{
}

MapLineObjectAction::~MapLineObjectAction()
{
	if(pObject)
	{
		pObject->remove();
	}
}

bool MapLineObjectAction::processMouseClickEvent(QMouseEvent *mouseEvent)
{
	if(mouseEvent->button() == Qt::LeftButton)
	{
		CoordPlane coord = pView->helper()->pictureToPlane(pView->canvas()->mapTopLeft() + mouseEvent->pos() );
		if(!pObject)
		{
			if(!pView->activeLayer())
			{
				QMessageBox::information(pView, "Добавление линии", "Не задан активный слой карты.", "Закрыть");
				return true;
			}

			int exCode = RscViewer::selectLineExCode(pView->activeLayer()->rscName());
			if(exCode <= 0)
			{
				return false;
			}

			QList<CoordPlane> coords;
			coords << coord;

			pObject = pView->activeLayer()->addLineObject(exCode, coords);
		}
		else
		{
			pObject->addPoint(coord);
			return false;
		}
	}

	return true;
}

bool MapLineObjectAction::processMouseDblClickEvent(QMouseEvent *mouseEvent)
{
	if(mouseEvent->button() == Qt::LeftButton)
	{
		CoordPlane coord = pView->helper()->pictureToPlane( pView->canvas()->mapTopLeft() + mouseEvent->pos() );

		if(pObject)
		{
			pObject->addPoint(coord);
			pObject = 0;
			return false;
		}
	}

	return true;
}

void MapLineObjectAction::setEnabled(const bool enabled)
{
	if(!enabled && pObject)
	{
		pObject->remove();
		pObject = 0;
	}
}
