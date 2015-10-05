#include "mapview.h"
#include "maplayer.h"
#include "maptools.h"
#include "mapcanvas.h"
#include "mapobject.h"
#include "maptoolbar.h"
#include "layersmodel.h"
#include "mapnavigation.h"
#include "rscselectdialog.h"

#include <QDir>
#include <QLabel>
#include <QDebug>
#include <QKeyEvent>
#include <QScrollBar>
#include <QGridLayout>
#include <QApplication>

MapView::MapView(QString sitDir, QString rscDir, QWidget *parent)
	: QWidget(parent), pNavigation(0), pToolBar(0), mMapHandle(0), mSelect(0), mIsDragged(false), mLastLayerId(0),
	  mRscDir(rscDir), mSitDir(sitDir),mTool(None)
{
	setFocusPolicy(Qt::TabFocus);

	pVerticalScroll = new QScrollBar(Qt::Vertical, this);
	pHorizontalScroll = new QScrollBar(Qt::Horizontal, this);

	pCanvas = new MapCanvas(this);
	pCanvas->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	pCanvas->installEventFilter( this );
	pCanvas->setMouseTracking(true);

	mLayersModel = new LayersModel(this);
	connect(mLayersModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)), pCanvas, SLOT(queueRepaint()));

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

	if(mSelect > 0)
	{
		mapDeleteSelectContext(mSelect);
	}

	if(mMapHandle > 0)
	{
		mapCloseData( mMapHandle );
	}
}

void MapView::openMap(QString mapFullPath)
{
	if(mSelect > 0)
	{
		mapDeleteSelectContext(mSelect);
		mSelect = 0;
	}

	if(mMapHandle > 0)
	{
		mapCloseData(mMapHandle);
		mMapHandle = 0;
	}

	mMapHandle = mapOpenData(qPrintable(mapFullPath), 0);
	mapSetBackColor(mMapHandle, QColor(255,255,255).rgb());

	mSelect = mapCreateMapSelectContext(mMapHandle);
	mapSelectObject(mSelect, -1, 0);

	pCanvas->setMapHandle(mMapHandle, mSelect);

	adjustScrollSize();
	adjustScrollValues();

	createNavigation();
}

MapLayer *MapView::createLayer(QString rscName, QString name)
{
	if(rscName.isEmpty())
	{
		RscSelectDialog dlg;
		if(!dlg.exec() || dlg.selectedRsc().isEmpty())
		{
			qDebug()<<"*** СОЗДАНИЕ СЛОЯ: Не выбран классификатор.";
			return 0;
		}

		rscName = dlg.selectedRsc();
	}

	mLastLayerId++;
	MapLayer *ml = new MapLayer(mLastLayerId, rscName, this);
	if(name.isEmpty())
	{
		name = QString("Layer %0").arg(mLastLayerId);
	}
	ml->setLayerName(name);
	mLayersModel->addLayer( ml );
	return ml;
}

