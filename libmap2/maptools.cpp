#include "mapview.h"
#include "maptools.h"
#include "maplayer.h"
#include "mapruler.h"
#include "mapcanvas.h"
#include "rscviewer.h"
#include "maphelper.h"
#include "mapobject.h"
#include "maplineobject.h"
#include "mapzoneobject.h"
#include "mapvectorobject.h"

#include <QtMath>
#include <QDebug>
#include <QAction>
#include <QToolBar>
#include <QMouseEvent>
#include <QMessageBox>

MapTools::MapTools(MapView *view)
	: QObject(view), pView(view), pToolBar(0), mTool(MapTools::None), pRuler(0), pTempObject(0), mIsDragged(false)
{

}

MapTools::~MapTools()
{
	if( pToolBar && pToolBar->parent() == 0)
	{
		pToolBar->deleteLater();
	}

	qDeleteAll(mTempSites);
}

QToolBar *MapTools::toolBar()
{
	if(!pToolBar)
	{
		pToolBar = new QToolBar("Инструменты");

		QActionGroup *group = new QActionGroup(this);
		group->setExclusive(true);

		group->addAction( addActionWithData(new QAction(QIcon(":cursor"), "Нет", this), MapTools::None) )->setChecked(true);
		group->addAction( addActionWithData(new QAction(QIcon(":move"), "Переместить", this), MapTools::MoveObject) );
		group->addAction( addActionWithData(new QAction(QIcon(":rotate"), "Повернуть", this), MapTools::RotateObject) );
		group->addAction( addActionWithData(new QAction(QIcon(":delete"),"Удалить", this), MapTools::DeleteObject) );
		group->addAction( addActionWithData(new QAction(QIcon(":marker"),"Добавить вектор", this), MapTools::AddVectorObject) );
		group->addAction( addActionWithData(new QAction("Добавить линию", this), MapTools::AddLineObject) );
		group->addAction( addActionWithData(new QAction(QIcon(":polygon"),"Добавить зону", this), MapTools::AddZoneObject) );
		group->addAction( addActionWithData(new QAction("Линейка", this), MapTools::Ruler) );
		group->addAction( addActionWithData(new QAction(QIcon(":zoom_in"),"Приблизить", this), MapTools::RectZoom) );

		connect(group, SIGNAL(triggered(QAction*)), this, SLOT(onActionTriggered(QAction*)));
	}

	return pToolBar;
}

bool MapTools::processMousePressEvent(QMouseEvent *mouseEvent)
{
	if(mouseEvent->button() == Qt::LeftButton)
	{
		// Пока интересуют только клики левой кнопкой.
		mClickTi.start();

		if(mTool == MapTools::RectZoom)
		{
			mIsDragged = true;
			mDragStartPoint = mouseEvent->pos();

			pView->canvas()->setZoomRect( QRect(mouseEvent->pos(), mouseEvent->pos()));
			pView->canvas()->setCursor( QCursor(Qt::SizeFDiagCursor) );
		}
		else if(mTool == MapTools::None)
		{
			pView->canvas()->setCursor( QCursor(Qt::ClosedHandCursor) );
		}
		else if(mTool == MapTools::MoveObject)
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
		else if(mTool == MapTools::Ruler)
		{
			return false;
		}
		else if(mTool == MapTools::AddLineObject)
		{
			CoordPlane coord = MapHelper::pictureToPlane(pView->mapHandle(), pView->canvas()->mapTopLeft() + mouseEvent->pos() );
			if(!pTempObject)
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

				pTempObject =  pView->activeLayer()->addLineObject(exCode, coords);
			}
			else
			{
				MapLineObject *o = dynamic_cast<MapLineObject*>(pTempObject);
				if(!o)
				{
					return false;
				}

				o->addPoint(coord);
				return false;
			}
		}
		else if(mTool == MapTools::AddZoneObject)
		{
			CoordPlane coord = MapHelper::pictureToPlane(pView->mapHandle(), pView->canvas()->mapTopLeft() + mouseEvent->pos() );
			if(!pTempObject)
			{
				if(!pView->activeLayer())
				{
					QMessageBox::information(pView, "Добавление зоны", "Не задан активный слой карты.", "Закрыть");
					return true;
				}

				int exCode = RscViewer::selectZoneExCode(pView->activeLayer()->rscName());
				if(exCode <= 0)
				{
					return false;
				}

				QList<CoordPlane> coords;
				coords << coord;

				pTempObject =  pView->activeLayer()->addZoneObject(exCode, coords);
			}
			else
			{
				MapZoneObject *o = dynamic_cast<MapZoneObject*>(pTempObject);
				if(!o)
				{
					return false;
				}

				qDebug()<<"add point to zone";

				o->addPoint(coord);
				return false;
			}
		}
		else if(mTool == MapTools::RotateObject)
		{
			qDebug()<<"trying to start rotation...";
			QList<MapObject*> objects = pView->objectsAtPoint(mouseEvent->pos(), 5);
			if(objects.isEmpty())
			{
				qDebug()<<"No objects!";
				return true;
			}

			pTempObject = 0;
			foreach (MapObject *o, objects)
			{
				if(o->type() == MapObject::MO_Vector)
				{
					pTempObject = o;
					break;
				}
			}

			if(!pTempObject)
			{
				qDebug()<<"No vector object!";
				return true;
			}

			mIsDragged = true;
			mDragStartPoint = mouseEvent->pos();
			qDebug()<<"Started!";

			return false;
		}
	}
	return true;
}

