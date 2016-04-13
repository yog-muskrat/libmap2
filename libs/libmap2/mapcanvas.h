#ifndef MAPCANVAS_H
#define MAPCANVAS_H

#include <QPen>
#include <QTimer>
#include <QWidget>

#include "gis.h"
#include "mapstructs.h"

namespace Map2
{

class MapCanvas : public QWidget
{
	Q_OBJECT
public:
	explicit MapCanvas(QWidget *parent = 0);
	~MapCanvas();

	HMAP mapHandle() const { return mMapHandle; }
	void setMapHandle(const HMAP &hnd);
	QPixmap mapPreview(int width);
	QPixmap objectPreview(CoordPlane coord, QSize picSize) const;
	QPoint mapTopLeft() const {return mMapTopLeft;}

	void setZoomRect(QRect rect);
	QRect zoomRect() const {return mZoomRect;}

	double scale() const;
	double scaleRation() const;

public slots:
	void setMapTopLeft(const QPoint &point);
	void setScale(double scale);

	/*!
	 * \brief Выставляет флаг перерисовки.
	 */
	void queueRepaint();

protected:
	virtual void paintEvent(QPaintEvent *e);

private slots:
	void onRepaintTimer();

private:
	HMAP mMapHandle;
	int mMapBitDepth;
	QPoint mMapTopLeft;
	bool mRepaint; //!< Флаг необходимости перерисовки карты по таймеру.
	QTimer mRepaintTi; //!< Таймер перерисовки;

	QRect mZoomRect; //!< Прямоугольник для интсрумента "Приблизить область".
	QPen mZoomRectPen;
};
}
#endif // MAPCANVAS_H
