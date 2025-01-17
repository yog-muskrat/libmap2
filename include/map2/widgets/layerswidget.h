#ifndef LAYERSWIDGET
#define LAYERSWIDGET

#include <QWidget>

class QTableView;
class QPushButton;
class QModelIndex;

namespace Map2
{

class MapView;
class MapLayer;

class LayersWidget : public QWidget
{
	Q_OBJECT
public:
	explicit LayersWidget(QWidget *parent = 0);
	~LayersWidget();

	void setMapView(Map2::MapView *view);

signals:
	void layerSelected(Map2::MapLayer *layer);

private slots:
	void onActiveLayerChanged(Map2::MapLayer *layer);
	void onLayerClicked(const QModelIndex &index);
	void onLayerDoubleClicked(const QModelIndex &index);
	void onAdd();
	void onRemove();
	void onMoveUp();
	void onMoveDown();
	void onToggleVisibility(bool visible);
	void onToggleLock(bool locked);

private:
	MapView *pMapView;
	QTableView *pTableView;
	QPushButton *pbUp;
	QPushButton *pbDown;
	QPushButton *pbAdd;
	QPushButton *pbRemove;
	QPushButton *pbVisibility;
	QPushButton *pbLock;
};
}

#endif // LAYERSWIDGET

