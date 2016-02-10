#ifndef MAPGROUP_H
#define MAPGROUP_H

#include <QMap>
#include <QString>
#include "map2/mapstructs.h"

namespace Map2
{
class MapObject;

class MapObject;

/**
 * @brief Базовый класс для групповых объектов карты - формуляров, флагштоков и т.п.
 */
class MapGroup
{
public:
	enum Type
	{
		MG_Simple, /// Простая группировка. Объекты отображаются в своих реальных координатах
		MG_Stack, /// Вертикальная стопка (Флагшток). Объекты отображаются над базовым объектом в виде стопки.
		MG_Formular /// Формуляр. Объекты отображаются в виде формуляра базового объекта.
	};

	/*!
	 * \brief Поведение при вызове деструктора объекта группы
	 */
	enum DtorPolicy
	{
		DP_None, /// Ничего не делать
		DP_ShowChildren, /// Отобразить всех детей в реальных координатах.
		DP_RemoveChildren /// Удалить всех детей.
	};

	explicit MapGroup(MapObject *parent = 0) : mDtorPolicy(DP_ShowChildren), mChildrenVisible(true), pParent(parent){}
	virtual ~MapGroup();

	virtual Map2::MapGroup::Type type() {return MG_Simple;}

	virtual void update();

	void hideChildren() {setChildrenVisible(false);}
	void showChildren() {setChildrenVisible(true);}
	virtual void setChildrenVisible(bool visible);
	virtual QList<Map2::MapObject*> children() const {return mChildren; }
	bool childrenVisible() const {return mChildrenVisible;}
	virtual int childrenCount() const {return mChildren.count();}
	virtual bool addChild(Map2::MapObject *child);
	Map2::MapObject * takeChild(int pos);
	Map2::MapObject * takeChild(Map2::MapObject *child);

	void setDtorPolicy(Map2::MapGroup::DtorPolicy policy) {mDtorPolicy = policy;}
	Map2::MapGroup::DtorPolicy dtorPolicy() const {return mDtorPolicy;}

	QString name() const { return mName; }
	void setName(const QString &value) { mName = value; }

	MapObject *parent() const { return pParent; }
	void setParent(MapObject *value) { pParent = value; }

protected:
	virtual void updateChildrenDisplayCoordinates() {}
	virtual void restoreInitialChildrenCoordinates() {}

	DtorPolicy mDtorPolicy;
	bool mChildrenVisible;
	QString mName;

	QList<MapObject*> mChildren;
	MapObject *pParent;
};
}
#endif // MAPGROUP_H
