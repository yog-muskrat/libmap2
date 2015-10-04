#ifndef MAPCANVAS_H
#define MAPCANVAS_H

#include <QTimer>
#include <QWidget>

#include "gis.h"

class MapCanvas : public QWidget
{
	Q_OBJECT
public:
	explicit MapCanvas(QWidget *parent = 0);
	~MapCanvas();

	HMAP mapHandle() const { return mMapHandle; }
	void setMapHandle(const HMAP &hnd, const HSELECT &select);
	QPixmap mapPreview(int width);
	QPoint mapTopLeft() const {return mMapTopLeft;}

public slots:
	void setMapTopLeft(const QPoint &point);
	void setScale(double scale);
	double scale() const;

	void setSelectionColor(const QColor &color);

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

	COLORREF mSelectColor;
	HSELECT mSelect;
};

#endif // MAPCANVAS_H
