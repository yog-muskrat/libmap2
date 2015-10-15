#include "maplayer.h"
#include "mapview.h"
#include "mapobject.h"
#include "mapvectorobject.h"
#include "maplineobject.h"
#include "mapzoneobject.h"

#include <QDir>
#include <QFile>
#include <QDebug>
#include <QTextCodec>
#include <QApplication>

MapLayer::MapLayer(quint16 id, QString rscName, MapView *parent, bool temp) : QAbstractItemModel(parent),
	pMapView(parent), mSiteHandle(-1), mRscName(rscName), mLastInternalId(0), mVisible(true), mValid(false)
{
	MAPREGISTER mapreg;
	LISTREGISTER listreg;

	mapGetMapInfo(pMapView->mapHandle(), 1, &mapreg, &listreg);

	CREATESITE cs;
	memset((void*)&cs,0,sizeof(cs));
	cs.Length = sizeof( CREATESITE );

	cs.MaterialProjection = mapreg.MaterialProjection;
	cs.MapType = mapreg.MapType;
	cs.Scale = mapreg.Scale;
	strncpy(cs.MapName, mapreg.Name, 32);
	cs.AxisMeridian = mapreg.AxisMeridian;
	cs.FirstMainParallel = mapreg.FirstMainParallel;
	cs.SecondMainParallel = mapreg.SecondMainParallel;
	cs.MainPointParallel = mapreg.MainPointParallel;

	mFileName = QString("layer_%0").arg(id);
	QString sitname = QString("%0/%1.sit").arg(pMapView->sitDir()).arg(mFileName);
	QString rscname = QString("%0/%1").arg(pMapView->rscDir(), rscName);
	if(!QFile::exists(rscname))
	{
		qDebug()<<"Ошибка классификатора";
		return;
	}

	if(temp)
	{
		mSiteHandle = mapCreateAndAppendTempSite(pMapView->mapHandle(), qPrintable(rscname));
	}
	else
	{
		mSiteHandle = mapCreateAndAppendSite(pMapView->mapHandle(), qPrintable(sitname), qPrintable(rscname), &cs);
	}

	//! Нижеследующий блок - костыль против странного глюка с дублированием первого объекта в сите.
	//! Возможно его можно будет убрать после обновления библиотек.
	HOBJ hobj = mapCreateSiteObject(pMapView->mapHandle(), siteHandle());
	mapAppendPointPlane(hobj, 0, 0);
	mapCommitObject(hobj);
	mapDeleteObject(hobj);
	mapCommitObject(hobj);
	mapFreeObject(hobj);

	mValid = mSiteHandle > 0;
}

QVariant MapLayer::displayRole(const QModelIndex &idx) const
{
	MapObject *obj = mObjects.at(idx.row());

	if(!obj)
	{
		return QVariant();
	}

	if(idx.column() == COL_Name)
	{
		return obj->name();
	}
	else if(idx.column() == COL_Coord)
	{
		return obj->coordinate().toString();
	}
	else if(idx.column() == COL_Type)
	{
		return obj->typeName();
	}

	return QVariant();
}

QVariant MapLayer::editRole(const QModelIndex &idx) const
{
	MapObject *obj = mObjects.at(idx.row());

	if(!obj)
	{
		return QVariant();
	}

	if(idx.column() == COL_Coord)
	{
		return QVariant::fromValue( obj->coordinate() );
	}
	else if(idx.column() == COL_Name)
	{
		return obj->name();
	}
	else if(idx.column() == COL_Type)
	{
		return QVariant::fromValue( obj->type() );
	}

	return QVariant();
}

