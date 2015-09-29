#include "mainwindow.h"
#include "map2/mapview.h"
#include "map2/maplayer.h"
#include "ui_mainwindow.h"
#include "map2/layersmodel.h"
#include "map2/mapvectorobject.h"

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

	MapLayer *l = pView->createLayer("mgk.rsc", "Слой 1");

	MapVectorObject *obj = new MapVectorObject(10403010, l);
	obj->setCoordinates( Coord(60., 30.) );

	QSize size = QDesktopWidget().availableGeometry().size();

	resize( size * 0.85 );

	pScaleLabel = new QLabel( QString("1:%0").arg(pView->scale(), 0, 'f' ) );

	statusBar()->addPermanentWidget( pScaleLabel );
	statusBar()->addPermanentWidget( pCoordLabel = new QLabel());

	connect(pView, SIGNAL(coordChanged(Coord)), this, SLOT(onCoordChanged(Coord)));
	connect(pView, SIGNAL(scaleChanged(double)), this, SLOT(onScaleChanged(double)));
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
	MapLayer *l =pView->createLayer("mgk.rsc", "Новый слой");


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
}
