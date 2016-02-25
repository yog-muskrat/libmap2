#include "actions/mapruleraction.h"
#include "mapruler.h"
#include "maphelper.h"
#include "maplayer.h"
#include "mapcanvas.h"

#include <QObject>

using namespace Map2;

MapRulerAction::MapRulerAction(Map2::MapView *view) : MapAction(view)
{
	pLayer = pView->createLayer("mgk.rsc", "", "ruler_layer", true);
	QObject::connect(pLayer, SIGNAL(dataChanged(QModelIndex,QModelIndex)), pView->canvas(), SLOT(queueRepaint()));
	pLayer->setVisible(true);
	pRuler = new MapRuler( pLayer );
}

MapRulerAction::~MapRulerAction()
{
	delete pRuler;
	delete pLayer;
}

bool MapRulerAction::processMouseClickEvent(QMouseEvent *mouseEvent)
{
	if(mouseEvent->button() == Qt::LeftButton)
	{
		pRuler->addPoint( pView->helper()->pictureToPlane(mouseEvent->pos()+pView->canvas()->mapTopLeft() ) );
		return false;
	}

	return true;
}

void MapRulerAction::clear()
{
	pRuler->clear();
}

void MapRulerAction::setEnabled(const bool enabled)
{
	pLayer->setVisible(enabled);
	if(!enabled )
	{
		pRuler->clear();
	}
}
