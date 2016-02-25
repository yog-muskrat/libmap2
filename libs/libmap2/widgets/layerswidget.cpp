#include "widgets/layerswidget.h"

#include "mapview.h"
#include "maplayer.h"
#include "layersmodel.h"
#include "rscselectdialog.h"

#include <QLabel>
#include <QDebug>
#include <QLayout>
#include <QTableView>
#include <QPushButton>
#include <QHeaderView>
#include <QMessageBox>
#include <QInputDialog>

using namespace Map2;

LayersWidget::LayersWidget(QWidget *parent) : QWidget(parent), pMapView(0)
{
	QLabel *title = new QLabel("Слои карты");
	title->setAlignment( Qt::AlignLeft | Qt::AlignVCenter);
	QFont f = title->font();
	f.setBold( true );
	f.setPointSize(11);
	title->setFont( f );

	pTableView = new QTableView(this);
	pTableView->horizontalHeader()->setStretchLastSection(true);
	pTableView->setAlternatingRowColors( true );
	pTableView->setSelectionMode( QTableView::SingleSelection );
	pTableView->setSelectionBehavior( QTableView::SelectRows );
	pTableView->verticalHeader()->hide();

	pbAdd = new QPushButton( QIcon(":map2/plus"), "");
	pbAdd->setToolTip("Добавить слой");

	pbRemove = new QPushButton( QIcon(":map2/minus"), "");
	pbRemove->setToolTip("Удалить слой");
	pbRemove->setEnabled(false);

	pbVisibility = new QPushButton( QIcon(":visible_on"), "");
	pbVisibility->setCheckable(true);
	pbVisibility->setChecked(false);
	pbVisibility->setEnabled(false);
	pbVisibility->setToolTip("Видимость слоя");

	pbLock = new QPushButton( QIcon(":map2/locked"), "");
	pbLock->setCheckable(true);
	pbLock->setChecked(false);
	pbLock->setEnabled(false);
	pbLock->setToolTip("Запрет редактирования");

	QHBoxLayout *btnLay = new QHBoxLayout();
	btnLay->addWidget( title );
	btnLay->addStretch();
	btnLay->addWidget(pbAdd);
	btnLay->addWidget(pbRemove);
	btnLay->addWidget(pbVisibility);
	btnLay->addWidget(pbLock);
	btnLay->setSpacing(1);
	btnLay->setContentsMargins( QMargins() );

	QVBoxLayout *mainLay = new QVBoxLayout(this);
	mainLay->addLayout( btnLay );
	mainLay->addWidget( pTableView );
	mainLay->setSpacing(1);
	mainLay->setContentsMargins( QMargins() );

	connect(pTableView, SIGNAL(clicked(QModelIndex)), this, SLOT(onLayerClicked(QModelIndex)));
	connect(pTableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onLayerDoubleClicked(QModelIndex)));
	connect(pbAdd, SIGNAL(clicked(bool)), this, SLOT(onAdd()));
	connect(pbRemove, SIGNAL(clicked(bool)), this, SLOT(onRemove()));
	connect(pbLock, SIGNAL(toggled(bool)), this, SLOT(onToggleLock(bool)));
	connect(pbVisibility, SIGNAL(toggled(bool)), this, SLOT(onToggleVisibility(bool)));
}

LayersWidget::~LayersWidget()
{

}

void LayersWidget::setMapView(Map2::MapView *view)
{
	if(pMapView == view)
	{
		return;
	}

	pMapView = view;

	Q_ASSERT(pTableView);

	pTableView->setModel( pMapView->layersModel() );
	pTableView->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
}

void LayersWidget::onLayerClicked(const QModelIndex &index)
{
	MapLayer *l = pMapView->layersModel()->layerAt( index.row() );
	pMapView->setActiveLayer(l);

	pbRemove->setEnabled(true);
	pbVisibility->setEnabled( true );
	pbLock->setEnabled( true );

	pbVisibility->setChecked( ! l->isVisible() );
	pbLock->setChecked( l->isLocked() );


	emit layerSelected(l);
}

void LayersWidget::onLayerDoubleClicked(const QModelIndex &index)
{
	MapLayer *l = pMapView->layersModel()->layerAt( index.row() );

	if( index.column() == LayersModel::COL_Visible )
	{
		l->setVisible( !l->isVisible() );
	}
	else if( index.column() == LayersModel::COL_Locked )
	{
		l->setLocked( !l->isLocked() );
	}
}

void LayersWidget::onAdd()
{
	bool ok = false;
	QString name = QInputDialog::getText(this, "Новый слой", "Введите название нового слоя", QLineEdit::Normal, "Новый слой", &ok);

	if(!ok || name.isEmpty())
	{
		return;
	}

	RscSelectDialog dlg(this);
	if(!dlg.exec() || dlg.selectedRsc().isEmpty())
	{
		return;
	}

	MapLayer *l = pMapView->createLayer(dlg.selectedRsc(), "", name);
	int row = pMapView->layersModel()->layerIndex(l);

	Q_ASSERT(l);

	pTableView->selectRow(row);
	onLayerClicked(pTableView->currentIndex());
}

void LayersWidget::onRemove()
{
	QModelIndex idx = pTableView->currentIndex();
	if(! idx.isValid())
	{
		return;
	}

	MapLayer *l = pMapView->layersModel()->layerAt(idx.row());

	int btn = QMessageBox::question(this, "Удаление слоя",
									QString("Слой %0 и все его объекты будут удалены. Продолжить?").arg(l->layerName()),
									QMessageBox::Yes, QMessageBox::No);

	if(btn == QMessageBox::No)
	{
		return;
	}

	pMapView->layersModel()->removeLayer( idx.row() );

	pbRemove->setEnabled(false);
	pbVisibility->setEnabled(false);
	pbLock->setEnabled(false);
}

void LayersWidget::onToggleVisibility(const bool &visible)
{
	QModelIndex idx = pTableView->currentIndex();
	if(! idx.isValid())
	{
		return;
	}

	MapLayer *l = pMapView->layersModel()->layerAt( idx.row() );
	l->setVisible( !visible );

	pbVisibility->setIcon( QIcon( (visible ? ":visible_off" : ":visible_on") ) );
}

void LayersWidget::onToggleLock(const bool &locked)
{
	QModelIndex idx = pTableView->currentIndex();
	if(! idx.isValid())
	{
		return;
	}

	MapLayer *l = pMapView->layersModel()->layerAt( idx.row() );
	l->setLocked(locked);

	pbLock->setIcon( QIcon( (locked ? ":map2/locked" : ":map2/unlocked" ) ) );
}
