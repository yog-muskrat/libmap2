#include "mapgroupsmodel.h"
#include "mapview.h"

#include "groups/mapgroup.h"

Map2::GroupsModel::GroupsModel(Map2::MapView *parent) : QAbstractTableModel(parent)
{

}

Map2::GroupsModel::~GroupsModel()
{
	qDeleteAll(mGroups);
}

Map2::MapGroup *Map2::GroupsModel::groupAt(const QModelIndex &index) const
{
	return groupAt(index.row());
}

Map2::MapGroup *Map2::GroupsModel::groupAt(int row) const
{
	if(row < 0 || row >= rowCount())
	{
		return 0;
	}

	return mGroups[row];
}

Map2::MapGroup *Map2::GroupsModel::takeGroup(int row)
{
	if(row < 0 || row >= rowCount())
	{
		return 0;
	}

	beginRemoveRows(QModelIndex(), row, row);

	Map2::MapGroup *group =  mGroups.takeAt(row);

	endRemoveRows();

	return group;
}

Map2::MapGroup *Map2::GroupsModel::takeGroup(Map2::MapGroup *group)
{
	int row = mGroups.indexOf(group);
	return takeGroup(row);
}

void Map2::GroupsModel::addGroup(Map2::MapGroup *group)
{
	if(mGroups.contains( group ))
	{
		return;
	}

	beginInsertRows(QModelIndex(), rowCount(), rowCount());
	mGroups << group;
	endInsertRows();
}

int Map2::GroupsModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);
	return mGroups.count();
}

int Map2::GroupsModel::columnCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);
	return COL_Count;
}

QVariant Map2::GroupsModel::data(const QModelIndex &index, int role) const
{
	if(index.row() < 0 || index.column() < 0 || index.row() >= rowCount() || index.column() >= columnCount())
	{
		return QVariant();
	}

	if(role == Qt::DisplayRole)
	{
		MapGroup *group = groupAt(index);

		Q_ASSERT(group);

		if(index.column() == COL_Type)
		{
			MapGroup::Type type = group->type();
			if(type == MapGroup::MG_Simple)
			{
				return "Простая";
			}
			else if(type == MapGroup::MG_Formular)
			{
				return "Формуляр";
			}
			else if(type == MapGroup::MG_Stack)
			{
				return "Флагшток";
			}
		}
		else if(index.column() == COL_Name)
		{
			return group->name();
		}
	}

	return QVariant();
}

QVariant Map2::GroupsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if(orientation != Qt::Horizontal || role != Qt::DisplayRole)
	{
		return QAbstractTableModel::headerData(section, orientation, role);
	}

	if(section == COL_Type)
	{
		return "Тип";
	}
	else if(section == COL_Name)
	{
		return "Название";
	}

	return QVariant();
}
