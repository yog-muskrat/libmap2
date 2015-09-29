#include "mapview.h"
#include "maplayer.h"
#include "layersmodel.h"
#include "mapcanvas.h"
#include "mapnavigation.h"

#include <QLabel>
#include <QDebug>
#include <QKeyEvent>
#include <QScrollBar>
#include <QGridLayout>
#include <QApplication>
#include <QDir>

MapView::MapView(QString sitDir, QString rscDir, QWidget *parent)
	: QWidget(parent), pNavigation(0), mIsDragged(false), mLastLayerId(0), mRscDir(rscDir), mSitDir(sitDir)
{
	setFocusPolicy(Qt::TabFocus);

	pVerticalScroll = new QScrollBar(Qt::Vertical, this);
	pHorizontalScroll = new QScrollBar(Qt::Horizontal, this);

	pCanvas = new MapCanvas(this);
	pCanvas->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	pCanvas->installEventFilter( this );
	pCanvas->setMouseTracking(true);

	mLayersModel = new LayersModel(this);
	connect(mLayersModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)), pCanvas, SLOT(repaint()));

	QGridLayout *lay = new QGridLayout(this);
	lay->addWidget(pVerticalScroll, 0, 0);
	lay->addWidget(pCanvas, 0, 1);
	lay->addWidget(pHorizontalScroll, 1, 1);

	connect(pVerticalScroll, SIGNAL(sliderMoved(int)), this, SLOT(onScrollMap()));
	connect(pVerticalScroll, SIGNAL(actionTriggered(int)), this, SLOT(onScrollMap()));
	connect(pHorizontalScroll, SIGNAL(sliderMoved(int)), this, SLOT(onScrollMap()));
	connect(pHorizontalScroll, SIGNAL(actionTriggered(int)), this, SLOT(onScrollMap()));

	if(!checkDirs())
	{
		qDebug()<<"Ошибка! Некорректные каталоги классификаторов и пользовательских карт.";
	}

	mapSetCommonRscPath( qPrintable(mRscDir) );
}

MapView::~MapView()
{
	mLayersModel->deleteLater();

	if(mMapHandle > 0)
	{
		mapCloseData( mMapHandle );
	}
}

void MapView::openMap(QString mapFullPath)
{
	mMapHandle = mapOpenData(qPrintable(mapFullPath), 0);
	mapSetBackColor(mMapHandle, QColor(255,255,255).rgb());
	pCanvas->setMapHandle(mMapHandle);

	adjustScrollSize();
	adjustScrollValues();

	createNavigation();
}

MapLayer *MapView::createLayer(QString rscName, QString name)
{
	mLastLayerId++;
	MapLayer *ml = new MapLayer(mLastLayerId, rscName, this);
	ml->setLayerName(name);
	mLayersModel->addLayer( ml );
	return ml;
}

double MapView::scale()
{
	return mapGetShowScale(mapHandle());
}

QWidget *MapView::detachNavigation()
{
	if(!pNavigation)
	{
		createNavigation();
	}

	pNavigation->setParent(0);
	return pNavigation;
}

void MapView::attachNavigation()
{
	if(!pNavigation)
	{
		createNavigation();
	}

	pNavigation->setParent(this);
}

void MapView::createNavigation()
{
	pNavigation = new MapNavigation(this);
	connect(pNavigation, SIGNAL(navigationMoved(QPoint)), this, SLOT(moveMapTopLeft(QPoint)));
	pNavigation->setPixmap( pCanvas->mapPreview( 300 ) );
	pNavigation->show();
}

