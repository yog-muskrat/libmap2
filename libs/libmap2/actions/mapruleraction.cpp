#include "actions/mapruleraction.h"
#include "mapruler.h"
#include "maphelper.h"
#include "maplayer.h"
#include "mapcanvas.h"
#include "layersmodel.h"

#include <QObject>

using namespace Map2;

MapRulerAction::MapRulerAction(Map2::MapView *view) : MapAction(view), pRuler(0)
{
}

MapRulerAction::~MapRulerAction()
{
	if(pRuler)
	{
		delete pRuler;
	}
}

bool MapRulerAction::processMouseClickEvent(QMouseEvent *mouseEvent)
{
	if(!ruler())
	{
		return true;
	}

	if(mouseEvent->button() == Qt::LeftButton)
	{
		ruler()->addPoint( pView->helper()->pictureToPlane(mouseEvent->pos()+pView->canvas()->mapTopLeft() ) );
		return false;
	}

	return true;
}

void MapRulerAction::clear()
{
	if(!ruler())
	{
		return;
	}

	ruler()->clear();
}

MapRuler *MapRulerAction::ruler()
{
	///NOTE: Тут прошито имя классификатора!

	if(!pRuler)
	{
		// Если карта еще не загружена - не создавать технологический слой
		if(pView->mapHandle() <= 0)
		{
			return 0;
		}

		MapLayer *layer = 0;
		if(pView->layersModel()->containsKey("misc"))
		{
			layer = pView->layersModel()->layerByKey("misc");
		}
		else
		{
			layer = pView->createLayer("mgk.rsc", "misc", "Проч.", true);
		}

		Q_ASSERT(layer);

		pRuler = new MapRuler( layer );
	}

	return pRuler;
}

void MapRulerAction::setEnabled(const bool enabled)
{
	if(!ruler())
	{
		return;
	}

	ruler()->setVisible( enabled );
}
