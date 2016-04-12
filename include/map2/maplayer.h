#ifndef MAPLAYER_H
#define MAPLAYER_H

#include "mapstructs.h"

#include <QAbstractTableModel>

namespace Map2
{

class MapView;
class MapObject;
class MapVectorObject;
class MapLineObject;
class MapZoneObject;

class MapLayer : public QAbstractTableModel
{
	Q_OBJECT
public:

	enum Columns
	{
		COL_Type,
		COL_Name,
		COL_Coord,
		COL_Count
	};

	~MapLayer();

	HSITE siteHandle() const {return mSiteHandle;}
	HMAP mapHandle() const;
	HSELECT selectHandle() const {return mSelectHandle;}

	bool isValid();

	bool isVisible() { return mVisible; }
	void setVisible(bool visible = true);

	bool isLocked(){ return mLocked; }
	void setLocked(bool locked = true);

	bool isTemporary() const {return mTemp;}

	QString layerName() const {return mLayerName;}
	void setLayerName(const QString &value);

	QString layerKey() const {return mLayerKey;}
	void setLayerKey(const QString &value);

	Map2::MapObject *takeObjectAt(QModelIndex index);
	Map2::MapObject *takeObject(Map2::MapObject *obj);

	Map2::MapObject *objectByParameter(const QString &parameter, const QVariant &value) const;

	/*!
	 * \brief Возвращает объект по его уникальному номеру на карте.
	 * \param number Уникальный номер объекта карты.
	 */
	Map2::MapObject *objectByHandle(HMAP hMap);

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

	void addObject(Map2::MapObject *object);
	Map2::MapVectorObject* addVectorObject(const QString &rscKey, Map2::Coord coords = Coord(), QString name = "");
	Map2::MapLineObject* addLineObject(const QString &rscKey, const QList<Coord> &coords = QList<Map2::Coord>());
	Map2::MapZoneObject* addZoneObject(const QString &rscKey, QList<Map2::Coord> coords = QList<Map2::Coord>());

	void removeObject(MapObject *object);

	Map2::MapObject * objectAtIndex(const QModelIndex &index) const;
	Map2::MapObject * objectAtIndex(int row) const;

	QModelIndex objectIndex(Map2::MapObject *object) const;

	// QAbstractItemModel interface
	virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
	virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
	virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
	virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
	virtual bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());

	friend class MapView;
	friend class MapObject;

public slots:
	/*!
	 * \brief Удаляет все объекты слоя.
	 */
	void clear();

signals:
	void layerNameChanged(QString newName);
	void layerKeyChanged(QString newName);
	void visibilityToggled(bool visible);
	void lockToggled(bool locked);

private:
	explicit MapLayer( const QString &rscName, const QString &key, const QString &name, MapView *parent, bool temp = false);
	QVariant displayRole(const QModelIndex &idx) const;
	QVariant editRole(const QModelIndex &idx) const;
	QVariant decorationRole(const QModelIndex &idx) const;

	void objectChangedNotify(MapObject *obj);

	MapView *pMapView;

	QList<MapObject*> mObjects;
	QHash<quint16, MapObject*> mObjectsHash; ///TODO: Не забыть про сию задумку.

	HSITE mSiteHandle;
	HSELECT mSelectHandle;
	QString mRscName;
	QString mLayerName;
	QString mLayerKey;
	QString mFileName;

	bool mVisible;
	bool mValid;
	bool mLocked;
	bool mTemp;
};
}
#endif // MAPLAYER_H
