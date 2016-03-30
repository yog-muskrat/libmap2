#include "maplayer.h"
#include "mapview.h"
#include "objects/mapobject.h"
#include "objects/mapvectorobject.h"
#include "objects/maplineobject.h"
#include "objects/mapzoneobject.h"

#include "gis.h"

#include <QDir>
#include <QFile>
#include <QIcon>
#include <QFont>
#include <QDebug>
#include <QTextCodec>
#include <QApplication>

using namespace Map2;

MapLayer::MapLayer(const QString &rscName, const QString &key, const QString &name, Map2::MapView *parent, bool temp) :
	QAbstractTableModel(parent),
	pMapView(parent),
	mSiteHandle(-1),
	mRscName(rscName),
	mLayerName(name),
	mLayerKey(key),
	mVisible(true),
	mValid(false),
	mLocked(false),
	mTemp(temp)
{
	mFileName = key;
	QString sitname = QString("%0/%1.sit").arg(pMapView->sitDir()).arg(mFileName);
	QString rscname = QString("%0/%1").arg(pMapView->rscDir(), rscName);

	if(!QFile::exists(rscname))
	{
		qDebug()<<"Ошибка классификатора";
		return;
	}

	if(mTemp)
	{
		mSiteHandle = mapCreateAndAppendTempSite(pMapView->mapHandle(), qPrintable(rscname));
	}
	else
	{
		MAPREGISTER mapreg;
		LISTREGISTER listreg;
		CREATESITE cs;

		mapGetMapInfo(pMapView->mapHandle(), 1, &mapreg, &listreg);
		memset((void*)&cs,0,sizeof(cs));
		strncpy(cs.MapName, mapreg.Name, 32);

		cs.Length = sizeof( CREATESITE );
		cs.MaterialProjection = mapreg.MaterialProjection;
		cs.MapType = mapreg.MapType;
		cs.Scale = mapreg.Scale;
		cs.AxisMeridian = mapreg.AxisMeridian;
		cs.FirstMainParallel = mapreg.FirstMainParallel;
		cs.SecondMainParallel = mapreg.SecondMainParallel;
		cs.MainPointParallel = mapreg.MainPointParallel;
		mSiteHandle = mapCreateAndAppendSite(pMapView->mapHandle(), qPrintable(sitname), qPrintable(rscname), &cs);
	}

	mSelectHandle = mapCreateSiteSelectContext(pMapView->mapHandle(), mSiteHandle);

	mValid = mSiteHandle > 0;

	//! Нижеследующий блок - костыль против странного глюка с дублированием первого объекта в сите.
	//! Возможно, его можно будет убрать после обновления библиотек.
	HOBJ invisibleRootObject = mapCreateSiteObject(pMapView->mapHandle(), siteHandle());
	mapAppendPointPlane(invisibleRootObject, 0, 0);
	mapCommitObject(invisibleRootObject);
	mapFreeObject(invisibleRootObject);
}

MapLayer::~MapLayer()
{
	if(mSiteHandle > 1 && pMapView->mapHandle() > 0)
	{
		mapDeleteSelectContext(selectHandle());

		qDeleteAll(mObjects);
		mapCloseData(mSiteHandle);
	}
}

QVariant MapLayer::displayRole(const QModelIndex &idx) const
{
	MapObject *obj = objectAtIndex(idx);
	Q_ASSERT(obj);

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
		return obj->coordinatePlane().toString();
	}
	else if(idx.column() == COL_Type)
	{
		return obj->typeName();
	}

	return QVariant();
}

