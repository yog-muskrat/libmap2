#ifndef LAYERSMODEL_H
#define LAYERSMODEL_H

#include <QAbstractTableModel>

#include "gis.h"

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
		COL_Name,
		COL_Count
	};

	explicit LayersModel(QObject *parent = 0);
	~LayersModel();

	void addLayer(MapLayer * layer);
	void removeLayer(MapLayer *layer);
	void removeLayer(int row);
	MapLayer * layerAt(int row);
	MapLayer * layerByHandle(HSITE handle);

	virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
	virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
	virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
	virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
	virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
	virtual Qt::ItemFlags flags(const QModelIndex &index) const;

private slots:
	void onLayerUpdated();

private:
	bool checkIndex( const QModelIndex &idx) const;

	QList<MapLayer*> mLayers;
};

#endif // LAYERSMODEL_H
