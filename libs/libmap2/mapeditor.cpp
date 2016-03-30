#include "mapeditor.h"

#include "mapview.h"
#include "maplayer.h"
#include "objects/mapobject.h"
#include "layersmodel.h"

#include "widgets/layerswidget.h"
#include "widgets/objectswidget.h"
#include "widgets/mapinfowidget.h"

#include <QAction>
#include <QLayout>
#include <QToolBar>

using namespace Map2;

MapEditor::MapEditor(QString sitDir, QString rscDir, QWidget *parent) : QWidget(parent)
{
	pMapView = new MapView(sitDir, rscDir);

	pToolBar = pMapView->toolBar();
	pToolBar->setOrientation(Qt::Vertical);

	pMapInfo = new MapInfoWidget(this);
	pMapInfo->setMapView(pMapView);

	pLayersTable = new LayersWidget(this);
	pObjectsTable = new ObjectsWidget(this);

	QWidget *panelsWidget = new QWidget();

	QVBoxLayout *tablesLay = new QVBoxLayout(panelsWidget);
	tablesLay->addWidget(pMapInfo);
	tablesLay->addWidget(pLayersTable);
	tablesLay->addWidget(pObjectsTable);
	tablesLay->setSpacing(10);
	tablesLay->setContentsMargins( QMargins() );

	pToolBar->addAction(QIcon(":map2/zoom-in"), "Приблизить", pMapView, SLOT(zoomIn()));
	pToolBar->addAction(QIcon(":map2/zoom-out"), "Удалить", pMapView, SLOT(zoomOut()));

	pToolBar->addSeparator();
	QAction *act = pToolBar->addAction(QIcon(":map2/layers"), "Показать слои");
	act->setCheckable(true);
	act->setChecked(true);
	connect(act, SIGNAL(toggled(bool)), panelsWidget, SLOT(setVisible(bool)));


	QHBoxLayout *mainLay = new QHBoxLayout(this);
	mainLay->addWidget(pToolBar);
	mainLay->addWidget(pMapView, 4);
	mainLay->addWidget(panelsWidget, 1);
	mainLay->setSpacing(1);
	mainLay->setContentsMargins( QMargins() );

	pLayersTable->setMapView( pMapView );

	connect(pLayersTable, SIGNAL(layerSelected(Map2::MapLayer*)), pObjectsTable, SLOT(setMapLayer(Map2::MapLayer*)));
	connect(pObjectsTable, SIGNAL(objectEditRequest(Map2::MapObject*)), this, SIGNAL(objectEditRequested(Map2::MapObject*)));
	connect(pObjectsTable, SIGNAL(objectAddRequest(Map2::Coord)), this, SIGNAL(objectAddRequested(Map2::Coord)));
}

MapEditor::~MapEditor()
{

}