bool MapView::checkDirs()
{
	if(mRscDir.isEmpty())
	{
		mRscDir = "./map/rsc";
	}

	if(mSitDir.isEmpty())
	{
		mSitDir = "./map/sit";
	}

	if(QDir(mRscDir).isRelative())
	{
		QDir d = QDir::current();
		d.cd(mRscDir);
		if(!d.exists())
		{
			d.mkpath( d.absolutePath() );
		}

		mRscDir = d.absolutePath();
	}

	if(QDir(mSitDir).isRelative())
	{
		QDir d = QDir::current();
		d.cd(mSitDir);
		if(!d.exists())
		{
			d.mkpath( d.absolutePath() );
		}

		mSitDir = d.absolutePath();
	}

	return QDir(mRscDir).exists() && QDir(mSitDir).exists();
}

void MapView::setScale(double scale)
{
	QPoint point = pCanvas->mapTopLeft();

	long x = point.x() + pCanvas->width() / 2;
	long y = point.y() + pCanvas->height() / 2;

	mapSetViewScale(mMapHandle, &x, &y, scale);

	x -= pCanvas->width() / 2;
	y -= pCanvas->height() / 2;

	pCanvas->setMapTopLeft(QPoint(x, y));

	adjustScrollSize();
	adjustScrollValues();
	adjustNavigation();

	emit scaleChanged(scale);
}

void MapView::setNavigationVisible(bool visible)
{
	pNavigation->setVisible(visible);
}

void MapView::onScrollMap()
{
	QPoint p(pHorizontalScroll->value(), pVerticalScroll->value());
	moveMapTopLeft(p);
	pNavigation->moveFrame(pCanvas->mapTopLeft());
}

void MapView::adjustScrollSize()
{
	QSize mapSize = mapSizePx();

	pVerticalScroll->setVisible( mapSize.height() > pCanvas->height());

	if(mapSize.height() > pCanvas->height())
	{
		pVerticalScroll->setPageStep( pCanvas->width() );
		pVerticalScroll->setMaximum( mapSize.height() - pCanvas->height() );
	}

	pHorizontalScroll->setVisible( mapSize.width() > pCanvas->width());

	if(mapSize.width() > pCanvas->width())
	{
		pHorizontalScroll->setPageStep( pCanvas->height() );
		pHorizontalScroll->setMaximum( mapSize.width() - pCanvas->width() );
	}
}

void MapView::adjustScrollValues()
{
	pHorizontalScroll->setValue( pCanvas->mapTopLeft().x());
	pVerticalScroll->setValue( pCanvas->mapTopLeft().y());
}

void MapView::adjustNavigation()
{
	if(pNavigation->parent() == this)
	{
		pNavigation->move( width() - pNavigation->width() - 25, 25);
	}

	pNavigation->setSizes(mapSizePx(), pCanvas->size());
	pNavigation->moveFrame(pCanvas->mapTopLeft());
}

bool MapView::eventFilter(QObject *obj, QEvent *e)
{
	Q_ASSERT(obj == pCanvas);

	if(e->type() == QEvent::Wheel)
	{
		processWheelEvent(e);
		return true;
	}
	else if(e->type() == QEvent::MouseMove)
	{
		processMouseMoveEvent(e);
		return true;
	}
	else if(e->type() == QEvent::MouseButtonPress)
	{
		processMousePressEvent(e);
		return true;
	}
	else if(e->type() == QEvent::MouseButtonRelease)
	{
		processMouseReleaseEvent(e);
		return true;
	}
	else if(e->type() == QEvent::MouseButtonDblClick)
	{
		processMouseDoubleClickEvent(e);
		return true;
	}

	return QWidget::eventFilter(obj, e);
}

void MapView::keyPressEvent(QKeyEvent *keyEvent)
{
	if(keyEvent->key() == Qt::Key_Left)
	{
		scrollMapTopLeft(-pCanvas->width()*0.25, 0);
		adjustScrollValues();
	}
	else if(keyEvent->key() == Qt::Key_Right)
	{
		scrollMapTopLeft(pCanvas->width()*0.25, 0);
		adjustScrollValues();
	}
	else if(keyEvent->key() == Qt::Key_Up)
	{
		scrollMapTopLeft(0, -pCanvas->height()*0.25);
		adjustScrollValues();
	}
	else if(keyEvent->key() == Qt::Key_Down)
	{
		scrollMapTopLeft(0, pCanvas->height()*0.25);
		adjustScrollValues();
	}
	else if(keyEvent->key() == Qt::Key_PageUp)
	{
		scrollMapTopLeft(0, -pCanvas->height());
		adjustScrollValues();
	}
	else if(keyEvent->key() == Qt::Key_PageDown)
	{
		scrollMapTopLeft(0, pCanvas->height());
		adjustScrollValues();
	}
}

