#ifndef MAPNAVIGATION_H
#define MAPNAVIGATION_H

#include <QGraphicsView>

#include "mapstructs.h"

class QGraphicsScene;
class QGraphicsRectItem;
class QGraphicsPixmapItem;

namespace Map2
{
class MapView;

class MapNavigation : public QGraphicsView
{
	Q_OBJECT
public:
	explicit MapNavigation(QWidget *parent = 0);

	void setMapView(Map2::MapView *view);

protected:
	virtual void resizeEvent(QResizeEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
	virtual void mouseDoubleClickEvent(QMouseEvent *event);

private slots:
	void adjustSize();
	void onMapLoaded();
	void onMapScrolled();

private:
	void updatePixmap();
	void dragFrameBy(int dx, int dy);

	double mScaleX;
	double mScaleY;
	bool mIsDragged; //!< Признак того, что пользователь перемещает рамку навигации.
	QPoint mPrevPoint; //!< Предыдущая координата рамки. Для обработки события mouseMove.
	QGraphicsScene *pScene;
	QGraphicsRectItem *pFrame;
	QGraphicsPixmapItem *pPixmapItem;

	QPixmap mPixmap;

	MapView *pMapView;
};
}
#endif // MAPNAVIGATION_H
