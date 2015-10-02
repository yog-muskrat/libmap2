#ifndef MAPNAVIGATION_H
#define MAPNAVIGATION_H

#include <QGraphicsView>

#include "structs.h"

class QGraphicsScene;
class QGraphicsRectItem;
class QGraphicsPixmapItem;

class MapNavigation : public QGraphicsView
{
	Q_OBJECT
public:
	explicit MapNavigation(QWidget *parent = 0);
	void setPixmap(const QPixmap &pm);

	void updatePixmap();
public slots:
	void setSizes(QSize mapSize, QSize viewportSize);
	void moveFrame(QPoint originalTopLeft);

signals:
	void navigationMoved(QPoint newPos);

protected:
	virtual void resizeEvent(QResizeEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
	virtual void mouseDoubleClickEvent(QMouseEvent *event);

private:
	void dragFrameBy(int dx, int dy);
	void notifyFrameGlobalPos();

	double mScaleX;
	double mScaleY;
	bool mIsDragged; //!< Признак того, что пользователь перемещает рамку навигации.
	QPoint mPrevPoint; //!< Предыдущая координата рамки. Для обработки события mouseMove.
	QGraphicsScene *pScene;
	QGraphicsRectItem *pFrame;
	QGraphicsPixmapItem *pPixmap;

	QPixmap mPixmap;
	QSize mMapSize;
	QSize mViewportSize;
};
#endif // MAPNAVIGATION_H
