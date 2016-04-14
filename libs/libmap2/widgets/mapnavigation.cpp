#include "widgets/mapnavigation.h"
#include "mapview.h"
#include "maphelper.h"

#include <QDebug>
#include <QMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>

using namespace Map2;

MapNavigation::MapNavigation(QWidget *parent) :
	QGraphicsView(parent), mScaleX(1), mScaleY(1), mIsDragged(false), pMapView(0)
{
	pScene = new QGraphicsScene();
	setScene(pScene);

	pPixmapItem = pScene->addPixmap(QPixmap());
	pPixmapItem->setPos(0, 0);
	pPixmapItem->setZValue(0);

	pFrame = pScene->addRect(0, 0, 30, 10);
	pFrame->setBrush( QBrush( QColor(255,255,255, 150 )));
	pFrame->setZValue(100);

	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	setFrameShape( QFrame::Box );
	setFrameShadow( QFrame::Plain );

	setMouseTracking(true);
}

void MapNavigation::setMapView(MapView *view)
{
	if(view == pMapView)
	{
		return;
	}

	if(pMapView)
	{
		disconnect(pMapView, SIGNAL(mapLoaded(QString)), this, SLOT(onMapLoaded()));
		disconnect(pMapView, SIGNAL(mapCenterScrolled(Map2::Coord)), this, SLOT(onMapScrolled()));
		disconnect(pMapView, SIGNAL(resized(QSize)), this, SLOT(adjustSize()));
		disconnect(pMapView, SIGNAL(scaleChanged(double)), this, SLOT(adjustSize()));
	}

	pMapView = view;

	if(pMapView->mapHandle() > 0)
	{
		mPixmap = pMapView->mapPreview( pMapView->width() > 0 ? pMapView->width() : 800 );
		updatePixmap();
	}
	else
	{
		mPixmap = QPixmap( size() );
	}

	connect(pMapView, SIGNAL(mapLoaded(QString)), this, SLOT(onMapLoaded()));
	connect(pMapView, SIGNAL(mapCenterScrolled(Map2::Coord)), this, SLOT(onMapScrolled()));
	connect(pMapView, SIGNAL(resized(QSize)), this, SLOT(adjustSize()));
	connect(pMapView, SIGNAL(scaleChanged(double)), this, SLOT(adjustSize()));
}

void MapNavigation::updatePixmap()
{
	QPixmap p = mPixmap.scaledToWidth( width()-2, Qt::SmoothTransformation );

	pScene->setSceneRect(p.rect());
	pPixmapItem->setPixmap(p);
}

void MapNavigation::onMapScrolled()
{
	if(!pMapView)
	{
		return;
	}

	Coord coord = pMapView->screenCenterCoordinate();

	QPoint point = pMapView->helper()->geoToPicture(coord);

	point -= pMapView->rect().center();

	int x = (double)point.x() / mScaleX;
	int y = (double)point.y() / mScaleY;

	///NOTE: Возможно, необходимость этой проверки - следствие какого-то моего косяка.
	/// Но пока это не доказано, буду считат ее ловким ходом.
	/// Yog.
	if(qAbs(x - pFrame->pos().x() > 1) || qAbs(pFrame->pos().y() - y) > 1)
	{
		pFrame->setPos(x, y);
	}
}

void MapNavigation::resizeEvent(QResizeEvent *event)
{
	QGraphicsView::resizeEvent(event);

	updatePixmap();

	setFixedHeight( pPixmapItem->pixmap().height() + 2);

	adjustSize();
}

void MapNavigation::mousePressEvent(QMouseEvent *event)
{
	if(itemAt(event->pos()) == pFrame)
	{
		mIsDragged = true;
		mPrevPoint = event->pos();
		setCursor( QCursor( Qt::ClosedHandCursor));
	}

	QGraphicsView::mousePressEvent(event);
}

void MapNavigation::mouseMoveEvent(QMouseEvent *event)
{
	if(mIsDragged)
	{
		int dx = event->x() - mPrevPoint.x();
		int dy = event->y() - mPrevPoint.y();

		dragFrameBy(dx, dy);

		mPrevPoint = event->pos();
		setCursor( QCursor( Qt::ClosedHandCursor));
	}
	else
	{
		if(itemAt(event->pos()) == pFrame)
		{
			setCursor( QCursor( Qt::OpenHandCursor));
		}
		else
		{
			setCursor( QCursor( Qt::ArrowCursor));
		}
	}

	QGraphicsView::mouseMoveEvent(event);
}

void MapNavigation::mouseReleaseEvent(QMouseEvent *event)
{
	mIsDragged = false;

	if(itemAt(event->pos()) == pFrame)
	{
		setCursor( QCursor( Qt::OpenHandCursor));
	}
	else
	{
		setCursor( QCursor( Qt::ArrowCursor));
	}

	QGraphicsView::mouseReleaseEvent(event);
}

void MapNavigation::mouseDoubleClickEvent(QMouseEvent *event)
{
	QPoint d = event->pos() - pFrame->sceneBoundingRect().center().toPoint();
	dragFrameBy(d.x(), d.y());

	QGraphicsView::mouseDoubleClickEvent(event);
}

void MapNavigation::adjustSize()
{
	if(!pMapView)
	{
		return;
	}

	QSize mapSize = pMapView->mapSizePx();
	QSize viewportSize = pMapView->size();

	mScaleX = (double)mapSize.width() / (double)sceneRect().width();
	mScaleY = (double)mapSize.height() / (double)sceneRect().height();

	int w = (double)viewportSize.width() / mScaleX;
	int h = (double)viewportSize.height() / mScaleY;

	Coord centerCoord = pMapView->screenCenterCoordinate();
	QPoint centerPoint = pMapView->helper()->geoToPicture(centerCoord);

	centerPoint -= pMapView->rect().center();

	int x = (double)centerPoint.x() / mScaleX;
	int y = (double)centerPoint.y() / mScaleY;

	pFrame->setRect(0, 0, w, h);
	pFrame->setPos(x, y);
}

void MapNavigation::onMapLoaded()
{
	mPixmap = pMapView->mapPreview( pMapView->width() > 0 ? pMapView->width() : 800 );
	updatePixmap();
	adjustSize();
}

void MapNavigation::dragFrameBy(int dx, int dy)
{
	pFrame->moveBy(dx, dy);

	if(!sceneRect().contains( pFrame->sceneBoundingRect()))
	{
		if(pFrame->x() < 0)
		{
			pFrame->setX(0);
		}
		else if(pFrame->sceneBoundingRect().right() > sceneRect().right())
		{
			pFrame->setX( sceneRect().width() - pFrame->rect().width() - 1);
		}

		if(pFrame->y() < 0)
		{
			pFrame->setY(0);
		}
		else if(pFrame->sceneBoundingRect().bottom() > sceneRect().bottom())
		{
			pFrame->setY( sceneRect().height() - pFrame->rect().height() - 1);
		}
	}

	int x =  (pFrame->x() + pFrame->rect().center().x())* mScaleX;
	int y = (pFrame->y() + pFrame->rect().center().y()) * mScaleY;

	qDebug()<<"Set center"<<QPoint(x,y);

	pMapView->setCenter( QPoint(x, y) );
}
