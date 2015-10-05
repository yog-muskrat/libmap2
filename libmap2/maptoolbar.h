#ifndef MAPTOOLBAR_H
#define MAPTOOLBAR_H

#include <QToolBar>

#include "mapview.h"

class QActionGroup;

class MapToolBar : public QToolBar
{
	Q_OBJECT
public:
	explicit MapToolBar(QWidget *parent = 0);

signals:
	void toolSelected(MapView::Tools tool);

private slots:
	void onActionTriggered(QAction *act);

private:
	QAction* addActionWithData( QAction *act, QVariant data);

	QActionGroup *pGroup;
};

#endif // MAPTOOLBAR_H
