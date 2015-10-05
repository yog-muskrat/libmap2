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
	virtual CoordPlane coordinate() const;

	Type type() const {return mType;}
	QString typeName()const;
	HOBJ handle() const {return mObjHandle;}

	MapLayer* mapLayer() {return pLayer;}

	QString name() const {return mName;}
	void setName(QString name);

	void bindMetric(int metricNumber, MapObject *targetObject, int targetMetricNumber);
	void unbindMetric(int metricNumber);
	void unbindMetrics();

	void updateMetric(int metricNumber, CoordPlane coord);

	long mapIndex();

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
	void commit();

	Type mType;
	HOBJ mObjHandle;
	MapLayer *pLayer;
	QString mName;
	long mMapIndex; //!< Порядковый номер объекта в карте.
	bool mSelected;

	QMap<int, MetricBinding> mMetricsBindings; //!< Метрики текущего объекта, привязанные к другим объектам.
	QMultiMap<int, MetricBinding> mObjectsBindings; //!< Метрики других объектов, привязанные к текущему.
};

Q_DECLARE_METATYPE(MapObject::Type)

#endif // MAPOBJECT_H
