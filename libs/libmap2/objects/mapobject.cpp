#include "objects/mapobject.h"
#include "maplayer.h"
#include "mapview.h"
#include "maphelper.h"
#include "groups/mapgroup.h"

#include "gis.h"

#include <QDebug>
#include <QTextCodec>

using namespace Map2;

MapObject::MapObject(Map2::MapObject::Type t, Map2::MapLayer *layer):
	mType(t),
	pLayer(layer),
	mHidden(false),
	mSelected(false),
	pParentGroup(0)
{
	if(pLayer)
	{
		pLayer->addObject(this);
	}
}

MapObject::~MapObject()
{
	if(mapLayer())
	{
		clearHandles();
	}

	if(pParentGroup)
	{
		pParentGroup->takeChild( this );
	}

	foreach(Map2::MapGroup *grp, pChildGroups)
	{
		if(grp)
		{
			delete grp;
		}
	}
}

void MapObject::remove()
{
	if(mapLayer())
	{
		mapLayer()->removeObject(this);
	}
	else
	{
		removeFromMap();
	}
}

void MapObject::centerOnObject() const
{
	if(!mapLayer())
	{
		return;
	}

	mapLayer()->mapView()->setCenter( coordinatePlane() );
}

void MapObject::setSelected(bool b)
{
	mSelected = b;

	if(!helper())
	{
		return;
	}

	if(mSelected)
	{
		foreach(HOBJ *hObj, mapHandles())
		{
			helper()->setSelected(*hObj);
		}

		commit();
	}
	else
	{
		refresh();
	}
}

CoordPlane MapObject::coordinatePlane() const
{
	if(!mapLayer())
	{
		qDebug()<<"*** MAP OBJECT: Невозможно обработать прямоугольную координату, пока объект не добавлен на карту";
		return CoordPlane();
	}

	MapHelper *helper = mapLayer()->mapView()->helper();

	return helper->geoToPlane( coordinateGeo() );
}

void MapObject::bringToFront()
{
	if(!mapLayer())
	{
		return;
	}
	refresh();
}

QString MapObject::typeName() const
{
	switch(mType)
	{
	case Map2::MapObject::MO_Vector: return "Одиночный";
	case Map2::MapObject::MO_Line: return "Линия";
	case Map2::MapObject::MO_Zone: return "Зона";
	case Map2::MapObject::MO_Text: return "Текст";
	case Map2::MapObject::MO_Commline: return "Линия связи";
	case Map2::MapObject::MO_Sector: return "Сектор";
	default: break;
	}

	return "";
}

void MapObject::setMapLayer(Map2::MapLayer *layer)
{
	if(layer == pLayer)
	{
		return;
	}

	pLayer = layer;
	refresh();
}

void MapObject::commit()
{
	if(mapLayer())
	{

		foreach(HOBJ *hObj, mapHandles())
		{
			helper()->commitObject(*hObj);
		}

		mapLayer()->objectChangedNotify(this);
	}
}

MapHelper *MapObject::helper() const
{
	if(!mapLayer())
	{
		return 0;
	}

	return mapLayer()->mapView()->helper();
}

void MapObject::clearHandles()
{
	if(!helper())
	{
		return;
	}

	foreach(HOBJ *hObj, mapHandles())
	{
		helper()->clearHandle(hObj);
	}
}

void MapObject::removeFromMap()
{
	if(!helper())
	{
		return;
	}

	foreach(HOBJ *hObj, mapHandles())
	{
		helper()->removeObject(*hObj);
	}

	clearHandles();
}

void MapObject::refresh()
{
	repaint();

	if(!mName.isEmpty())
	{
		setName(mName);
	}

	if(mSelected)
	{
		setSelected(true);
	}

	if(mHidden)
	{
		setHidden(true);
	}

	///TODO: Необходимо так же обновить семантики объекта, если они были заданы
}
QPair<int, int> MapObject::displayRange() const
{
	return mDisplayRange;
}

void MapObject::setDisplayRange(const QPair<int, int> &value)
{
	if(mDisplayRange == value)
	{
		return;
	}

	foreach(HOBJ *hObj, mapHandles())
	{
		if(value.first == -1 || value.second == -1)
		{
			mapClearBotTop(*hObj);
		}

		if(value.first == 0)
		{
			mapSetObjectBotScale(*hObj, mDisplayRange.first);
		}
		else if(value.first > 0)
		{
			mapSetObjectBotScale(*hObj, value.first);
		}

		if(value.second == 0)
		{
			mapSetObjectTopScale(*hObj, mDisplayRange.second);
		}
		else if(value.second > 0)
		{
			mapSetObjectTopScale(*hObj, value.second);
		}
	}

	mDisplayRange = value;

	commit();
}

void MapObject::setDisplayRange(int min, int max)
{
	setDisplayRange( qMakePair(min, max) );
}


void MapObject::setParentGroup(MapGroup *group)
{
	if(pParentGroup == group)
	{
		return;
	}

	if(pParentGroup != 0)
	{
		pParentGroup->takeChild(this);
	}

	pParentGroup = group;
}

void MapObject::addChildGroup(MapGroup *childGroup)
{
	if(pChildGroups.contains( childGroup ))
	{
		return;
	}

	pChildGroups << childGroup;
}

void MapObject::setName(QString name)
{
	mName = name;

	if(mapLayer())
	{
		pLayer->objectChangedNotify(this);
	}
}

bool MapObject::containsObject(HOBJ hObj)
{
	if(!helper())
	{
		return false;
	}

	/// Предполагается, что объекты не могут находится на разных картах,
	/// поэтому используется идентификатор карты текущего слоя

	if( mapGetObjectSiteIdent(mapLayer()->mapHandle(), hObj) != mapLayer()->siteHandle())
	{
		return false;
	}

	long key = helper()->objectMapKey( hObj );

	if(key <=0 )
	{
		return false;
	}

	foreach(HOBJ *hobj, mapHandles())
	{
		long selfKey = mapObjectKey(*hobj);
		if(key == selfKey)
		{
			return true;
		}
	}

	return false;
}

void MapObject::setParameter(QString parameter, QVariant value)
{
	mParameters[parameter] = value;
}

QVariant MapObject::parameter(QString parameter) const
{
	return mParameters[parameter];
}

void MapObject::hide()
{
	setHidden(true);
}

void MapObject::show()
{
	setHidden(false);
}

void MapObject::setHidden(bool hidden)
{
	mHidden = hidden;

	if(!helper())
	{
		return;
	}

	/// NOTE: Закомментированый фрагмент содержит невыявленные на данный момент баги, из-за которых некоторые объекты
	/// не скрываются или не появляются, когда их об этом просят. Если текущий вариант не снижает быстродействия,
	/// то можно удалить закомментированный код.
	//	HMAP hMap = mapLayer()->mapHandle();
	//	HSITE hSite = mapLayer()->siteHandle();
	//	HSELECT hSelect = mapLayer()->selectHandle();

	//	foreach(HOBJ *hObj, mapHandles())
	//	{
	//		if(hidden)
	//		{
	//			helper()->removeObjectFromSelection(hSelect, *hObj);
	//		}
	//		else
	//		{
	//			helper()->addObjectToSelection(hSelect, *hObj);
	//		}
	//	}

	//	mapSetSiteViewSelect(hMap, hSite, hSelect);

	if(hidden)
	{
		foreach(HOBJ *hObj, mapHandles())
		{
			helper()->removeObject(*hObj);
		}
	}
	else
	{
		refresh();
	}

	mapLayer()->objectChangedNotify(this);
}
