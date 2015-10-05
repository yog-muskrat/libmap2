#include "maptoolbar.h"

#include <QAction>
#include <QDebug>

MapToolBar::MapToolBar(QWidget *parent) :
	QToolBar(parent)
{
	pGroup = new QActionGroup(this);
	pGroup->setExclusive(true);

	addActionWithData(new QAction("Нет", this), MapView::None)->setChecked(true);
	addActionWithData(new QAction("Переместить", this), MapView::MoveObject);
	addActionWithData(new QAction("Удалить", this), MapView::DeleteObject);
	addActionWithData(new QAction("Добавить вектор", this), MapView::AddVectorObject);
	addActionWithData(new QAction("Добавить линию", this), MapView::AddLineObject);
	addActionWithData(new QAction("Добавить зону", this), MapView::AddZoneObject);
	addActionWithData(new QAction("Линейка", this), MapView::Ruler);
	addActionWithData(new QAction("Приблизить", this), MapView::RectZoom);

	connect(this, SIGNAL(actionTriggered(QAction*)), SLOT(onActionTriggered(QAction*)));
}

void MapToolBar::onActionTriggered(QAction *act)
{
	if(act->isChecked())
	{
		MapView::Tools tool = static_cast<MapView::Tools>( act->data().toInt() );
		emit toolSelected(tool);
	}
}

QAction *MapToolBar::addActionWithData(QAction *act, QVariant data)
{
	act->setData(data);
	act->setCheckable(true);
	addAction(act);
	pGroup->addAction(act);

	return act;
}