void MapLayer::objectChangedNotify(MapObject *obj)
{
	if(!mObjects.contains(obj))
	{
		return;
	}

	const QModelIndex &idxFrom = index(mObjects.indexOf(obj), 0);
	const QModelIndex &idxTo = index(mObjects.indexOf(obj), columnCount()-1);

	emit dataChanged(idxFrom, idxTo);
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

MapObject *MapLayer::takeObjectAt(QModelIndex index)
{
	if(!index.isValid() || index.row() >= rowCount())
	{
		return 0;
	}

	beginRemoveColumns(QModelIndex(), index.row(), index.row());
	MapObject *obj = mObjects.takeAt( index.row() );
	endRemoveRows();
	return obj;
}

MapObject *MapLayer::takeObject(MapObject *obj)
{
	if(!mObjects.contains(obj))
	{
		return 0;
	}

	return takeObjectAt( index(mObjects.indexOf(obj), 0) );
}

MapObject *MapLayer::objectByMapKey(long mapKey)
{
	foreach(MapObject *obj, mObjects)
	{
		if(obj->mapKey() == mapKey)
		{
			return obj;
		}
	}

	return 0;
}

void MapLayer::deleteFiles()
{
	long number = mapGetSiteNumber( mapView()->mapHandle(), mSiteHandle);

	if(number <= 0)
	{
		qDebug()<<"*** СЛОЙ КАРТЫ: Не определен номер слоя.";
		return;
	}

	if(! mapDeleteSite(mapView()->mapHandle(), number))
	{
		qDebug()<<"*** СЛОЙ КАРТЫ: Ошибка удаления файлов.";
		return;
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

	return QTextCodec::codecForName("koi8r")->toUnicode( mapGetRscName(rsc) );
}

void MapLayer::addObject(MapObject *object, MapObject *parent)
{
	int row = mObjects.count();

	if(mObjects.contains(object) )
	{
		return;
	}

	beginInsertRows(QModelIndex(), row, row);
	object->setMapLayer( this );
	mObjects << object;
	endInsertRows();
}

MapVectorObject *MapLayer::addVectorObject(long rscCode, Coord coords, QString name)
{
	MapVectorObject *obj = new MapVectorObject(rscCode, this);
	addObject(obj);
	obj->setCoordinates(coords);
	obj->setName(name);
	return obj;
}

MapLineObject *MapLayer::addLineObject(long rscCode, QList<CoordPlane> coords)
{
	MapLineObject *obj = new MapLineObject(rscCode, this, coords);
	addObject(obj);
	return obj;
}

MapZoneObject *MapLayer::addZoneObject(long rscCode, QList<CoordPlane> coords)
{
	MapZoneObject *obj = new MapZoneObject(rscCode, coords, this);
	addObject(obj);
	return obj;
}

void MapLayer::removeObject(MapObject *object)
{
	int row = mObjects.indexOf(object);
	removeRow(row);
}

MapObject *MapLayer::objectAtIndex(const QModelIndex &index)
{
	if(!index.isValid() || index.row() >= rowCount())
	{
		return 0;
	}

	return mObjects.at( index.row());
}

QModelIndex MapLayer::index(int row, int column, const QModelIndex &parent) const
{
	MapObject *obj = mObjects.at(row);

	return createIndex(row, column, obj);
}

QModelIndex MapLayer::parent(const QModelIndex &child) const
{
	return QModelIndex();
}

int MapLayer::rowCount(const QModelIndex &parent) const
{
	return mObjects.count();
}

int MapLayer::columnCount(const QModelIndex &parent) const
{
	return COL_Count;
}

QVariant MapLayer::data(const QModelIndex &index, int role) const
{
	if(!index.isValid() || index.column() >= columnCount())
	{
		return QVariant();
	}

	if(role == Qt::DisplayRole)
	{
		return displayRole(index);
	}
	else if(role == Qt::EditRole)
	{
		return editRole(index);
	}

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

bool MapLayer::removeRows(int row, int count, const QModelIndex &parent)
{
	if(row < 0 || row+count > mObjects.count())
	{
		return false;
	}

	beginRemoveRows(QModelIndex(), row, row + count - 1);

	for(int i = 0; i < count; ++i)
	{
		MapObject *obj = mObjects.takeAt(row);
		obj->removeFromMap();
		delete obj;
	}

	endRemoveRows();

	return true;
}
