#include "maplayer.h"
#include "mapview.h"

#include "gis/maptype.h"
#include "gis/rscapi.h"

#include <QFile>
#include <QDebug>
#include <QApplication>

MapLayer::MapLayer(quint16 id, QString rscName, MapView *parent) : QAbstractItemModel(parent),
	pMapView(parent), mSiteHandle(-1), mRscName(rscName), mLastInternalId(0), mVisible(true), mValid(false)
{
	MAPREGISTER mapreg;
	LISTREGISTER listreg;

	mapGetMapInfo(pMapView->mapHandle(), 1, &mapreg, &listreg);

	CREATESITE cs;
	cs.Length = sizeof( CREATESITE );

	cs.MaterialProjection = mapreg.MaterialProjection;
	cs.MapType = mapreg.MapType;
	cs.Scale = mapreg.Scale;
	strncpy(cs.MapName, mapreg.Name, 32);
	cs.AxisMeridian = mapreg.AxisMeridian;
	cs.FirstMainParallel = mapreg.FirstMainParallel;
	cs.SecondMainParallel = mapreg.SecondMainParallel;
	cs.MainPointParallel = mapreg.MainPointParallel;

	QString sitname = QString("%0/layer_%1.sit").arg(pMapView->sitDir()).arg(id);
	QString rscname = QString("%0/%1").arg(pMapView->rscDir(), rscName);
	if(!QFile::exists(rscname))
	{
		qDebug()<<"Ошибка классификатора";
		return;
	}

	mSiteHandle = mapCreateAndAppendSite(pMapView->mapHandle(), qPrintable(sitname), qPrintable(rscname), &cs);

	mValid = mSiteHandle > 0;
}

MapLayer::~MapLayer()
{
	if(mSiteHandle > 1 && pMapView->mapHandle() > 0)
	{
		qDeleteAll(mObjects);
		mapCloseData(mSiteHandle);
	}
}

HMAP MapLayer::mapHandle() const
{
	if(!pMapView)
	{
		return 0;
	}

	return pMapView->mapHandle();
}

bool MapLayer::isValid()
{
	return mValid;
}

void MapLayer::setVisible(bool visible)
{
	if(visible != mVisible)
	{
		mVisible = visible;
		mapSetSiteViewFlag(mapHandle(), siteHandle(), (mVisible ? 1 : 0) );
		emit toggled(mVisible);
	}
}

void MapLayer::setLayerName(const QString &value)
{
	if(value != mLayerName)
	{
		mLayerName = value;
		emit layerNameChanged(mLayerName);
	}
}

QString MapLayer::rscName() const
{
	Q_ASSERT(pMapView);

	HRSC rsc = mapGetRscIdent(pMapView->mapHandle(), mSiteHandle);

	if(rsc <= 0)
	{
		return 0;
	}

	return QString::fromLocal8Bit( mapGetRscName(rsc) );
}

void MapLayer::addObject(MapObject *object, MapObject *parent)
{

}

void MapLayer::removeObject(MapObject *object)
{

}

QModelIndex MapLayer::index(int row, int column, const QModelIndex &parent) const
{
	return QModelIndex();
}

QModelIndex MapLayer::parent(const QModelIndex &child) const
{
	return QModelIndex();
}

int MapLayer::rowCount(const QModelIndex &parent) const
{
	return 0;
}

int MapLayer::columnCount(const QModelIndex &parent) const
{
	return COL_Count;
}

QVariant MapLayer::data(const QModelIndex &index, int role) const
{
	return QVariant();
}

QVariant MapLayer::headerData(int section, Qt::Orientation orientation, int role) const
{
	if(orientation != Qt::Horizontal)
	{
		return QAbstractItemModel::headerData(section, orientation, role);
	}

	if(role == Qt::DisplayRole)
	{
		if(section == COL_Name)
		{
			return "Название";
		}
		else if(section == COL_Coord)
		{
			return "Координаты";
		}
		else if(section == COL_Type)
		{
			return "Тип";
		}
	}

	return QVariant();
}
