#ifndef MAPINFOWIDGET
#define MAPINFOWIDGET

#include <QWidget>

#include "mapstructs.h"

class QLabel;

namespace Map2
{
class MapView;
class MapNavigation;

class MapInfoWidget : public QWidget
{
	Q_OBJECT
public:
	explicit MapInfoWidget(QWidget *parent = 0);
	~MapInfoWidget();

	void setMapView(Map2::MapView *view);

private slots:
	void onScaleChanged(double scale);
	void onCoordChanged(Map2::Coord coord);

private:
	QLabel *pScaleLabel;
	QLabel *pCoordLabel;
	MapView *pMapView;
	MapNavigation *pMapNavigation;
};
}

#endif // MAPINFOWIDGET
