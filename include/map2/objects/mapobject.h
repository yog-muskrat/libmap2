#ifndef MAPOBJECT_H
#define MAPOBJECT_H

#include "map2/mapstructs.h"

#include <QList>
#include <QRectF>
#include <QVariant>

namespace Map2
{
class MapLayer;
class MapGroup;
class MapHelper;

class MapObject
{
public:
	enum Type {
		MO_Vector,
		MO_Line,
		MO_Zone,
		MO_Text,
		MO_Commline,
		MO_Sector
	};

	MapObject(Map2::MapObject::Type t, Map2::MapLayer *layer = 0);
	virtual ~MapObject();

	void remove();

	void centerOnObject() const;

	CoordPlane coordinatePlane() const;
	virtual Coord coordinateGeo() const {return Coord();}

	virtual void moveBy(double dxPlane, double dyPlane) = 0;

	void bringToFront();

	Type type() const { return mType; }
	QString typeName()const;

	MapLayer* mapLayer() const { return pLayer; }

	QString name() const { return mName; }
	virtual void setName(QString name);

	/*!
	 * \brief Функция проверяет, является ли объект карты с дескриптором hObj частю текущего объекта.
	 */
	bool containsObject(HOBJ hObj);

	virtual QRectF sizePix() const { return QRectF(); }

	void setParameter(QString parameter, QVariant value);
	QVariant parameter(QString parameter) const;

	void setSelected(bool b = true);
	bool selected() const { return mSelected; }

	void setHidden(bool hidden);
	bool isHiden() const { return mHidden; }
	void hide();
	void show();

	Map2::MapGroup * group() const { return pGroup; }

	friend class MapLayer;
	friend class MapGroup;

private:
	void setMapLayer(MapLayer *layer);
	void setGroup(Map2::MapGroup *group);

	QVariantHash mParameters; //!< Дополнительные параметры объекта

protected:
	/*!
	 * \brief Уведомляет родительский слой об изменении объекта и вызывает функцию записи изменений в карте.
	 */
	void commit();

	Map2::MapHelper * helper() const;

	/*!
	 * \brief Очищает дескрипторы составных частей объекта. (Но не удаляет их с карты).
	 */
	void clearHandles();

	void removeFromMap();

	virtual QList<HOBJ*> mapHandles() {return QList<HOBJ*>();}

	void refresh();

	/*!
	 * \brief Функция используется для того, чтобы пересоздать объект.
	 */
	virtual void repaint() {}

	Type mType;
	QString mName;
	MapLayer *pLayer;

	bool mHidden;
	bool mSelected;

	MapGroup *pGroup;
};
}

Q_DECLARE_METATYPE(Map2::MapObject::Type)

#endif // MAPOBJECT_H