QVariant MapLayer::editRole(const QModelIndex &idx) const
{
	MapObject *obj = objectAtIndex(idx);
	Q_ASSERT(obj);

	if(idx.column() == COL_Coord)
	{
		return QVariant::fromValue( obj->coordinatePlane() );
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

QVariant MapLayer::decorationRole(const QModelIndex &idx) const
{
	MapObject *obj = objectAtIndex(idx);
	Q_ASSERT(obj);

	if(idx.column() == COL_Type)
	{
		if(obj->type() == MapObject::MO_Vector)
		{
			return QIcon(":map_object");
		}
		else if(obj->type() == MapObject::MO_Line)
		{
			return QIcon(":map_line");
		}
		else if(obj->type() == MapObject::MO_Zone)
		{
			return QIcon(":map_polygon");
		}
		else if(obj->type() == MapObject::MO_Text)
		{
			return QIcon(":map_text");
		}
		else
		{
			return QIcon(":help");
		}
	}

	return QVariant();
}

void MapLayer::objectChangedNotify(Map2::MapObject *obj)
{
	int row = mObjects.indexOf(obj);

	if(row < 0)
	{
		return;
	}

	const QModelIndex &idxFrom = index(row, 0);
	const QModelIndex &idxTo = index(row, columnCount()-1);

	emit dataChanged(idxFrom, idxTo);
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
		emit visibilityToggled(mVisible);
	}
}

void MapLayer::setLocked(bool locked)
{
	if(locked != mLocked)
	{
		mLocked = locked;
		mapSetSiteEditFlag(mapHandle(), siteHandle(),  mLocked ? 0 : 1);
		emit lockToggled(mLocked);
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

void MapLayer::setLayerKey(const QString &value)
{
	mLayerKey = value;
	emit layerKeyChanged(mLayerKey);
}

Map2::MapObject *MapLayer::takeObjectAt(QModelIndex index)
{
	if(!index.isValid() || index.row() >= rowCount())
	{
		return 0;
	}

	beginRemoveColumns(QModelIndex(), index.row(), index.row());
	MapObject *obj = mObjects.takeAt( index.row() );
	obj->setMapLayer(0);
	endRemoveRows();
	return obj;
}

Map2::MapObject *MapLayer::takeObject(Map2::MapObject *obj)
{
	if(!mObjects.contains(obj))
	{
		return 0;
	}

	return takeObjectAt( index(mObjects.indexOf(obj), 0) );
}

MapObject *MapLayer::objectByParameter(const QString &parameter, const QVariant &value) const
{
	foreach(MapObject *obj, mObjects)
	{
		if(obj->parameter(parameter) == value)
		{
			return obj;
		}
	}

	return 0;
}

Map2::MapObject *MapLayer::objectByHandle(HMAP hMap)
{
	foreach(MapObject *obj, mObjects)
	{
		if(obj->containsObject(hMap))
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

void MapLayer::addObject(Map2::MapObject *object)
{
	int row = mObjects.count();

	if(mObjects.contains(object) )
	{
		return;
	}

	beginInsertRows(QModelIndex(), row, row);

	if(object->mapLayer() != 0)
	{
		object->mapLayer()->takeObject(object);
	}

	object->setMapLayer( this );
	mObjects << object;
	endInsertRows();
}

Map2::MapVectorObject *MapLayer::addVectorObject(const QString &rscKey, Map2::Coord coords, QString name)
{
	MapVectorObject *obj = new MapVectorObject(rscKey);
	addObject(obj);
	obj->setCoordinates(coords);
	obj->setName(name);
	return obj;
}

Map2::MapLineObject *MapLayer::addLineObject(const QString &rscKey, const QList<Map2::CoordPlane> &coords)
{
	MapLineObject *obj = new MapLineObject(rscKey, coords);
	addObject(obj);
	return obj;
}

Map2::MapZoneObject *MapLayer::addZoneObject(const QString &rscKey, QList<Map2::CoordPlane> coords)
{
	MapZoneObject *obj = new MapZoneObject(rscKey, coords);
	addObject(obj);
	return obj;
}

MapZoneObject *MapLayer::addZoneObject(const QString &rscKey, QList<Coord> coords)
{
	MapZoneObject *obj = new MapZoneObject(rscKey, coords);
	addObject(obj);
	return obj;
}

void MapLayer::removeObject(Map2::MapObject *object)
{
	int row = mObjects.indexOf(object);
	removeRow(row);
}

Map2::MapObject *MapLayer::objectAtIndex(const QModelIndex &index) const
{
	if(!index.isValid())
	{
		return 0;
	}

	return objectAtIndex(index.row());
}

Map2::MapObject *MapLayer::objectAtIndex(int row) const
{
	if(row < 0 || row >= mObjects.count())
	{
		return 0;
	}

	return mObjects[row];
}

int MapLayer::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);

	return mObjects.count();
}

int MapLayer::columnCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);

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
	else if(role == Qt::DecorationRole)
	{
		return decorationRole(index);
	}
	else if(role == Qt::FontRole)
	{
		QFont f = qApp->font();
		f.setPointSize(10);
		return f;
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
	Q_UNUSED(parent);

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

void MapLayer::clear()
{
	if(rowCount() == 0)
	{
		return;
	}

	removeRows(0, rowCount());
}
