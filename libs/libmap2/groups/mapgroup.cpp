#include "groups/mapgroup.h"
#include "objects/mapobject.h"
#include "objects/mapvectorobject.h"

#include <QDebug>

Map2::MapGroup::MapGroup(Map2::MapVectorObject *parent) :
	mDtorPolicy(DP_ShowChildren),
	mChildrenVisible(true),
	pParent(parent)
{
	if(parent)
	{
		parent->addChildGroup(this);
	}
}

Map2::MapGroup::~MapGroup()
{
	pParent->pChildGroups.removeAll(this);

	if(dtorPolicy() == DP_ShowChildren)
	{
		showChildren();

		foreach(MapObject *obj, mChildren)
		{
			obj->pParentGroup = 0;
		}

	}
	else if(dtorPolicy() == DP_RemoveChildren)
	{
		foreach(MapObject *obj, mChildren)
		{
			obj->remove();
		}
	}

	///NOTE: Сделано для избежания бага с исчезновением родительского объекта при уничтожении группы.
	parent()->show();
}

void Map2::MapGroup::update()
{
	if(!childrenVisible() || childrenCount() == 0)
	{
		return;
	}
	updateChildrenDisplayCoordinates();
}

void Map2::MapGroup::setChildrenVisible(bool visible)
{
	mChildrenVisible = visible;

	foreach(MapObject*obj, mChildren)
	{
		if(visible)
		{
			obj->show();
		}
		else
		{
			obj->hide();
		}
	}
}

bool Map2::MapGroup::addChild(Map2::MapObject *child)
{
	if(mChildren.contains(child))
	{
		return false;
	}

	mChildren.append(child);
	child->setParentGroup(this);
	return true;
}

bool Map2::MapGroup::addChildren(QList<Map2::MapObject *> children)
{
	foreach(Map2::MapObject *child, children)
	{
		if(mChildren.contains(child))
		{
			continue;
		}
		mChildren.append(child);
		child->setParentGroup(this);
	}

	return true;
}

Map2::MapObject *Map2::MapGroup::takeChild(int pos)
{
	if(pos < 0 || pos >= childrenCount())
	{
		return 0;
	}

	Map2::MapObject *child = mChildren.takeAt(pos);

	child->pParentGroup = 0;
	update();

	return child;
}

Map2::MapObject *Map2::MapGroup::takeChild(Map2::MapObject *child)
{
	return takeChild(mChildren.indexOf(child));
}
