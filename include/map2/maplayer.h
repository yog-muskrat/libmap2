#ifndef MAPLAYER_H
#define MAPLAYER_H

#include "gis.h"
#include "structs.h"

#include <QAbstractItemModel>

class MapView;
class MapObject;
class MapVectorObject;
class MapLineObject;
class MapZoneObject;

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

	MapObject *takeObjectAt(QModelIndex index);
	MapObject *takeObject(MapObject *obj);

	/*!
	 * \brief Возвращает объект по его уникальному номеру на карте.
	 * \param number Уникальный номер объекта карты.
	 */
	MapObject *objectByMapKey(long mapIndex);

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
	MapVectorObject* addVectorObject(long rscCode, Coord coords = Coord(), QString name = "");
	MapLineObject* addLineObject(long rscCode, QList<CoordPlane> coords = QList<CoordPlane>());
	MapZoneObject* addZoneObject(long rscCode, QList<CoordPlane> coords = QList<CoordPlane>());

	void removeObject(MapObject *object);

	MapObject * objectAtIndex(const QModelIndex &index);


	// QAbstractItemModel interface
	virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
	virtual QModelIndex parent(const QModelIndex &child) const;
	virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
	virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
	virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
	virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
	virtual bool removeRows(int row, int count, const QModelIndex &parent);

	friend class MapView;
	friend class MapObject;

signals:
	void layerNameChanged(QString newName);
	void toggled(bool visible);

private:
	explicit MapLayer(quint16 id, QString rscName, MapView *parent, bool temp = false);
	QVariant displayRole(const QModelIndex &idx) const;
	QVariant editRole(const QModelIndex &idx) const;

	void objectChangedNotify(MapObject *obj);

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
