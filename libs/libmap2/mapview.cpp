#include "gis.h"
#include "mapview.h"
#include "mapruler.h"
#include "maplayer.h"
#include "maphelper.h"
#include "mapcanvas.h"
#include "rscviewer.h"
#include "layersmodel.h"
#include "rscselectdialog.h"

#include "objects/mapobject.h"
#include "objects/maplineobject.h"
#include "objects/mapvectorobject.h"

#include "widgets/maptoolbar.h"
#include "widgets/calibrationdialog.h"
#include "widgets/layerssettingsdialog.h"

#include <QDir>
#include <QUuid>
#include <QLabel>
#include <QDebug>
#include <QKeyEvent>
#include <QScrollBar>
#include <QGridLayout>
#include <QMessageBox>
#include <QApplication>

using namespace Map2;

MapView::MapView(QString sitDir, QString rscDir, QWidget *parent)
	: QWidget(parent), pTools(0), mMapHandle(0), mIsDragged(false), mLastLayerId(0),
	  mRscDir(rscDir), mSitDir(sitDir), pActiveLayer(0), pHelper(0)
{
	setFocusPolicy(Qt::TabFocus);

	pVerticalScroll = new QScrollBar(Qt::Vertical, this);
	pHorizontalScroll = new QScrollBar(Qt::Horizontal, this);

	pCanvas = new MapCanvas(this);
	pCanvas->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	pCanvas->installEventFilter( this );
	pCanvas->setMouseTracking(true);

	pLayersModel = new LayersModel(this);
	connect(pLayersModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)), pCanvas, SLOT(queueRepaint()));

	QGridLayout *lay = new QGridLayout(this);
	lay->addWidget(pCanvas, 0, 0);
	lay->addWidget(pVerticalScroll, 0, 1);
	lay->addWidget(pHorizontalScroll, 1, 0);
	lay->setSpacing(1);
	lay->setContentsMargins( QMargins() );

	connect(pVerticalScroll, SIGNAL(sliderMoved(int)), this, SLOT(onScrollMap()));
	connect(pVerticalScroll, SIGNAL(actionTriggered(int)), this, SLOT(onScrollMap()));
	connect(pHorizontalScroll, SIGNAL(sliderMoved(int)), this, SLOT(onScrollMap()));
	connect(pHorizontalScroll, SIGNAL(actionTriggered(int)), this, SLOT(onScrollMap()));

	if(!checkDirs())
	{
		qDebug()<<"Ошибка! Некорректные каталоги классификаторов и пользовательских карт.";
	}

	mapSetCommonRscPath( qPrintable(mRscDir) );

	double dpm = CalibrationDialog::dpm();
	mapSetScreenPrecision( (long)dpm );
}

MapView::~MapView()
{
	if(pHelper)
	{
		delete pHelper;
		pHelper = 0;
	}

	pLayersModel->deleteLater();

	if(mMapHandle > 0)
	{
		mapCloseData( mMapHandle );
		mMapHandle = 0;
	}
}

void MapView::openMap(QString mapFullPath)
{
	if(mMapHandle > 0)
	{
		mapCloseData(mMapHandle);
		mMapHandle = 0;
	}

	mMapFilePath = mapFullPath;

	mMapHandle = mapOpenData(qPrintable(mapFullPath), 0);
	if(mMapHandle <= 0)
	{
		return;
	}

	mapSetBackColor(mMapHandle, QColor(255,255,255).rgb());

	pCanvas->setMapHandle(mMapHandle);

	QFileInfo f(mapFullPath);

	emit mapLoaded(f.baseName());

	adjustScrollSize();
	adjustScrollValues();
}

Map2::MapLayer *MapView::createLayer(QString rscName, QString key, QString name, bool temp)
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

	if(key.isEmpty())
	{
		key = QUuid::createUuid().toString();
	}

	if(pLayersModel->layerByKey(key) != 0)
	{
		return 0;
	}

	if(name.isEmpty())
	{
		name = "Новый слой";
	}

	Map2::MapLayer *layer = new Map2::MapLayer(rscName, key, name, this, temp);
	pLayersModel->addLayer( layer );

	return layer;
}

double MapView::scale() const
{
	return pCanvas->scale();
}

double MapView::scaleRatio() const
{
	return pCanvas->scaleRatio();
}

Map2::Coord MapView::coordinateAtPoint(const QPoint &screenCoord)
{
	QPoint pictureCoord = pCanvas->mapTopLeft() + screenCoord;

	return helper()->pictureToGeo(pictureCoord);
}

Map2::Coord MapView::screenCenterCoordinate()
{
	QPoint p = pCanvas->mapTopLeft() + QPoint(pCanvas->rect().center());

	return helper()->pictureToGeo(p);
}

