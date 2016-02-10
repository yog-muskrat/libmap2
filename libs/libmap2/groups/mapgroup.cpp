#include "groups/mapgroup.h"
#include "objects/mapobject.h"


Map2::MapGroup::~MapGroup()
{
	if(dtorPolicy() == DP_ShowChildren)
	{
		restoreInitialChildrenCoordinates();
		showChildren();
	}
	else if(dtorPolicy() == DP_RemoveChildren)
	{
		foreach(MapObject *obj, mChildren)
		{
			obj->remove();
		}
	}
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
	child->setGroup(this);
	return true;
}

Map2::MapObject *Map2::MapGroup::takeChild(int pos)
{
	if(pos < 0 || pos >= childrenCount())
	{
		return 0;
	}

	Map2::MapObject *child = mChildren.takeAt(pos);

	update();

	return child;
}

Map2::MapObject *Map2::MapGroup::takeChild(Map2::MapObject *child)
{
	return takeChild(mChildren.indexOf(child));
}

