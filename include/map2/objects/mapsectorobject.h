#ifndef MAPSECTOROBJECT_H
#define MAPSECTOROBJECT_H

#include "map2/objects/mapobject.h"
#include "map2/mapstructs.h"

#include <QColor>
#include <QPolygonF>

namespace Map2
{
class MapSectorObject : public MapObject
{
public:
	enum Style
	{
		NoSides = 0x0001,		/// Стороны сектора не рисуются
		SidesRsc = 0x0002,		/// Стороны рисуются знаком из классификатора
		SidesColor = 0x0004,	/// Стороны рисуются цветной линией
		NoArc = 0x0010,			/// Дуга не рисуется
		ArcRsc = 0x0020,		/// Дуга рисуется знаком из классификатора
		ArcColor = 0x0040		/// Дуга рисуется цветной линией
	};
	Q_DECLARE_FLAGS(SectorStyle, Style)

	MapSectorObject(Map2::Coord centerOnObject, qreal radius = 1000, qreal azimuth = 0, qreal angle = 360, Map2::MapLayer *layer = 0);
	~MapSectorObject();

	Map2::Coord center() const {return mCenter;}
	void setCenter(const Map2::Coord &value);
	void setCenter(const Map2::CoordPlane &value);

	qreal radius() const { return mRadius; }
	void setRadius(const qreal &meters);

	qreal azimuth() const { return mAzimuth; }
	void setAzimuth(const qreal &value);

	qreal angle() const { return mAngle;}
	void setAngle(qreal value);
	void setAngle(qreal from, qreal to);

	Map2::MapSectorObject::SectorStyle style() const { return mStyle; }
	void setStyle(const Map2::MapSectorObject::SectorStyle &value);

	void setColor(QColor color);
	void setSidesColor(QColor color);
	void setArcColor(QColor color);

	QColor sidesColor() const {return mSidesColor;}
	QColor arcColor() const {return mArcColor;}

	void setWidth(qreal width);
	void setSidesWidth(qreal width);
	void setArcWidth(qreal width);

	qreal sidesWidth() const {return mSidesWidth;}
	qreal arcWidth() const {return mArcWidth;}

	void setRscKey(QString rscKey);
	void setSidesRscKey(QString rscKey);
	void setArcRscKey(QString rscKey);

	QString sidesRscKey() const {return mSidesRscKey;}
	QString arcRsckey() const {return mArcRscKey;}

private:
	QPolygonF getArcPolygon() const;
	QPolygonF getSidesPolygon() const;

	void updateSides() const;
	void updateArc() const;

	void appendDraw(HMAP handle, QColor color, qreal width) const;
	void registerObject(HMAP handle, QString rscKey) const;

	Coord mCenter;
	qreal mRadius;
	qreal mAzimuth;
	qreal mAngle;

	SectorStyle mStyle;

	QColor mSidesColor;
	QColor mArcColor;

	qreal mSidesWidth;
	qreal mArcWidth;

	QString mSidesRscKey;
	QString mArcRscKey;

	HMAP hSides;
	HMAP hArc;

	bool mUpdateObjects; // Признак того, что нужно пересоздать объекты (если измененяется не только метрика)

	// MapObject interface
public:
	virtual Map2::Coord coordinateGeo() const { return mCenter; }
	virtual void moveBy(double dxPlane, double dyPlane);
	virtual QRectF sizePix() const;

protected:
	virtual void repaint();
	virtual QList<HOBJ*> mapHandles();
};
}

Q_DECLARE_OPERATORS_FOR_FLAGS(Map2::MapSectorObject::SectorStyle)

#endif // MAPSECTOROBJECT_H
