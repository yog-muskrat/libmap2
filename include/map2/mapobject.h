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
	virtual ~MapObject();

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
	 * \brief Устанавливает признак выделения объекта.
	 */
	virtual void setSelected(bool b = true);

	bool selected() const {return mSelected;}

	/*!
	 * \brief Возвращает координаты объекта.
	 * В базовой реализации возвращаются координаты первой точки метрики.
	 * В классах-наследниках эта функция может быть переописана для более правильного поведения.
	 */
	virtual CoordPlane coordinate();

	/*!
	 * \brief Смещает объект на указанную величину.
	 * \param dxPlane, dyPlane Величины смещения по осям X и Y в метрах.
	 */
	virtual void moveBy(double dxPlane, double dyPlane);

	Type type() const {return mType;}
	QString typeName()const;
	HOBJ handle() const {return mObjHandle;}

	MapLayer* mapLayer() {return pLayer;}

	QString name() const {return mName;}
	void setName(QString name);

	void bindMetric(int metricNumber, MapObject *targetObject, int targetMetricNumber);
	void unbindMetric(int metricNumber);
	void unbindMetrics();

	long mapKey();

	friend class MapLayer;

private:
	struct MetricBinding
	{
		MapObject *object;
		int metricNumber;

		MetricBinding(MapObject *mo = 0, int metric = 0) : object(mo), metricNumber(metric) {}
		bool operator == (const MetricBinding &other) const { return object == other.object && metricNumber == other.metricNumber;}
	};

	void setMapLayer(MapLayer *layer);

	void addMetricBinding(MetricBinding binding, int targetMetric);
	void removeMetricBinding(MetricBinding binding, int targetMetric);

	void removeFromMap();

protected:
	/*!
	 * \brief Обновляет метрику объекты и все связанные с ней метрики других объектов.
	 * \param metricNumber Номер обновляемой метрики (начинается с 1)
	 * \param coord Новые координаты обновляемой метрики в метрах.
	 */
	void updateMetric(int metricNumber, CoordPlane coord);

	/*!
	 * \brief Пердназначена для вызова объектом, на который "повязана" метрика текущего объекта.
	 */
	void updateBindedMetric(int metricNumber, CoordPlane coord);

	/*!
	 * \brief Сохраняет изменения в пользовательской карте и уведомляет родительский слой.
	 */
	void commit();

	Type mType;
	HOBJ mObjHandle;
	MapLayer *pLayer;
	QString mName;
	long mMapKey; //!< Порядковый номер объекта в карте.
	bool mSelected;

	QMap<int, MetricBinding> mMetricsBindings; //!< Метрики текущего объекта, привязанные к другим объектам.
	QMultiMap<int, MetricBinding> mObjectsBindings; //!< Метрики других объектов, привязанные к текущему.

	int tmp;
};

Q_DECLARE_METATYPE(MapObject::Type)

#endif // MAPOBJECT_H
