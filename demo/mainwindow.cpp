#include "mainwindow.h"

#include <QDebug>
#include <QTimer>
#include <QLayout>
#include <QSettings>
#include <QShortcut>
#include <QPushButton>
#include <QApplication>

#include "map2/mapview.h"
#include "map2/maplayer.h"
#include "map2/rscviewer.h"
#include "map2/mapeditor.h"
#include "map2/maphelper.h"
#include "map2/layersmodel.h"

#include "map2/groups/mapstackgroup.h"
#include "map2/groups/mapformulargroup.h"

#include "map2/objects/mapobject.h"
#include "map2/objects/maplineobject.h"
#include "map2/objects/mapvectorobject.h"
#include "map2/objects/mapsectorobject.h"
#include "map2/objects/mapcommlineobject.h"

#include "map2/widgets/layerssettingsdialog.h"

using namespace Map2;

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	QWidget *w = new QWidget;

	QPushButton *btnCalibrate = new QPushButton("Калибровка");
	QPushButton *btnLayers= new QPushButton("Слои");

	QHBoxLayout *btnlay = new QHBoxLayout;
	btnlay->addStretch();
	btnlay->addWidget(btnCalibrate);
	btnlay->addWidget(btnLayers);

	pMap = new Map2::MapEditor("./map/sit", "./map/rsc");
	pMap->mapView()->openMap(qApp->applicationDirPath()+"/map/maps/World5m/5mlnWorld.map");

	QVBoxLayout *mainLay = new QVBoxLayout(w);
	mainLay->addWidget(pMap);
	mainLay->addLayout(btnlay);

	setCentralWidget(w);

	Map2::MapLayer *layer = pMap->mapView()->createLayer("mgk.rsc", "misc", "Слой 1");
	pMap->mapView()->setActiveLayer(layer);

	pObj = layer->addVectorObject("гр вмс", Coord(60., 30.), "Группа" );

	MapVectorObject *mvo = dynamic_cast<MapVectorObject*>(pObj);
	MapFormularGroup *group = new MapFormularGroup(mvo, Qt::red);

	group->addChild( layer->addVectorObject("оок вмс", Coord(55., 30.), "Корабль 1") );
	group->addChild( layer->addVectorObject("оок вмс", Coord(50., 30.), "Корабль 2") );
	group->addChild( layer->addVectorObject("оок вмс", Coord(45., 30.), "Корабль 3") );

	group->setChildrenVisible(false);

	Map2::MapCommlineObject *comm = new Map2::MapCommlineObject(Map2::Coord(30., 30.), Map2::Coord(45., 90.), layer);

	comm->addAssignment(Map2::MapCommlineObject::Assignment("Средство 1", "Некая часть РЭБ"));
	comm->addAssignment(Map2::MapCommlineObject::Assignment("Средство 2", "Другая часть РЭБ"));
	comm->addAssignment(Map2::MapCommlineObject::Assignment("Средство 3", "Еще одна часть РЭБ"));

	new QShortcut(QKeySequence::Quit, this, SLOT(close()));

	connect(pMap->mapView(), SIGNAL(scaleChanged(double)), this, SLOT(onScaleChanged()));
	connect(btnCalibrate, SIGNAL(clicked(bool)), pMap->mapView(), SLOT(calibrate()));
	connect(btnLayers, SIGNAL(clicked(bool)), this, SLOT(onEditLayers()));
	connect(pMap->mapView(), SIGNAL(mouseLeftClick(QPoint)), this, SLOT(onLeftClick(QPoint)));
	connect(pMap->mapView(), SIGNAL(mouseRightClick(QPoint)), this, SLOT(onRightClick(QPoint)));
}

MainWindow::~MainWindow()
{

}

void MainWindow::showEvent(QShowEvent *e)
{
	QSettings set("NIIPA", "map2test");
	restoreGeometry( set.value("geometry").toByteArray() );

	double scale = pMap->mapView()->scale();

	pMap->mapView()->setScale( set.value("scale", scale).toDouble());

	double lat = set.value("lat").toDouble();
	double lng = set.value("lng").toDouble();

	if(lat != 0 || lng != 0)
	{
		Map2::Coord coord(lat, lng);
		pMap->mapView()->setCenter(coord);
	}

	QMainWindow::showEvent(e);
}

void MainWindow::closeEvent(QCloseEvent *e)
{
	QSettings set("NIIPA", "map2test");
	set.setValue("geometry", this->saveGeometry());
	set.setValue("scale", pMap->mapView()->scale());

	Map2::Coord coord = pMap->mapView()->screenCenterCoordinate();

	set.setValue("lat", coord.lat);
	set.setValue("lng", coord.lng);

	QMainWindow::closeEvent(e);
}

void MainWindow::onScaleChanged()
{

}

void MainWindow::onEditLayers()
{
	Map2::LayersSettingsDialog dlg(pMap->mapView()->mapHandle(), this);
	dlg.exec();
}

void MainWindow::onLeftClick(QPoint point)
{
	QList<Map2::MapObject*> objs = pMap->mapView()->objectsAtPoint(point);

	if(objs.isEmpty())
	{
		return;
	}

	foreach(MapGroup *grp, objs.first()->childGroups())
	{
		if(grp->type() != MapGroup::MG_Formular)
		{
			continue;
		}

		grp->setChildrenVisible( !grp->childrenVisible() );
	}
}

void MainWindow::onRightClick(QPoint point)
{
	Map2::MapLayer *layer = pMap->mapView()->activeLayer();
	if(!layer)
	{
		return;
	}

	Map2::Coord coord = pMap->mapView()->coordinateAtPoint(point);

	QString key = Map2::RscViewer::selectVectorKey(layer->rscName());
	if(key.isEmpty())
	{
		return;
	}

	layer->addVectorObject(key, coord, "loh1");
}
