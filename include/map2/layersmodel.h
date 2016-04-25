#ifndef LAYERSMODEL_H
#define LAYERSMODEL_H

#include <QAbstractTableModel>

#include "mapstructs.h"

namespace Map2 {

class MapLayer;
class MapObject;

/*!
 * \brief Модель для работы с пользовательскими слоями карты.
 */
class LayersModel : public QAbstractTableModel
{
	Q_OBJECT
public:
	enum Columns
	{
		COL_Visible,
		COL_Locked,
		COL_Name,
		COL_Temp, /// Тип слоя - временный или постоянный
		COL_Count
	};

	explicit LayersModel(QObject *parent = 0);
	~LayersModel();

	int addLayer(Map2::MapLayer * layer);
	void removeLayer(Map2::MapLayer *layer);
	void removeLayer(int row);

	int layerIndex(Map2::MapLayer *l) const;
	Map2::MapLayer* layerAt(int row) const;
	Map2::MapLayer* layerByHandle(HSITE handle) const;
	Map2::MapLayer* layerByKey(const QString &key) const;

	bool containsKey(const QString &layerKey) const;

	virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
	virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
	virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
	virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
	virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
	virtual Qt::ItemFlags flags(const QModelIndex &index) const;

private slots:
	void onLayerUpdated();

private:
	QVariant displayRole(const QModelIndex &index)const ;
	QVariant checkStateRole(const QModelIndex &index) const;
	QVariant decorationRole(const QModelIndex &index) const;
	QVariant editRole(const QModelIndex &index) const;

	bool setCheckStateRole(QModelIndex index, QVariant value);
	bool setEditRole(QModelIndex index, QVariant value);
	bool checkIndex( const QModelIndex &idx) const;

	QList<MapLayer*> mLayers;
};
}

#endif // LAYERSMODEL_H