double MapView::scale()
{
	return pCanvas->scale();
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

QList<MapObject *> MapView::objectsAtPoint(QPoint point, double radiusPx)
{
	mapSelectObject(mSelect, -1, 0);

	HOBJ hobj = mapCreateObject(mMapHandle);

	point += pCanvas->mapTopLeft();
	MAPDFRAME frame;
	frame.X1 = point.x() - radiusPx;
	frame.Y1 = point.y() - radiusPx;
	frame.X2 = point.x() + radiusPx;
	frame.Y2 = point.y() + radiusPx;

	HOBJ found = mapWhatObject(mMapHandle, hobj, &frame, WO_LAST, PP_PICTURE);

	QList<MapObject*> result;

	while(found)
	{
		HSITE site = mapGetObjectSiteIdent(mMapHandle, found);
		long index = mapObjectCode(found);

		MapLayer *l = mLayersModel->layerByHandle( site);
		if(l)
		{
			MapObject *obj = l->objectByMapIndex(index);
			if(obj)
			{
				obj->setSelected( !obj->selected() );
				result << obj;
			}
		}
		found = mapWhatObject(mMapHandle, hobj, &frame, WO_BACK, PP_PICTURE);
	}

	mapFreeObject(hobj);

	return result;
}

QToolBar *MapView::toolBar()
{
	if(!pToolBar)
	{
		MapToolBar *tb = new MapToolBar(this);
		connect(tb, SIGNAL(toolSelected(MapView::Tools)), this, SLOT(setCurrentTool(MapView::Tools)));
		pToolBar = tb;
	}

	return pToolBar;
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

	if( QDir(mSitDir).isRelative() )
	{
		QDir d( QDir::currentPath() + "/" + mSitDir );

		if(!d.exists())
		{
			d.mkpath( d.absolutePath() );
		}

		mSitDir = d.absolutePath();
	}

	return QDir(mRscDir).exists() && QDir(mSitDir).exists();
}

void MapView::zoomToRect(const QRect &rect)
{
	if(rect.width() == 0 && rect.height()==0)
	{
		return;
	}

	QRect selfRect = pCanvas->rect();

	double selfRatio = (double)selfRect.width() / (double)selfRect.height();
	double rectRatio = (double)rect.width() / (double)rect.height();


	if(selfRatio > rectRatio)
	{
		int w = (double)rect.height() * (double)selfRect.width() / (double)selfRect.height();
		selfRect.setHeight( rect.height() );
		selfRect.setWidth( w );
	}
	else
	{
		int h = (double)rect.width() * (double)selfRect.height() / (double)selfRect.width();
		selfRect.setWidth( rect.width() );
		selfRect.setHeight( h );
	}

	selfRect.moveCenter( rect.center() );
	QPoint p = rect.center() - pCanvas->rect().center();
	scrollMapTopLeft( p.x(), p.y() );

	double newScale = scale() * selfRect.width() / pCanvas->width();
	setScale(newScale);
}

void MapView::setScale(double scale)
{
	pCanvas->setScale(scale);

	adjustScrollSize();
	adjustScrollValues();
	adjustNavigation();

	emit scaleChanged(scale);
}

void MapView::setNavigationVisible(bool visible)
{
	pNavigation->setVisible(visible);
}

void MapView::setCenter(QPoint pictureCoord)
{
	QPoint p = pictureCoord - pCanvas->rect().center();

	moveMapTopLeft(p);
	pNavigation->moveFrame(p);
}

void MapView::setCenter(Coord geoCoord)
{
	QPoint p = MapTools::geoToPicture(mapHandle(), geoCoord);
	setCenter(p);
}

void MapView::setCenter(CoordPlane planeCoord)
{
	QPoint p = MapTools::planeToPicture(mapHandle(), planeCoord);
	setCenter(p);
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

		if(mTool == MapView::RectZoom)
		{
			pCanvas->setZoomRect( QRect(mouseEvent->pos(), mouseEvent->pos()));
		}
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
		if(mTool == MapView::RectZoom)
		{
			QRect rect = pCanvas->zoomRect();
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
			pCanvas->setZoomRect(rect);
		}
		else
		{
			if(QLineF(mDragStartPoint, mouseEvent->pos()).length() > 20 )
			{
				int dx = mDragStartPoint.x() - mouseEvent->x();
				int dy = mDragStartPoint.y() - mouseEvent->y();

				scrollMapTopLeft(dx, dy);

				mDragStartPoint = mouseEvent->pos();

				adjustScrollValues();
				pNavigation->moveFrame(pCanvas->mapTopLeft());
			}
		}
	}

	double x = pCanvas->mapTopLeft().x() + mouseEvent->x();
	double y = pCanvas->mapTopLeft().y() + mouseEvent->y();

	mapPictureToPlane(mapHandle(), &x, &y);
	mapPlaneToGeo(mapHandle(), &x, &y);

	double lat = MapTools::radToDegree(x);
	double lng = MapTools::radToDegree(y);

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

	if(mTool == MapView::RectZoom && mouseEvent->button() == Qt::LeftButton)
	{
		zoomToRect( pCanvas->zoomRect() );
		pCanvas->setZoomRect(QRect(0,0,0,0));
	}
}

void MapView::processMouseDoubleClickEvent(QEvent *e)
{
	QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent*>(e);
	if(!mouseEvent)
	{
		return;
	}

	setCenter(pCanvas->mapTopLeft() + mouseEvent->pos());

	objectsAtPoint(mouseEvent->pos());
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
