#include "mapnavigation.h"

#include <QDebug>
#include <QMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>

MapNavigation::MapNavigation(QWidget *parent) :
	QGraphicsView(parent), mScaleX(1), mScaleY(1), mIsDragged(false)
{
	pScene = new QGraphicsScene();
	setScene(pScene);

	pPixmap = pScene->addPixmap(QPixmap());
	pPixmap->setPos(0, 0);
	pPixmap->setZValue(0);

	pFrame = pScene->addRect(0, 0, 30, 10);
	pFrame->setBrush( QBrush( QColor(255,255,255, 150 )));
	pFrame->setZValue(100);

	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	setFrameShape( QFrame::Box );
	setFrameShadow( QFrame::Plain );

	setMouseTracking(true);
}

void MapNavigation::updatePixmap()
{
	QPixmap p = mPixmap.scaledToWidth( width()-2, Qt::SmoothTransformation );

	setFixedHeight(p.height()+2);
	pScene->setSceneRect(p.rect());
	pPixmap->setPixmap(p);
}

void MapNavigation::setPixmap(const QPixmap &pm)
{
	mPixmap = pm;

	updatePixmap();
}

void MapNavigation::setSizes(QSize mapSize, QSize viewportSize)
{
	mMapSize = mapSize;
	mViewportSize = viewportSize;

	int mapX = pFrame->x() * mScaleX;
	int mapY = pFrame->y() * mScaleY;

	mScaleX = (double)mMapSize.width() / (double)sceneRect().width();
	mScaleY = (double)mMapSize.height() / (double)sceneRect().height();

	int w = (double)mViewportSize.width() / mScaleX;
	int h = (double)mViewportSize.height() / mScaleY;

	int x = (double)mapX / mScaleX;
	int y = (double)mapY / mScaleY;

	pFrame->setRect(0, 0, w, h);
	pFrame->setPos(x, y);
}

void MapNavigation::moveFrame(QPoint originalTopLeft)
{
	int x = (double)originalTopLeft.x() / mScaleX;
	int y = (double)originalTopLeft.y() / mScaleY;

	pFrame->setPos(x, y);
}

void MapNavigation::resizeEvent(QResizeEvent *event)
{
	QGraphicsView::resizeEvent(event);

	updatePixmap();

	setSizes(mMapSize, mViewportSize);
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

	notifyFrameGlobalPos();
}

void MapNavigation::notifyFrameGlobalPos()
{
	int x =  pFrame->x() * mScaleX;
	int y = pFrame->y() * mScaleY;

	emit navigationMoved(QPoint(x, y));
}
