#include "mapcanvas.h"

#include <QRect>
#include <QDebug>
#include <QPainter>
#include <QWheelEvent>
#include <QElapsedTimer>

using namespace Map2;

MapCanvas::MapCanvas(QWidget *parent) :
	QWidget(parent),
	mMapHandle(-1),
	mMapBitDepth(mapGetMapScreenDepth()),
	mMapTopLeft(QPoint(0,0)),
	mRepaint(false)
{
	connect(&mRepaintTi, SIGNAL(timeout()), this, SLOT(onRepaintTimer()));
	mRepaintTi.setSingleShot(true);

	mZoomRectPen.setColor( QColor(Qt::green) );
	mZoomRectPen.setWidth(2);
	mZoomRectPen.setCapStyle(Qt::RoundCap);
	mZoomRectPen.setJoinStyle( Qt::RoundJoin );

	mRepaintTi.start(30);
}

MapCanvas::~MapCanvas()
{

}

void MapCanvas::setMapHandle(const HMAP &hnd)
{
	mMapHandle = hnd;

	mRepaint = true;
}

QPixmap MapCanvas::mapPreview(int width)
{
	if( mapHandle() <= 0)
	{
		return QPixmap(width, width);
	}

	long mapWidth = mapGetPictureWidth(mapHandle());

	double ratio = (double)mapWidth / (double)width;

	long mapScale = mapGetShowScale(mapHandle());
	long newScale = mapScale * ratio;

	long x = 0;
	long y = 1;

	mapSetViewScale(mapHandle(), &x, &y, newScale);

	long mapNewWidth = mapGetPictureWidth(mapHandle());
	long mapNewHeight = mapGetPictureHeight(mapHandle());

	int bytesPerLine = static_cast<int>(mapNewWidth * mMapBitDepth / 8);
	int size = bytesPerLine * mapNewHeight;

	char *dataBytes = AllocateTheMemory(size);
	memset(dataBytes, 0x0, size);

	XIMAGEDESC ximage;
	ximage.Point = dataBytes;
	ximage.Width = static_cast<long>(mapNewWidth);
	ximage.Height = static_cast<long>(mapNewHeight);
	ximage.Depth = mMapBitDepth;
	ximage.CellSize = mMapBitDepth / 8;
	ximage.RowSize = static_cast<long>(bytesPerLine);

	RECT rect;
	rect.top = 0;
	rect.left = 0;
	rect.bottom = static_cast<long>(mapNewHeight);
	rect.right = static_cast<long>(mapNewWidth);

	mapPaintToXImage(mapHandle(), &ximage, 0, 0, &rect);
	mapSetViewScale(mapHandle(), &x, &y, mapScale);

	QImage img = QImage((uchar *) dataBytes, mapNewWidth, mapNewHeight, QImage::Format_RGB32).copy();
	FreeTheMemory(dataBytes);

	QPixmap pm = QPixmap::fromImage(img);

	return pm;
}

void MapCanvas::setZoomRect(QRect rect)
{
	mZoomRect = rect;
	mRepaint = true;
}

void MapCanvas::setMapTopLeft(const QPoint &point)
{
	mMapTopLeft = point;
	mRepaint = true;
}

void MapCanvas::setScale(double scale)
{
	QPoint point = mapTopLeft() + rect().center();

	long x = point.x();
	long y = point.y();

	if(scale <= 0)
	{
		scale = mapGetMapScale(mMapHandle);
	}

	mapSetViewScale(mapHandle(), &x, &y, scale);

	x -= rect().center().x();
	y -= rect().center().y();

	setMapTopLeft(QPoint(x, y));
}

double MapCanvas::scale() const
{
	return mapGetShowScale( mapHandle() );
}

void MapCanvas::queueRepaint()
{
	mRepaint = true;
}

void MapCanvas::paintEvent(QPaintEvent *e)
{
	if(mapHandle() <= 0 )
	{
		QWidget::paintEvent(e);
		return;
	}

//	QElapsedTimer ti;
//	ti.start();

	QRect drawRect;
	drawRect.setTop( mapTopLeft().y() );
	drawRect.setLeft( mapTopLeft().x() );
	drawRect.setHeight( height() );
	drawRect.setWidth( width() );

	int bytesPerLine = static_cast<int>(drawRect.width() * mMapBitDepth / 8);
	int size = bytesPerLine * drawRect.height();

	char *dataBytes = AllocateTheMemory(size);
	memset(dataBytes, 0x0, size);

	XIMAGEDESC ximage;
	ximage.Point = dataBytes;
	ximage.Width = static_cast<long>(drawRect.width());
	ximage.Height = static_cast<long>(drawRect.height());
	ximage.Depth = mMapBitDepth;
	ximage.CellSize = mMapBitDepth / 8;
	ximage.RowSize = static_cast<long>(bytesPerLine);

	RECT rect;
	rect.top = drawRect.top();
	rect.left = drawRect.left();
	rect.bottom = static_cast<long>(drawRect.bottom());
	rect.right = static_cast<long>(drawRect.right());

	mapPaintToXImage(mMapHandle, &ximage, 0, 0, &rect);

	QImage img((uchar *) dataBytes, drawRect.width(), drawRect.height(), QImage::Format_RGB32);

	QPainter p(this);
	p.drawImage(0, 0, img);
	p.setPen( mZoomRectPen);
	p.drawRect(mZoomRect);

	FreeTheMemory(dataBytes);

	mRepaint = false;

//	qDebug()<<"Repaint in"<<ti.elapsed()<<"ms";
}

void MapCanvas::onRepaintTimer()
{
	if(mRepaint)
	{
		repaint();
	}

	mRepaintTi.start(30);
}
