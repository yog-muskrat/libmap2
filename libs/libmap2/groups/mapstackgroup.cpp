#include "groups/mapstackgroup.h"
#include "objects/mapobject.h"
#include "objects/mapvectorobject.h"
#include "maphelper.h"
#include "maplayer.h"
#include "mapview.h"
#include "gis.h"

#include <QDebug>

Map2::MapStackGroup::MapStackGroup(MapVectorObject *parent) : MapGroup(parent)
{

}

bool Map2::MapStackGroup::addChild(Map2::MapObject *child)
{
	if(child->type() != MapObject::MO_Vector)
	{
		return false;
	}

	if(!MapGroup::addChild(child))
	{
		return false;
	}

	mInitialCoordinates[child] = child->coordinate();
	updateChildrenDisplayCoordinates();

	updateChildrenDisplayCoordinates();
	return true;
}

void Map2::MapStackGroup::updateChildrenDisplayCoordinates()
{
	if(!parent() || !parent()->mapLayer() || childrenCount() == 0)
	{
		return;
	}

	HMAP hMap = parent()->mapLayer()->mapHandle();

	MapVectorObject *parentObj = dynamic_cast<MapVectorObject*>(parent());
	Q_ASSERT(parentObj);

	Map2::MapHelper *helper = pParent->mapLayer()->mapView()->helper();

	QPoint picturePos = helper->geoToPicture(parentObj->coordinatesGeo());

	///TODO: Это тут временно. Нужно перенести, скорее всего, в MapView.
	double scale = mapGetMapScale(hMap) / parent()->mapLayer()->mapView()->scale();
	if(scale > 1)
	{
		scale = 1;
	}

	QRectF rect = parentObj->sizePix();

//	qDebug()<<"Parent size= "<<rect << "scale="<<scale;

	foreach (MapObject *obj, mChildren)
	{
		MapVectorObject *mvo = dynamic_cast<MapVectorObject*>(obj);
		Q_ASSERT(mvo);
		picturePos.setY( picturePos.y() - rect.y() * scale *.99);

		Coord coord = helper->pictureToGeo(picturePos);

		mvo->setCoordinates(coord);

		rect = mvo->sizePix();

//		qDebug()<<"   Child size="<<rect;
	}
}

void Map2::MapStackGroup::restoreInitialChildrenCoordinates()
{
	foreach(MapObject*obj, mChildren)
	{
		MapVectorObject *mvo = dynamic_cast<MapVectorObject*>(obj);
		Q_ASSERT(mvo && mInitialCoordinates.contains(mvo));

		mvo->setCoordinates(mInitialCoordinates[mvo]);
	}
}