void MapView::resizeEvent(QResizeEvent *e)
{
	QWidget::resizeEvent(e);

	adjustScrollSize();
	adjustNavigation();
}

void MapView::processWheelEvent(QEvent *e)
{
	QWheelEvent *wheelEvent = dynamic_cast<QWheelEvent*>(e);
	if(!wheelEvent)
	{
		return;
	}

	long scale = mapGetShowScale(mMapHandle);
	scale *= wheelEvent->delta() < 0 ? 1.1 : 0.9;

	setScale(scale);
}

void MapView::processMousePressEvent(QEvent *e)
{
	QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent*>(e);
	if(!mouseEvent)
	{
		return;
	}

	if(mouseEvent->button() == Qt::LeftButton)
	{
		mIsDragged = true;
		mDragStartPoint = mouseEvent->pos();
	}
}

void MapView::processMouseMoveEvent(QEvent *e)
{
	QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent*>(e);
	if(!mouseEvent)
	{
		return;
	}

	if(mIsDragged)
	{
		int dx = mDragStartPoint.x() - mouseEvent->x();
		int dy = mDragStartPoint.y() - mouseEvent->y();

		scrollMapTopLeft(dx, dy);

		mDragStartPoint = mouseEvent->pos();

		adjustScrollValues();
		pNavigation->moveFrame(pCanvas->mapTopLeft());
	}

	double x = pCanvas->mapTopLeft().x() + mouseEvent->x();
	double y = pCanvas->mapTopLeft().y() + mouseEvent->y();

	mapPictureToPlane(mapHandle(), &x, &y);
	mapPlaneToGeo(mapHandle(), &x, &y);

	double lat = x * 180. / M_PI;
	double lng = y * 180. / M_PI;

	emit coordChanged( Coord(lat, lng));
}

void MapView::processMouseReleaseEvent(QEvent *e)
{
	QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent*>(e);
	if(!mouseEvent)
	{
		return;
	}

	mIsDragged = false;
	mDragStartPoint = QPoint();
}

void MapView::processMouseDoubleClickEvent(QEvent *e)
{
	QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent*>(e);
	if(!mouseEvent)
	{
		return;
	}

	QPoint p = pCanvas->mapTopLeft() + mouseEvent->pos() - pCanvas->rect().center();

	moveMapTopLeft(p);
	pNavigation->moveFrame(p);
}

QSize MapView::mapSizePx() const
{
	long width = 0;
	long height = 0;

	mapGetPictureSize(mMapHandle, &width, &height);

	return QSize(width, height);
}

void MapView::moveMapTopLeft(QPoint pos)
{
	QSize mapSize = mapSizePx();

	if(pos.x() < 0)
	{
		pos.setX(0);
	}
	else if(pos.x() + pCanvas->width() > mapSize.width())
	{
		pos.setX(mapSize.width() - pCanvas->width() );
	}

	if(pos.y() < 0)
	{
		pos.setY(0);
	}
	else if(pos.y() + pCanvas->height() > mapSize.height())
	{
		pos.setY(mapSize.height() - pCanvas->height());
	}

	pCanvas->setMapTopLeft( pos );
}

void MapView::scrollMapTopLeft(int dx, int dy)
{
	QPoint point = pCanvas->mapTopLeft();
	QPoint p(point.x() + dx, point.y() + dy);
	moveMapTopLeft(p);
}