QList<Map2::MapObject *> MapView::objectsAtPoint(QPoint point, double radiusPx)
{
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
		MapLayer *l = pLayersModel->layerByHandle( site);
		if(l && !l->isLocked())
		{
			MapObject *obj = l->objectByHandle(found);
			if(obj)
			{
				result << obj;
			}
		}
		found = mapWhatObject(mMapHandle, hobj, &frame, WO_BACK, PP_PICTURE);
	}

	mapFreeObject(hobj);

	return result;
}

void Map2::MapView::addObjectToSelection(Map2::MapObject *obj)
{
	mSelectedObjects << obj;
	obj->setSelected();
}

QToolBar *MapView::toolBar()
{
	if(!pTools)
	{
		pTools = new MapToolBar(this);
		connect(pTools, SIGNAL(leftClick(QPoint)), this, SIGNAL(mouseLeftClick(QPoint)));
		connect(pTools, SIGNAL(rightClick(QPoint)), this, SIGNAL(mouseRightClick(QPoint)));
	}

	return pTools->toolBar();
}

QPixmap MapView::mapPreview(int width)
{
	return pCanvas->mapPreview(width);
}

QPixmap MapView::objectPreview(MapVectorObject *obj, QSize size, double scale)
{
	if(!obj)
	{
		QPixmap pm(size);
		pm.fill( QColor( Qt::white ));
		return pm;
	}

	long x1 = 0;
	long y1 = 0;

	long oldScale = this->scale();
	mapSetViewScale(mapHandle(), &x1, &y1, scale);

	double ratio = scaleRatio();
	if(ratio > 1)
	{
		ratio = 1;
	}

	QRectF objRect =obj->sizePix();
	QSize objSize = QSize(objRect.width() * ratio, objRect.height() * ratio);

	QPoint coord = helper()->planeToPicture( obj->coordinatePlane() );
	coord += QPoint( objSize.width() /2, objSize.height() / 2) - (objRect.topLeft() * ratio).toPoint();

	CoordPlane coordPlane = helper()->pictureToPlane( coord );

	if(objSize.width() > size.width())
	{
		size.setWidth( objSize.width() * 1.2);
	}

	if(objSize.height() > size.height())
	{
		size.setHeight( objSize.height() * 1.2);
	}

	const QPixmap &pm = canvas()->objectPreview( coordPlane, size);

	mapSetViewScale(mapHandle(), &x1, &y1, oldScale);

	return pm;
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

void MapView::calibrate()
{
	CalibrationDialog cld(this);
	if(!cld.exec())
	{
		return;
	}

	double dpm = CalibrationDialog::dpm();
	double mkmInPx = CalibrationDialog::mkmInPx();

	mapSetScreenPrecision( (long)dpm );
	helper()->setMkmInPxRatio( mkmInPx );

	canvas()->queueRepaint();
}

void MapView::zoomIn()
{
	long scale = mapGetShowScale(mMapHandle);
	scale *= 1.1;
	setScale(scale);
}

void MapView::zoomOut()
{
	long scale = mapGetShowScale(mMapHandle);
	scale *= 0.9;
	setScale(scale);
}

void MapView::setScale(double scale)
{
	if(mapSizePx().height() <= height() && scale > pCanvas->scale())
	{
		return;
	}

	pCanvas->setScale(scale);

	QPoint topLeft = pCanvas->mapTopLeft();
	QSize mapSize = mapSizePx();
	if(topLeft.x() < 0)
	{
		topLeft.setX(0);
	}
	else if(topLeft.x() > mapSize.width() - pCanvas->width())
	{
		topLeft.setX( mapSize.width() - pCanvas->width() );
	}

	if(topLeft.y() < 0)
	{
		topLeft.setY(0);
	}
	else if(topLeft.y() > mapSize.height() - pCanvas->height())
	{
		topLeft.setY( mapSize.height() - pCanvas->height() );
	}

	if(pCanvas->mapTopLeft() != topLeft)
	{
		moveMapTopLeft( topLeft );
	}

	adjustScrollSize();
	adjustScrollValues();

	emit scaleChanged(pCanvas->scale());
}

void MapView::setCenter(QPoint pictureCoord)
{
	QPoint p = pictureCoord - pCanvas->rect().center();

	moveMapTopLeft(p);
}

void MapView::setCenter(Map2::Coord geoCoord)
{
	QPoint p = helper()->geoToPicture(geoCoord);
	setCenter(p);
}

void MapView::setCenter(Map2::CoordPlane planeCoord)
{
	QPoint p = helper()->planeToPicture(planeCoord);
	setCenter(p);
}

void MapView::clearSelection()
{
	while(!mSelectedObjects.isEmpty())
	{
		mSelectedObjects.takeFirst()->setSelected(false);
	}
}

void MapView::setActiveLayer(Map2::MapLayer *layer)
{
	if(!layer || layer == pActiveLayer)
	{
		return;
	}

	pActiveLayer = layer;
	emit activeLayerChanged(layer);
}

void MapView::setActiveLayer(int index)
{
	setActiveLayer(pLayersModel->layerAt(index));
}

Map2::MapLayer *MapView::activeLayer()
{
	return pActiveLayer;
}

void MapView::onScrollMap()
{
	QPoint p(pHorizontalScroll->value(), pVerticalScroll->value());
	moveMapTopLeft(p);
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
	emit resized(e->size());
}

void MapView::processWheelEvent(QEvent *e)
{
	QWheelEvent *wheelEvent = dynamic_cast<QWheelEvent*>(e);
	Q_ASSERT(wheelEvent);

	if(wheelEvent->delta() < 0)
	{
		zoomIn();
	}
	else
	{
		zoomOut();
	}
}

void MapView::processMousePressEvent(QEvent *e)
{
	QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent*>(e);
	Q_ASSERT(mouseEvent);

	if(pTools && !pTools->processMousePressEvent(mouseEvent))
	{
		return;
	}

	if(mouseEvent->button() == Qt::RightButton)
	{
		mIsDragged = true;
		mDragStartPoint = mouseEvent->pos();
		pCanvas->setCursor( QCursor(Qt::ClosedHandCursor) );
	}
}

void MapView::processMouseMoveEvent(QEvent *e)
{
	QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent*>(e);
	Q_ASSERT(mouseEvent);

	QList<MapObject*> objs = objectsAtPoint(mouseEvent->pos(), 5);
	if(!objs.isEmpty())
	{
		emit toolTipRequest(mouseEvent->pos(), objs.first());
	}

	if(pTools && !pTools->processMouseMoveEvent(mouseEvent))
	{
		return;
	}

	if(mIsDragged)
	{
		if(QLineF(mDragStartPoint, mouseEvent->pos()).length() > 20 )
		{
			QPoint delta = mDragStartPoint - mouseEvent->pos();

			scrollMapTopLeft(delta.x(), delta.y());

			mDragStartPoint = mouseEvent->pos();

			adjustScrollValues();
		}
		pCanvas->setCursor( QCursor(Qt::ClosedHandCursor) );
	}
	else
	{
		pCanvas->setCursor( QCursor(Qt::OpenHandCursor) );
	}

	QPoint p = pCanvas->mapTopLeft() + mouseEvent->pos();

	emit coordChanged( helper()->pictureToGeo(p) );
}

void MapView::processMouseReleaseEvent(QEvent *e)
{
	QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent*>(e);
	Q_ASSERT(mouseEvent);

	if(pTools && !pTools->processMouseReleaseEvent(mouseEvent))
	{
		return;
	}

	if(mouseEvent->button() == Qt::RightButton)
	{
		mIsDragged = false;
		mDragStartPoint = QPoint();
		pCanvas->setCursor( QCursor(Qt::OpenHandCursor) );
	}
}

void MapView::processMouseDoubleClickEvent(QEvent *e)
{
	QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent*>(e);
	Q_ASSERT(mouseEvent);

	if(pTools && !pTools->processMouseDoubleClickEvent(mouseEvent))
	{
		return;
	}

	setCenter(pCanvas->mapTopLeft() + mouseEvent->pos());
}

QSize MapView::mapSizePx() const
{
	long width = 0;
	long height = 0;

	mapGetPictureSize(mMapHandle, &width, &height);

	return QSize(width, height);
}

CoordPlane MapView::bottomLeftPlane() const
{
	DFRAME dfr;
	mapGetTotalBorder(mMapHandle, &dfr, PP_PLANE);
	return CoordPlane(dfr.X1, dfr.Y1);
}

CoordPlane MapView::topRightPlane() const
{
	DFRAME dfr;
	mapGetTotalBorder(mMapHandle, &dfr, PP_PLANE);
	return CoordPlane(dfr.X2, dfr.Y2);
}

MapHelper *MapView::helper()
{
	if(!pHelper)
	{
		double mkmInPx = CalibrationDialog::mkmInPx();

		pHelper = new MapHelper(mMapHandle, mkmInPx);
	}

	return pHelper;
}

QRect MapView::visibleRect() const
{
	QRect rect;
	rect.setTopLeft( pCanvas->mapTopLeft() );
	rect.setSize( pCanvas->size() );

	return rect;
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

	emit mapCenterScrolled( screenCenterCoordinate() );
}

void MapView::scrollMapTopLeft(int dx, int dy)
{
	QPoint point = pCanvas->mapTopLeft();
	QPoint p(point.x() + dx, point.y() + dy);
	moveMapTopLeft(p);
}
