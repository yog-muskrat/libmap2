#ifndef MAPEDITOR
#define MAPEDITOR

#include <QWidget>

#include "mapstructs.h"

class QToolBar;
class QModelIndex;

namespace Map2
{

class MapView;
class MapLayer;
class MapObject;
class LayersWidget;
class MapInfoWidget;
class ObjectsWidget;

/*!
 * \brief Класс редактора карты.
 * Помимо окна для отображения самой карты включает в себя таблицы слоев и объектов, панель инструментов
 * и виджет навигации.
 */
class MapEditor : public QWidget
{
	Q_OBJECT
public:
	MapEditor(QString sitDir, QString rscDir, QWidget *parent = 0);
	~MapEditor();

	Map2::MapView* mapView(){return pMapView;}

signals:
	void objectEditRequested(Map2::MapObject *obj);
	void objectAddRequested(Map2::Coord coord);

private:
	MapView *pMapView;
	QToolBar *pToolBar;
	LayersWidget *pLayersTable;
	ObjectsWidget *pObjectsTable;
	MapInfoWidget *pMapInfo;
};
}

#endif // MAPEDITOR