bool MapTools::processMouseMoveEvent(QMouseEvent *mouseEvent)
{
	if(mIsDragged)
	{
		if(mTool == MapTools::RectZoom)
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
		else if(mTool == MapTools::None)
		{
			pView->canvas()->setCursor( QCursor(Qt::ClosedHandCursor) );
		}
		else if(mTool == MapTools::MoveObject)
		{
			if(!pView->selectedObjects().isEmpty() && mouseEvent->buttons().testFlag( Qt::LeftButton ))
			{
				CoordPlane oldCoord = MapHelper::pictureToPlane(pView->mapHandle(), mDragStartPoint);
				CoordPlane newCoord = MapHelper::pictureToPlane(pView->mapHandle(), mouseEvent->pos());

				CoordPlane delta = oldCoord - newCoord;

				foreach(MapObject *o, pView->selectedObjects())
				{
					o->moveBy(delta.x, delta.y);
				}

				mDragStartPoint = mouseEvent->pos();

				pView->canvas()->setCursor( QCursor(Qt::ClosedHandCursor) );
			}
		}
		else if(mTool == MapTools::RotateObject)
		{
			qDebug()<<"trying to rotate object...";
			if(pTempObject)
			{
				QLineF line(mDragStartPoint, mouseEvent->pos());

				qreal angle = fmod( (line.angle() + 90. + 360.), 360.); // +90, т.к. в Qt ноль - справа.
				qDebug()<<"rotating to angle"<<angle;

				MapVectorObject *obj = dynamic_cast<MapVectorObject*>(pTempObject);
				if(obj)
				{
					obj->setRotation(angle);
					qDebug()<<"Rotation is set!";
				}
			}
		}
	}
	else
	{
		if(mTool == MapTools::None)
		{
			pView->canvas()->setCursor( QCursor(Qt::OpenHandCursor) );
		}
		else if(mTool == MapTools::RectZoom)
		{
			pView->canvas()->setCursor( QCursor(Qt::CrossCursor) );
		}
		else if(mTool == MapTools::MoveObject)
		{
			if(!pView->objectsAtPoint(mouseEvent->pos(), 5).isEmpty())
			{
				if(mouseEvent->modifiers().testFlag( Qt::ControlModifier))
				{
					pView->canvas()->setCursor( QCursor(Qt::ArrowCursor) );
				}
				else
				{
					pView->canvas()->setCursor( QCursor(Qt::OpenHandCursor) );
				}
			}
			else
			{
				pView->canvas()->setCursor( QCursor(Qt::ArrowCursor) );
			}
		}
		else
		{
			pView->canvas()->setCursor( QCursor(Qt::ArrowCursor) );
		}
	}

	return true;
}

