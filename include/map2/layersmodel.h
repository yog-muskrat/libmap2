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
		COL_Count
	};

	explicit LayersModel(QObject *parent = 0);
	~LayersModel();

	int addLayer(Map2::MapLayer * layer);
	void removeLayer(Map2::MapLayer *layer);
	void removeLayer(int row);
	Map2::MapLayer * layerAt(int row);
	Map2::MapLayer * layerByHandle(HSITE handle);

	virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
	virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
	virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
	virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
	virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
	virtual Qt::ItemFlags flags(const QModelIndex &index) const;

private slots:
	void onLayerUpdated();

	QVariant displayRole(const QModelIndex &index)const ;
	QVariant checkStateRole(const QModelIndex &index) const;
	QVariant decorationRole(const QModelIndex &index) const;

	bool setCheckStateRole(QModelIndex index, QVariant value);
	bool setEditRole(QModelIndex index, QVariant value);

private:
	bool checkIndex( const QModelIndex &idx) const;

	QList<MapLayer*> mLayers;
};
}

#endif // LAYERSMODEL_H
