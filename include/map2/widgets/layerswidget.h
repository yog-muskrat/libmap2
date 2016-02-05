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
	void onLayerClicked(const QModelIndex &index);
	void onLayerDoubleClicked(const QModelIndex &index);
	void onAdd();
	void onRemove();
	void onToggleVisibility(const bool &visible);
	void onToggleLock(const bool &locked);

private:
	MapView *pMapView;
	QTableView *pTableView;
	QPushButton *pbAdd;
	QPushButton *pbRemove;
	QPushButton *pbVisibility;
	QPushButton *pbLock;
};
}

#endif // LAYERSWIDGET