bool MapTools::processMouseReleaseEvent(QMouseEvent *mouseEvent)
{
	if(mouseEvent->button() == Qt::LeftButton)
	{
		bool click = false;
		if(mClickTi.isValid() && mClickTi.elapsed() < 1000 )
		{
			mClickTi.invalidate();
			click = true;
		}

		if(mTool == MapTools::RectZoom)
		{
			pView->zoomToRect( pView->canvas()->zoomRect() );
			pView->canvas()->setZoomRect(QRect(0,0,0,0));
			pView->canvas()->setCursor( QCursor(Qt::CrossCursor) );
			return false;
		}
		else if(mTool == MapTools::None)
		{
			pView->canvas()->setCursor( QCursor(Qt::OpenHandCursor) );
		}
		else if(mTool == MapTools::MoveObject)
		{
			if(pView->objectsAtPoint(mouseEvent->pos()).isEmpty(), 5)
			{
				pView->canvas()->setCursor( QCursor(Qt::ArrowCursor) );
			}
			else
			{
				pView->canvas()->setCursor( QCursor(Qt::OpenHandCursor) );
			}

			mIsDragged = false;
			return false;
		}
		else if(mTool == MapTools::Ruler)
		{
			Q_ASSERT(pRuler);

			pRuler->addPoint( MapHelper::pictureToPlane( pView->mapHandle(), mouseEvent->pos()+pView->canvas()->mapTopLeft() ) );
			return false;
		}
		else if(mTool == MapTools::RotateObject)
		{
			qDebug()<<"tryin to stop rotation...";
			if(pTempObject)
			{
				pTempObject = 0;
				mIsDragged = false;
				mDragStartPoint = QPoint();
				qDebug()<<"rotate no more!";
			}
		}
	}
	return true;
}

bool MapTools::processMouseDoubleClickEvent(QMouseEvent *mouseEvent)
{
	if(mTool == MapTools::AddVectorObject)
	{
		if(!pView->activeLayer())
		{
			QMessageBox::information(pView, "Добавление объекта", "Не задан активный слой карты.", "Закрыть");
			return true;
		}

		int exCode = RscViewer::selectVectorExCode(pView->activeLayer()->rscName());

		if(exCode <= 0)
		{
			return true;
		}

		MapVectorObject *obj = new MapVectorObject(exCode, pView->activeLayer());

		QPoint pictureCoord = pView->canvas()->mapTopLeft() + mouseEvent->pos();

		obj->setCoordinates( MapHelper::pictureToPlane(pView->mapHandle(), pictureCoord));
		return false;
	}
	else if(mTool == MapTools::AddLineObject)
	{
		CoordPlane coord = MapHelper::pictureToPlane(pView->mapHandle(), pView->canvas()->mapTopLeft() + mouseEvent->pos() );

		if(pTempObject)
		{
			MapLineObject *o = dynamic_cast<MapLineObject*>(pTempObject);
			if(!o)
			{
				return false;
			}

			o->addPoint(coord);
			pTempObject = 0;
			return false;
		}
	}
	else if(mTool == MapTools::AddZoneObject)
	{
		qDebug()<<"dbl click zone";
		CoordPlane coord = MapHelper::pictureToPlane(pView->mapHandle(), pView->canvas()->mapTopLeft() + mouseEvent->pos() );

		if(pTempObject)
		{
			qDebug()<<"dbl click zone temp";
			MapZoneObject *o = dynamic_cast<MapZoneObject*>(pTempObject);
			if(!o)
			{
				return false;
			}

			qDebug()<<"dbl almost there";

			o->addPoint(coord);
			o->closeZone();
			pTempObject = 0;
			return false;
		}
	}
	return true;
}

void MapTools::onActionTriggered(QAction *act)
{
	Q_ASSERT(pView);

	if(act->isChecked())
	{
		MapTools::Tools tool = static_cast<MapTools::Tools>( act->data().toInt() );
		setCurrentTool(tool);
	}
}

void MapTools::setCurrentTool(MapTools::Tools tool)
{
	mTool = tool;

	if(mTool == MapTools::Ruler)
	{
		if(!mTempSites.contains("ruler"))
		{
			MapLayer *l = pView->createTempLayer("mgk.rsc", "ruler_layer");
			mTempSites["ruler"] = l;

			connect(l, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)), pView->canvas(), SLOT(queueRepaint()));
		}
		mTempSites["ruler"]->setVisible(true);

		if(!pRuler)
		{
			pRuler = new MapRuler( mTempSites["ruler"] );
		}
	}
	else
	{
		if(mTempSites.contains("ruler"))
		{
			mTempSites["ruler"]->setVisible(false);
		}

		if(pRuler)
		{
			pRuler->clear();
		}
	}

	if(pTempObject != 0)
	{
		pTempObject->mapLayer()->removeObject(pTempObject);
		pTempObject = 0;
	}
}

QAction *MapTools::addActionWithData(QAction *act, QVariant data)
{
	Q_ASSERT(pToolBar);

	act->setData(data);
	act->setCheckable(true);
	pToolBar->addAction(act);

	return act;
}
