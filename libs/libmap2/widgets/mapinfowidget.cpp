#include "widgets/mapinfowidget.h"
#include "widgets/mapnavigation.h"
#include "mapview.h"

#include <QLabel>
#include <QLayout>

using namespace Map2;

MapInfoWidget::MapInfoWidget(QWidget *parent) : QWidget(parent), pMapView(0)
{
	pMapNavigation = new MapNavigation(0);

	pScaleLabel = new QLabel("...");
	pScaleLabel->setAlignment(Qt::AlignLeft);
	QFont f = pScaleLabel->font();
	f.setBold(false);
	f.setPointSize(9);
	pScaleLabel->setFont(f);

	pCoordLabel = new QLabel("...");
	pCoordLabel->setAlignment( Qt::AlignLeft);
	pCoordLabel->setFont(f);

	QVBoxLayout *mainLay = new QVBoxLayout(this);
	mainLay->setContentsMargins( QMargins() );
	mainLay->setSpacing(1);

	mainLay->addWidget(pMapNavigation);

	QHBoxLayout *lblLay = new QHBoxLayout();
	lblLay->setContentsMargins( QMargins() );
	lblLay->addWidget(pCoordLabel);
	lblLay->addWidget(pScaleLabel);

	mainLay->addLayout(lblLay);
}

MapInfoWidget::~MapInfoWidget()
{

}

void MapInfoWidget::setMapView(MapView *view)
{
	if(view == pMapView)
	{
		return;
	}

	if(pMapView)
	{
		disconnect(pMapView, SIGNAL(coordChanged(Map2::Coord)), this, SLOT(onCoordChanged(Map2::Coord)));
		disconnect(pMapView, SIGNAL(scaleChanged(double)), this, SLOT(onScaleChanged(double)));
	}

	pMapView = view;

	pMapNavigation->setMapView( pMapView );

	connect(pMapView, SIGNAL(coordChanged(Map2::Coord)), this, SLOT(onCoordChanged(Map2::Coord)));
	connect(pMapView, SIGNAL(scaleChanged(double)), this, SLOT(onScaleChanged(double)));
}

void MapInfoWidget::onScaleChanged(double scale)
{
	pScaleLabel->setText( QString("1:%0").arg(scale, 4, 'f', 0) );
}

void MapInfoWidget::onCoordChanged(Coord coord)
{
	pCoordLabel->setText(QString("Ш:%0 Д:%1").arg(coord.lat, 4, 'f', 4).arg(coord.lng, 4, 'f', 4));
}
