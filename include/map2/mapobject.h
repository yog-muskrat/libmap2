#ifndef MAPOBJECT_H
#define MAPOBJECT_H

#include "structs.h"
#include "gis.h"

#include <QVariant>

class MapLayer;

class MapObject
{
public:
	enum Type
	{
		MO_Vector,
		MO_Line,
		MO_Zone
	};

	MapObject(Type t, MapLayer *layer = 0);
	~MapObject();

	/*!
	 * \brief Удаляет объект со слоя.
	 */
	void remove();

	/*!
	 * \brief Центрирует карту на объекте.
	 * В базовой реализации центром считается первая точка метрики объекта.
	 * В классах-наследниках эта функция может быть переописана для более правильного поведения.
	 */
	virtual void center();

	/*!
	 * \brief Возвращает координаты объекта.
	 * В базовой реализации возвращаются координаты первой точки метрики.
	 * В классах-наследниках эта функция может быть переописана для более правильного поведения.
	 */
	virtual CoordPlane coordinate() const;

	Type type() const {return mType;}
	QString typeName()const;
	HOBJ handle() const {return mObjHandle;}

	void setMapLayer(MapLayer *layer);
	MapLayer* mapLayer() {return pLayer;}

	QString name() const {return mName;}
	void setName(QString name);

protected:
	Type mType;
	HOBJ mObjHandle;
	MapLayer *pLayer;
	QString mName;
};

Q_DECLARE_METATYPE(MapObject::Type)

#endif // MAPOBJECT_H
