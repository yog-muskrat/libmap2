#include "layersmodel.h"
#include "maplayer.h"

#include <QDebug>
#include <QPixmap>

LayersModel::LayersModel(QObject *parent) :
	QAbstractTableModel(parent)
{
}

LayersModel::~LayersModel()
{
	qDeleteAll(mLayers);
}

void LayersModel::addLayer(MapLayer *layer)
{
	beginInsertRows( QModelIndex(), mLayers.count(), mLayers.count());

	mLayers << layer;
	connect(layer, SIGNAL(layerNameChanged(QString)), this, SLOT(onLayerUpdated()));
	connect(layer, SIGNAL(toggled(bool)), this, SLOT(onLayerUpdated()));

	endInsertRows();
}

void LayersModel::removeLayer(MapLayer *layer)
{
	removeLayer( mLayers.indexOf(layer));
}

void LayersModel::removeLayer(int row)
{
	if (row < 0 || row >= rowCount())
	{
		return;
	}

	beginRemoveRows(QModelIndex(), row, row);
	MapLayer *l = mLayers.takeAt(row);
	l->deleteFiles();
	l->deleteLater();
	endRemoveRows();
}

MapLayer *LayersModel::layerAt(int row)
{
	if(row < 0 || row >= rowCount())
	{
		return 0;
	}

	return mLayers[row];
}


int LayersModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);

	return mLayers.count();
}

int LayersModel::columnCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);

	return COL_Count;
}

QVariant LayersModel::data(const QModelIndex &index, int role) const
{
	if(!checkIndex(index))
	{
		return QVariant();
	}

	MapLayer *l = mLayers.at(index.row());

	// Пока все в одной куче. Нужно будет растащить.
	if(index.column() == COL_Name)
	{
		if(role == Qt::DisplayRole || role == Qt::EditRole)
		{
			return l->layerName();
		}
	}
	else if(index.column() == COL_Visible)
	{
		if(role == Qt::CheckStateRole)
		{
			return l->isVisible() ? Qt::Checked : Qt::Unchecked;
		}
		else if(role == Qt::SizeHintRole)
		{
			return QSize(32, 32);
		}
	}

	return QVariant();
}

bool LayersModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if(!checkIndex(index))
	{
		return false;
	}

	MapLayer *layer = mLayers.at(index.row());

	if(index.column() == COL_Visible && role == Qt::CheckStateRole)
	{
		Qt::CheckState cs = static_cast<Qt::CheckState>(value.toInt());

		layer->setVisible( cs == Qt::Checked );

		return true;
	}

	if(index.column() == COL_Name)
	{
		if(role == Qt::DisplayRole || role == Qt::EditRole)
		{
			layer->setLayerName( value.toString());
			return true;
		}
	}

	return QAbstractTableModel::setData(index, value, role);
}

QVariant LayersModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if(orientation != Qt::Horizontal)
	{
		return QAbstractTableModel::headerData(section, orientation, role);
	}

	if(section < 0 || section >= columnCount())
	{
		return QVariant();
	}

	if(section == COL_Visible)
	{
		if(role == Qt::DecorationRole)
		{
			return QPixmap(":eye");
		}
	}

	if(section == COL_Name)
	{
		if(role == Qt::DisplayRole || role == Qt::EditRole)
		{
			return "Название слоя";
		}
	}

	return QVariant();
}

Qt::ItemFlags LayersModel::flags(const QModelIndex &index) const
{
	Qt::ItemFlags flags = QAbstractItemModel::flags(index);

	if(index.column() == COL_Visible)
	{
		flags |= Qt::ItemIsUserCheckable;
	}
	else if(index.column() == COL_Name)
	{
		flags |= Qt::ItemIsEditable;
	}

	return flags;
}

void LayersModel::onLayerUpdated()
{
	MapLayer *layer = qobject_cast<MapLayer*>( sender() );
	if(!layer || !mLayers.contains( layer ))
	{
		return;
	}

	int row = mLayers.indexOf( layer );

	emit dataChanged(index(row, 0), index(row, columnCount()));
}

bool LayersModel::checkIndex(const QModelIndex &idx) const
{
	return idx.isValid() && idx.row() < rowCount() && idx.column() < columnCount();
}
