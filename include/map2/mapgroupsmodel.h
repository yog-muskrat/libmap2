#ifndef MAPGROUPSMODEL_H
#define MAPGROUPSMODEL_H

#include <QAbstractTableModel>

namespace Map2
{
class MapView;
class MapGroup;

/*!
 * \brief Модель групповых объектов карты.
 * Используется для синхронизации обновления внешнего вида групповых объектов при изменении масштаба карты.
 */
class GroupsModel : public QAbstractTableModel
{
	Q_OBJECT
public:
	enum Column
	{
		COL_Type,
		COL_Name,
		COL_Count
	};

	explicit GroupsModel(Map2::MapView *parent);
	~GroupsModel();

	Map2::MapGroup* groupAt(const QModelIndex &index) const;
	Map2::MapGroup* groupAt(int row) const;

	Map2::MapGroup * takeGroup(int row);
	Map2::MapGroup * takeGroup(Map2::MapGroup *group);

	void addGroup(MapGroup *group);

	virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
	virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
	virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
	virtual QVariant headerData(int section, Qt::Orientation orientation = Qt::Horizontal, int role = Qt::DisplayRole) const;

private:
	QList<MapGroup*> mGroups;
};
}

#endif // MAPGROUPSMODEL_H
