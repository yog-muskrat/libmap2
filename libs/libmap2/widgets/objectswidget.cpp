#include "widgets/objectswidget.h"
#include "mapview.h"
#include "maplayer.h"
#include "objects/mapobject.h"

#include <QDebug>
#include <QLabel>
#include <QLayout>
#include <QTableView>
#include <QHeaderView>
#include <QPushButton>
#include <QMessageBox>

using namespace Map2;

ObjectsWidget::ObjectsWidget(QWidget *parent) : QWidget(parent)
{
	pProxyModel = new HiddenTextProxyModel(this);
	pProxyModel->setColumnTextHidden(MapLayer::COL_Type);

	pTableView = new QTableView();
	pTableView->verticalHeader()->hide();
	pTableView->horizontalHeader()->setStretchLastSection(true);
	pTableView->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
	pTableView->setSelectionBehavior( QTableView::SelectRows );
	pTableView->setModel( pProxyModel );

	pbAdd = new QPushButton(QIcon(":plus"), "");
	pbRemove = new QPushButton(QIcon(":minus"), "");
	pbRemove->setEnabled(false);
	pbEdit = new QPushButton(QIcon(":edit"), "");
	pbEdit->setEnabled(false);

	pTitle = new QLabel("Объекты слоя");
	pTitle->setAlignment(Qt::AlignLeft);
	pTitle->setWordWrap(true);
	pTitle->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Preferred);
	QFont f = pTitle->font();
	f.setBold(true);
	f.setPointSize(11);
	pTitle->setFont(f);

	QHBoxLayout *btnLay = new QHBoxLayout();
	btnLay->addWidget(pTitle);
	btnLay->addWidget(pbAdd);
	btnLay->addWidget(pbRemove);
	btnLay->addWidget(pbEdit);
	btnLay->setContentsMargins( QMargins() );
	btnLay->setSpacing(1);

	QVBoxLayout *mainLay = new QVBoxLayout(this);
	mainLay->addLayout(btnLay);
	mainLay->addWidget(pTableView);
	mainLay->setContentsMargins(QMargins());
	mainLay->setSpacing(1);

	connect(pbAdd, SIGNAL(clicked(bool)), this, SLOT(onAdd()));
	connect(pbRemove, SIGNAL(clicked(bool)),this, SLOT(onRemove()));
	connect(pbEdit, SIGNAL(clicked(bool)),this, SLOT(onEdit()));
	connect(pTableView, SIGNAL(clicked(QModelIndex)), this, SLOT(onObjectClicked(QModelIndex)));
	connect(pTableView, SIGNAL(doubleClicked(QModelIndex)),this, SLOT(onObjectDoubleClicked(QModelIndex)));
}

ObjectsWidget::~ObjectsWidget()
{

}

void ObjectsWidget::setMapLayer(Map2::MapLayer *layer)
{
	if(pLayerModel == layer)
	{
		return;
	}

	pLayerModel = layer;
	pProxyModel->setSourceModel( pLayerModel );
	pTableView->hideColumn( MapLayer::COL_Coord);
	pbRemove->setEnabled(false);
	pbEdit->setEnabled(false);

	pTitle->setText( "Объекты слоя "+layer->layerName() );
}

void ObjectsWidget::onAdd()
{
	Coord coord = pLayerModel->mapView()->screenCenterCoordinate();
	emit objectAddRequest(coord);
}

void ObjectsWidget::onRemove()
{
	QModelIndex idx = pTableView->currentIndex();
	if(!idx.isValid())
	{
		return;
	}

	MapObject *obj = pLayerModel->objectAtIndex( idx );
	Q_ASSERT(obj);

	int btn = QMessageBox::question(this,
									"Удаление объекта",
									QString("Объект %0 будет удален. Продолжить?").arg(obj->name()),
									QMessageBox::Yes,
									QMessageBox::No);

	if(btn == QMessageBox::No)
	{
		return;
	}

	obj->remove();
}

void ObjectsWidget::onEdit()
{
	QModelIndex idx = pTableView->currentIndex();
	if(!idx.isValid())
	{
		return;
	}

	MapObject *obj = pLayerModel->objectAtIndex( idx );
	Q_ASSERT(obj);

	emit objectEditRequest(obj);
}

void ObjectsWidget::onObjectClicked(const QModelIndex &index)
{
	Q_UNUSED(index);

	pbRemove->setEnabled(true);
	pbEdit->setEnabled(true);
}

void ObjectsWidget::onObjectDoubleClicked(const QModelIndex &index)
{
	if(!pLayerModel)
	{
		return;
	}

	MapObject *obj = pLayerModel->objectAtIndex( pProxyModel->mapToSource( index) );
	Q_ASSERT(obj);

	obj->center();
	onEdit();
}


void HiddenTextProxyModel::setColumnTextHidden(int col, bool hidden)
{
	if(hidden)
	{
		mHiddenTextCols << col;
	}
	else
	{
		mHiddenTextCols.remove(col);
	}
}

void HiddenTextProxyModel::showAllText()
{
	mHiddenTextCols.clear();
}

QVariant HiddenTextProxyModel::data(const QModelIndex &proxyIndex, int role) const
{
	if(role == Qt::DisplayRole && mHiddenTextCols.contains(proxyIndex.column()))
	{
		return QVariant();
	}

	return sourceModel()->data( mapToSource(proxyIndex), role);
}
