#include "mapview.h"
#include "maplayer.h"
#include "mapcanvas.h"
#include "rscviewer.h"
#include "maphelper.h"
#include "objects/mapobject.h"
#include "objects/maplineobject.h"
#include "objects/mapzoneobject.h"
#include "objects/mapvectorobject.h"
#include "widgets/maptoolbar.h"

#include "actions/mapnoaction.h"
#include "actions/mapmoveaction.h"
#include "actions/mapruleraction.h"
#include "actions/maprotateaction.h"
#include "actions/mapdeleteaction.h"
#include "actions/maprectzoomaction.h"
#include "actions/maplineobjectaction.h"
#include "actions/mapzoneobjectaction.h"
#include "actions/mapvectorobjectaction.h"

#include <qmath.h>
#include <QDebug>
#include <QAction>
#include <QToolBar>
#include <QMouseEvent>
#include <QMessageBox>

using namespace Map2;

MapToolBar::MapToolBar(Map2::MapView *view)
	: QObject(view), pView(view), pToolBar(0), mCurrentTool(MapToolBar::None),
	  mLeftBtnPressed(false), mRightBtnPressed(false)
{

}

MapToolBar::~MapToolBar()
{
	if( pToolBar && pToolBar->parent() == 0)
	{
		pToolBar->deleteLater();
	}
}

QToolBar *MapToolBar::toolBar()
{
	if(!pToolBar)
	{
		pToolBar = new QToolBar("Инструменты");

		QActionGroup *group = new QActionGroup(this);
		group->setExclusive(true);

		group->addAction( addActionWithData(new QAction(QIcon(":cursor"), "Нет", this), MapToolBar::None) )->setChecked(true);
		group->addAction( addActionWithData(new QAction(QIcon(":move"), "Переместить объект", this), MapToolBar::MoveObject) );
		group->addAction( addActionWithData(new QAction(QIcon(":rotate"), "Повернуть объект", this), MapToolBar::RotateObject) );
		group->addAction( addActionWithData(new QAction(QIcon(":delete"),"Удалить объект", this), MapToolBar::DeleteObject) );
		group->addAction( addActionWithData(new QAction(QIcon(":map_object"),"Добавить вектор", this), MapToolBar::AddVectorObject) );
		group->addAction( addActionWithData(new QAction(QIcon(":map_line"), "Добавить линию", this), MapToolBar::AddLineObject) );
		group->addAction( addActionWithData(new QAction(QIcon(":map_polygon"),"Добавить зону", this), MapToolBar::AddZoneObject) );
		group->addAction( addActionWithData(new QAction(QIcon(":map_ruler"), "Линейка", this), MapToolBar::Ruler) );
		group->addAction( addActionWithData(new QAction(QIcon(":zoom_in_bw"),"Приблизить область", this), MapToolBar::RectZoom) );

		mActions[MapToolBar::None] = new MapNoAction(pView);
		mActions[MapToolBar::Ruler] = new MapRulerAction(pView);
		mActions[MapToolBar::RectZoom] = new MapRectZoomAction(pView);
		mActions[MapToolBar::MoveObject] = new MapMoveAction(pView);
		mActions[MapToolBar::RotateObject] = new MapRotateAction(pView);
		mActions[MapToolBar::DeleteObject] = new MapDeleteAction(pView);
		mActions[MapToolBar::AddLineObject] = new MapLineObjectAction(pView);
		mActions[MapToolBar::AddZoneObject] = new MapZoneObjectAction(pView);
		mActions[MapToolBar::AddVectorObject] = new MapVectorObjectAction(pView);

		connect(group, SIGNAL(triggered(QAction*)), this, SLOT(onActionTriggered(QAction*)));
	}

	return pToolBar;
}

bool MapToolBar::processMousePressEvent(QMouseEvent *mouseEvent)
{
	Q_ASSERT(mActions.contains(mCurrentTool));
	MapAction *act = mActions[mCurrentTool];

	if(mouseEvent->button() == Qt::LeftButton)
	{
		mLeftClickTi.start();
		mLeftBtnPressed = true;
	}
	else if(mouseEvent->button() == Qt::RightButton)
	{
		mRightClickTi.start();
		mRightBtnPressed = true;
	}

	return act->processMousePressEvent(mouseEvent);
}

bool MapToolBar::processMouseMoveEvent(QMouseEvent *mouseEvent)
{
	Q_ASSERT(mActions.contains(mCurrentTool));
	MapAction *act = mActions[mCurrentTool];

	return act->processMouseMoveEvent(mouseEvent);
}

bool MapToolBar::processMouseReleaseEvent(QMouseEvent *mouseEvent)
{
	Q_ASSERT(mActions.contains(mCurrentTool));
	MapAction *act = mActions[mCurrentTool];

	bool b = act->processMouseReleaseEvent(mouseEvent);

	if(mouseEvent->button() == Qt::LeftButton)
	{
		if(mLeftBtnPressed && mLeftClickTi.elapsed() < mClickInterval )
		{
			mLeftClickTi.invalidate();
			mLeftBtnPressed = false;
			emit leftClick(mouseEvent->pos());

			if(b)
			{
				b = act->processMouseClickEvent(mouseEvent);
			}
		}

	}

	else if(mouseEvent->button() == Qt::RightButton)
	{
		if(mRightBtnPressed && mRightClickTi.elapsed() < mClickInterval )
		{
			mRightClickTi.invalidate();
			mRightBtnPressed = false;
			emit rightClick(mouseEvent->pos());
			if(b)
			{
				b = act->processMouseClickEvent(mouseEvent);
			}
		}
	}

	return b;
}

bool MapToolBar::processMouseDoubleClickEvent(QMouseEvent *mouseEvent)
{
	Q_ASSERT(mActions.contains(mCurrentTool));
	MapAction *act = mActions[mCurrentTool];

	return act->processMouseDblClickEvent(mouseEvent);
}

void MapToolBar::onActionTriggered(QAction *act)
{
	Q_ASSERT(pView);

	if(act->isChecked())
	{
		MapToolBar::Tools tool = static_cast<MapToolBar::Tools>( act->data().toInt() );
		setCurrentTool(tool);
	}
}

void MapToolBar::setCurrentTool(MapToolBar::Tools tool)
{
	if(tool == mCurrentTool)
	{
		return;
	}

	mActions[mCurrentTool]->setEnabled(false);
	mCurrentTool = tool;
	mActions[mCurrentTool]->setEnabled(true);
}

QAction *MapToolBar::addActionWithData(QAction *act, QVariant data)
{
	Q_ASSERT(pToolBar);

	act->setData(data);
	act->setCheckable(true);
	pToolBar->addAction(act);

	return act;
}
