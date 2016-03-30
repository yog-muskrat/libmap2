#include "groups/mapstackgroup.h"
#include "objects/mapobject.h"
#include "objects/mapvectorobject.h"
#include "maphelper.h"
#include "maplayer.h"
#include "mapview.h"
#include "gis.h"

#include <QDebug>

Map2::MapStackGroup::MapStackGroup(MapVectorObject *parent, Qt::AlignmentFlag parentPosition) : MapGroup(parent), mParentPosition(parentPosition)
{
	if(parentPosition != Qt::AlignTop && parentPosition != Qt::AlignBottom)
	{
		qDebug()<<"*** ФЛАГШТОК: Некорректное позиция родителя"<<parentPosition<<". Будет установлено значение по умолчанию";
		mParentPosition = Qt::AlignBottom;
	}

	mParentInitialCoord = parent->coordinateGeo();
}

Map2::MapStackGroup::~MapStackGroup()
{
	restoreInitialCoordinates();
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

	mInitialCoordinates[child] = child->coordinateGeo();
	updateChildrenDisplayCoordinates();
	return true;
}

bool Map2::MapStackGroup::addChildren(QList<Map2::MapObject *> children)
{
	if(!MapGroup::addChildren(children))
	{
		return false;
	}
	foreach(Map2::MapObject *child, children)
	{
		if(mInitialCoordinates.contains(child))
		{
			continue;
		}

		mInitialCoordinates[child] = child->coordinateGeo();
	}
	updateChildrenDisplayCoordinates();
	return true;
}

void Map2::MapStackGroup::updateChildrenDisplayCoordinates()
{
	if(!parent() || !parent()->mapLayer() || childrenCount() == 0)
	{
		return;
	}

	double scale = parent()->mapLayer()->mapView()->scaleRatio();
	if(scale > 1)
	{
		scale = 1;
	}

	QList<MapObject*> items;

	items << parent();
	items += mChildren;

	Q_ASSERT(!items.isEmpty());

	if(mParentPosition == Qt::AlignTop)
	{
		for(int i = 0; i < items.count() / 2; ++i)
		{
			items.swap(i, items.count() - (1+i));
		}
	}

	Map2::MapVectorObject *parentObj = dynamic_cast<Map2::MapVectorObject*>(items.first());
	Q_ASSERT(parentObj);


	Map2::MapHelper *helper = pParent->mapLayer()->mapView()->helper();
	QPoint picturePos = helper->geoToPicture(parentObj->coordinateGeo());

	QRectF parentRect = parentObj->sizePix();

	for(int i = 1; i < items.count(); ++i)
	{

		MapVectorObject *mvo = dynamic_cast<MapVectorObject*>(items[i]);
		Q_ASSERT(mvo);

		QRectF childRect = mvo->sizePix();

		picturePos.setY(picturePos.y() - (parentRect.y() - childRect.y() * 0.3) * scale);

		Coord coord = helper->pictureToGeo(picturePos);

		mvo->setCoordinates(coord);

		parentRect = childRect;
	}
}

void Map2::MapStackGroup::restoreInitialCoordinates()
{
	foreach(MapObject*obj, mChildren)
	{
		MapVectorObject *mvo = dynamic_cast<MapVectorObject*>(obj);
		Q_ASSERT(mvo && mInitialCoordinates.contains(mvo));

		mvo->setCoordinates(mInitialCoordinates[mvo]);
	}

	MapVectorObject *pvo = dynamic_cast<MapVectorObject*>(parent());
	Q_ASSERT(pvo);

	pvo->setCoordinates( mParentInitialCoord );
}
