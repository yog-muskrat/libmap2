#include "mainwindow.h"

#include <QDebug>
#include <QLayout>
#include <QSettings>
#include <QShortcut>
#include <QPushButton>
#include <QApplication>

#include "map2/mapview.h"
#include "map2/maplayer.h"
#include "map2/rscviewer.h"
#include "map2/mapeditor.h"
#include "map2/layersmodel.h"
#include "map2/groups/mapstackgroup.h"
#include "map2/groups/mapformulargroup.h"
#include "map2/objects/mapobject.h"
#include "map2/objects/mapvectorobject.h"
#include "map2/objects/mapcommlineobject.h"
#include "map2/widgets/layerssettingsdialog.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	QWidget *w = new QWidget;

	QPushButton *pbObj1 = new QPushButton("Аэродром");
	pbObj1->setCheckable(true);
	pbObj1->setChecked(true);

	QPushButton *pbObj2 = new QPushButton("СФ");
	pbObj2->setCheckable(true);
	pbObj2->setChecked(true);

	QPushButton *pbObj3 = new QPushButton("186 ОЦ РЭБ");
	pbObj3->setCheckable(true);
	pbObj3->setChecked(true);

	QPushButton *pbAll = new QPushButton("Все");
	pbAll->setCheckable(true);
	pbAll->setChecked(true);

	QPushButton *btnCalibrate = new QPushButton("Калибровка");
	QPushButton *btnLayers= new QPushButton("Слои");

	QHBoxLayout *btnlay = new QHBoxLayout;
	btnlay->addWidget(pbObj1);
	btnlay->addWidget(pbObj2);
	btnlay->addWidget(pbObj3);
	btnlay->addWidget(pbAll);
	btnlay->addStretch();
	btnlay->addWidget(btnCalibrate);
	btnlay->addWidget(btnLayers);

	pMap = new Map2::MapEditor("./map/sit", "./map/rsc");
	pMap->mapView()->openMap(qApp->applicationDirPath()+"/map/maps/World5m/5mlnWorld.map");

	Map2::MapLayer *layer = pMap->mapView()->createLayer("mgk.rsc", "Layer 1");
	pMap->mapView()->setActiveLayer(layer);

	Map2::MapVectorObject *obj = layer->addVectorObject(10704002, Map2::Coord(69.0571, 33.1), "Североморск 1");
	mObjButtons[pbObj1] = obj;
	mObjButtons[pbObj2] = layer->addVectorObject(10708001, Map2::Coord(69.0571, 33.4), "СФ");
	mObjButtons[pbObj3] = layer->addVectorObject(10711001, Map2::Coord(69.0571, 33.7), "186 ОЦ РЭБ");

	pStackGroup = new Map2::MapStackGroup(obj);
	pStackGroup->addChild(mObjButtons[pbObj2]);
	pStackGroup->addChild(mObjButtons[pbObj3]);

	pFormGroup = new Map2::MapFormularGroup(layer->addVectorObject(10501000, Map2::Coord(69.0571, 35.7), "ПБ \"Сокол\""), Qt::red);
	pFormGroup->addChild( layer->addVectorObject(10208010, Map2::Coord(67.0571, 35.7), "Корабль 1") );
	pFormGroup->addChild( layer->addVectorObject(10211080, Map2::Coord(67.0571, 35.7), "Корабль 2") );
	pFormGroup->addChild( layer->addVectorObject(10102052, Map2::Coord(67.0571, 35.7), "Корабль 3") );
	pFormGroup->addChild( layer->addVectorObject(10102022, Map2::Coord(67.0571, 35.7), "Корабль 4") );
	pFormGroup->addChild( layer->addVectorObject(10601000, Map2::Coord(67.0571, 35.7), "Внезапно!") );

	Map2::MapCommlineObject *commLine1 = new Map2::MapCommlineObject(Map2::Coord(65., 30.), Map2::Coord(69., 40.), layer);
	commLine1->setLineWidth(3);
	Map2::MapCommlineObject *commLine2 = new Map2::MapCommlineObject(Map2::Coord(35., 20.), Map2::Coord(69., 70.), layer);
	commLine2->setArrowStyle( Map2::MapCommlineObject::AS_EndArrow);
	Map2::MapCommlineObject *commLine3 = new Map2::MapCommlineObject(Map2::Coord(0., 10.), Map2::Coord(70., 170.), layer);
	commLine3->setColor( Qt::red );

	QVBoxLayout *mainLay = new QVBoxLayout(w);
	mainLay->addWidget(pMap);
	mainLay->addLayout(btnlay);

	setCentralWidget(w);

	new QShortcut(QKeySequence::Quit, this, SLOT(close()));

	connect(pbObj1, SIGNAL(toggled(bool)), this, SLOT(toggleObj(bool)));
	connect(pbObj2, SIGNAL(toggled(bool)), this, SLOT(toggleObj(bool)));
	connect(pbObj3, SIGNAL(toggled(bool)), this, SLOT(toggleObj(bool)));
	connect(pbAll, SIGNAL(toggled(bool)), this, SLOT(toggleGroup(bool)));
	connect(pMap->mapView(), SIGNAL(scaleChanged(double)), this, SLOT(onScaleChanged()));
	connect(btnCalibrate, SIGNAL(clicked(bool)), pMap->mapView(), SLOT(calibrate()));
	connect(btnLayers, SIGNAL(clicked(bool)), this, SLOT(onEditLayers()));
}

MainWindow::~MainWindow()
{
	delete pStackGroup;
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

void MainWindow::toggleObj(bool visible)
{
	QPushButton *pb = qobject_cast<QPushButton*>(sender());
	Q_ASSERT(pb);

	mObjButtons[pb]->setSelected(visible);

	/*if(visible)
	{
		mObjButtons[pb]->show();
	}
	else
	{
		mObjButtons[pb]->hide();
	}*/
}

void MainWindow::toggleGroup(bool visible)
{
	if(visible)
	{
		pStackGroup->showChildren();
		pFormGroup->showChildren();
	}
	else
	{
		pStackGroup->hideChildren();
		pFormGroup->hideChildren();
	}
}

void MainWindow::onScaleChanged()
{
	pStackGroup->update();
	pFormGroup->update();
}

void MainWindow::onEditLayers()
{
	Map2::LayersSettingsDialog dlg(pMap->mapView()->mapHandle(), this);
	dlg.exec();
}
