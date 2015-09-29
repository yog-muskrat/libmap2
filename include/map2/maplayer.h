#ifndef MAPLAYER_H
#define MAPLAYER_H

#include "gis/mapapi.h"
#include "gis/maptype.h"

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

	void addObject(MapObject *object, MapObject *parent = 0);
	void removeObject(MapObject *object);

	// QAbstractItemModel interface
	virtual QModelIndex index(int row, int column, const QModelIndex &parent) const;
	virtual QModelIndex parent(const QModelIndex &child) const;
	virtual int rowCount(const QModelIndex &parent) const;
	virtual int columnCount(const QModelIndex &parent) const;
	virtual QVariant data(const QModelIndex &index, int role) const;
	virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;

	friend class MapView;

signals:
	void layerNameChanged(QString newName);
	void toggled(bool visible);

private:
	explicit MapLayer(quint16 id, QString rscName, MapView *parent);

	MapView *pMapView;

	QList<MapObject*> mObjects;
	QHash<quint16, MapObject*> mObjectsHash;

	HSITE mSiteHandle;
	QString mRscName;
	QString mLayerName;

	quint16 mLastInternalId;
	bool mVisible;
	bool mValid;
};

#endif // MAPLAYER_H
