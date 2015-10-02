#ifndef MAPLAYER_H
#define MAPLAYER_H

#include "gis.h"

#include <QAbstractItemModel>

class MapView;
class MapObject;

class MapLayer : public QAbstractItemModel
{
	Q_OBJECT
public:

	enum Columns
	{
		COL_Name,
		COL_Coord,
		COL_Type,
		COL_Count
	};

	~MapLayer();

	HSITE siteHandle() const {return mSiteHandle;}
	HMAP mapHandle() const;

	bool isValid();

	bool isVisible() { return mVisible; }
	void setVisible(bool visible = true);

	QString layerName() const {return mLayerName;}
	void setLayerName(const QString &value);

	/*!
	 * \brief Удаляет файлы слоя.
	 * \return Признак успешности.
	 */
	void deleteFiles();

	/*!
	 * \brief Возвращает название используемого классификатора.
	 */
	QString rscName() const;

	/*!
	 * \brief Возвращает указатель на используемую карту.
	 */
	MapView *mapView() { return pMapView; }

	void addObject(MapObject *object, MapObject *parent = 0);
	void removeObject(MapObject *object);

	MapObject * objectAtIndex(const QModelIndex &index);

	// QAbstractItemModel interface
	virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
	virtual QModelIndex parent(const QModelIndex &child) const;
	virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
	virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
	virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
	virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

	friend class MapView;

signals:
	void layerNameChanged(QString newName);
	void toggled(bool visible);

private:
	explicit MapLayer(quint16 id, QString rscName, MapView *parent);
	QVariant displayRole(const QModelIndex &idx) const;
	QVariant editRole(const QModelIndex &idx) const;

	MapView *pMapView;

	QList<MapObject*> mObjects;
	QHash<quint16, MapObject*> mObjectsHash;

	HSITE mSiteHandle;
	QString mRscName;
	QString mLayerName;
	QString mFileName;

	quint16 mLastInternalId;
	bool mVisible;
	bool mValid;
};

#endif // MAPLAYER_H
