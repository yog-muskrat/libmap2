#ifndef MAPSTACKGROUP_H
#define MAPSTACKGROUP_H

#include "map2/mapstructs.h"
#include "map2/groups/mapgroup.h"

#include <QList>

namespace Map2
{
class MapVectorObject;

class MapStackGroup : public MapGroup
{
public:
	explicit MapStackGroup(Map2::MapVectorObject *parent, Qt::AlignmentFlag parentPosition = Qt::AlignBottom);
	~MapStackGroup();

	virtual bool addChild(MapObject *child);
	virtual bool addChildren(QList<MapObject *> children);
	virtual MapGroup::Type type() const { return MG_Stack; }

protected:
	virtual void updateChildrenDisplayCoordinates();

private:
	void restoreInitialCoordinates();


	/// Временное решение. В последствии нужно добавить в сам MapObject понятия "Реальная координата" и "Отображаемая координата".
	QMap<MapObject*, Coord> mInitialCoordinates;
	Coord mParentInitialCoord;

	Qt::AlignmentFlag mParentPosition;
};
}

#endif // MAPSTACKGROUP_H
