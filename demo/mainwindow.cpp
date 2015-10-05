#include "mainwindow.h"
#include "map2/mapview.h"
#include "map2/maplayer.h"
#include "ui_mainwindow.h"
#include "map2/layersmodel.h"
#include "map2/mapvectorobject.h"
#include "map2/rscviewer.h"

#include <QDesktopWidget>
#include <QDockWidget>
#include <QTableView>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow), pView(0)
{
	ui->setupUi(this);

	pView = new MapView("./sit", "../maps/rsc", this);
	setCentralWidget(pView);
	pView->openMap( QApplication::applicationDirPath()+"/../maps/World5m/5mlnWorld.map");

	ui->layersTable->setModel( pView->layersModel() );
	ui->layersTable->setColumnWidth( LayersModel::COL_Visible, 32);

	ui->navigationDockLayout->insertWidget(0, pView->detachNavigation());

	addToolBar( pView->toolBar() );

	MapLayer *l = pView->createLayer("mgk.rsc", "Слой 1");

	MapVectorObject *obj1 = l->addVectorObject(10403010, Coord(60., 30.) );
	obj1->setName("Самолетик");

	statusBar()->addPermanentWidget( pScaleLabel = new QLabel( QString("1:%0").arg(pView->scale(), 0, 'f' )));
	statusBar()->addPermanentWidget( pCoordLabel = new QLabel());

	connect(pView, SIGNAL(coordChanged(Coord)), this, SLOT(onCoordChanged(Coord)));
	connect(pView, SIGNAL(scaleChanged(double)), this, SLOT(onScaleChanged(double)));

	QSize size = QDesktopWidget().availableGeometry().size();
	resize( size * 0.85 );
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::onScaleChanged(double scale)
{
	pScaleLabel->setText( QString("1:%0").arg(scale, 0, 'f'));
}

void MainWindow::onCoordChanged(Coord coord)
{
	pCoordLabel->setText(coord.toString());
}

void MainWindow::on_pbAddLayer_clicked()
{
	pView->createLayer("", "Новый слой");
}

void MainWindow::on_pbRemoveLayer_clicked()
{
	QModelIndex idx = ui->layersTable->currentIndex();
	if(!idx.isValid())
	{
		return;
	}

	pView->layersModel()->removeLayer( idx.row() );
}

void MainWindow::on_layersTable_clicked(const QModelIndex &index)
{
	MapLayer *l = pView->layersModel()->layerAt(index.row() );
	if(!l)
	{
		return;
	}

	ui->objectsTable->setModel(l);
	ui->lblLayerName->setText( l->layerName() );
	ui->lblRscName->setText( l->rscName() );
}

void MainWindow::on_pbAddObject_clicked()
{
	QModelIndex idx = ui->layersTable->currentIndex();
	if(!idx.isValid())
	{
		return;
	}

	MapLayer *l = pView->layersModel()->layerAt(idx.row() );
	if(!l)
	{
		return;
	}

	long code = RscViewer::selectExCode( l->rscName() );

	if(code <= 0)
	{
		return;
	}

	MapVectorObject *obj = new MapVectorObject(code, l);
	obj->setCoordinates( Coord(0, 0) );
	obj->center();

	obj->setRotation(45);
}

void MainWindow::on_pbRemoveObject_clicked()
{
	QModelIndex objectIdx = ui->objectsTable->currentIndex();
	if(!objectIdx.isValid())
	{
		return;
	}

	ui->objectsTable->model()->removeRow( objectIdx.row());
}

void MainWindow::on_objectsTable_doubleClicked(const QModelIndex &index)
{
	QModelIndex idx = ui->layersTable->currentIndex();
	if(!idx.isValid())
	{
		return;
	}

	MapLayer *l = pView->layersModel()->layerAt(idx.row() );
	if(!l)
	{
		return;
	}

	MapObject *o =l->objectAtIndex( index );

	if(!o)
	{
		return;
	}

	o->center();
}
