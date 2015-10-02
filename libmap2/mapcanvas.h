#ifndef MAPCANVAS_H
#define MAPCANVAS_H

#include <QWidget>

#include "gis.h"

class MapCanvas : public QWidget
{
	Q_OBJECT
public:
	explicit MapCanvas(QWidget *parent = 0);

	HMAP mapHandle() const { return mMapHandle; }
	void setMapHandle(const HMAP &hnd);
	QPixmap mapPreview(int width);
	QPoint mapTopLeft() const {return mMapTopLeft;}

public slots:
	void setMapTopLeft(const QPoint &point);

protected:
	void paintEvent(QPaintEvent *e);

private:
	HMAP mMapHandle;
	int mMapBitDepth;
	QPoint mMapTopLeft;
};

#endif // MAPCANVAS_H
