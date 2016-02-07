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
#include <QLabel>
#include <QDebug>
#include <QKeyEvent>
#include <QScrollBar>
#include <QGridLayout>
#include <QMessageBox>
#include <QApplication>

using namespace Map2;

MapView::MapView(QString sitDir, QString rscDir, QWidget *parent)
	: QWidget(parent), pTools(0), mMapHandle(0), mSelect(0), mIsDragged(false), mLastLayerId(0),
	  mRscDir(rscDir), mSitDir(sitDir), pActiveLayer(0), pHelper(0)
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
	if(mMapHandle <= 0)
	{
		return;
	}

	mapSetBackColor(mMapHandle, QColor(255,255,255).rgb());

	mSelect = mapCreateMapSelectContext(mMapHandle);
	mapSelectObject(mSelect, -1, 0);

	pCanvas->setMapHandle(mMapHandle, mSelect);

	QList<int> hiddenLayers = Map2::LayersSettingsDialog::hiddenLayers();
	Map2::LayersSettingsDialog::setHiddenLayers(mapHandle(), hiddenLayers);

	emit mapLoaded();

	adjustScrollSize();
	adjustScrollValues();
}

Map2::MapLayer *MapView::createLayer(QString rscName, QString name)
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

Map2::MapLayer *MapView::createTempLayer(QString rscName, QString name)
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

	MapLayer *l = new MapLayer(-1, rscName, this, true);
	l->setLayerName(name);
	return l;
}

double MapView::scale()
{
	return pCanvas->scale();
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
		long key = mapObjectKey(found);

		MapLayer *l = mLayersModel->layerByHandle( site);
		if(l && !l->isLocked())
		{
			MapObject *obj = l->objectByMapKey(key);
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
	pActiveLayer = layer;
}

void MapView::setActiveLayer(int index)
{
	pActiveLayer = mLayersModel->layerAt(index);
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

	long scale = mapGetShowScale(mMapHandle);
	scale *= wheelEvent->delta() < 0 ? 1.1 : 0.9;

	setScale(scale);
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
	if(objs.isEmpty())
	{
		pCanvas->setToolTip("");
	}
	else
	{
		pCanvas->setToolTip(objs.first()->name());
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

MapHelper *MapView::helper()
{
	if(!pHelper)
	{
		///TODO: Здесь и ниже - временный костыль. Переменную mMkmInPix нужно вынести в настройки
		double mkmInPix = 475000 / 1920;
	//	double mkmInPix = 340000 / 1280;

		pHelper = new MapHelper(mMapHandle, mkmInPix);
	}

	return pHelper;
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
