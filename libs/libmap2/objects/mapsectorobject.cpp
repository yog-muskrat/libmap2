#include "objects/mapsectorobject.h"

#include "maplayer.h"
#include "mapview.h"
#include "maphelper.h"

#include "gis.h"

#include <QLineF>
#include <QDebug>
#include <qmath.h>

Map2::MapSectorObject::MapSectorObject(Map2::Coord center, qreal radius, qreal azimuth, qreal angle, Map2::MapLayer *layer) :
	Map2::MapObject( MO_Sector, layer),
	mCenter(center),
	mRadius(radius),
	mAzimuth(azimuth),
	mAngle(angle),
	mStyle( SidesRsc | ArcRsc),
	mSidesColor(Qt::black),
	mArcColor(Qt::black),
	mSidesWidth(3),
	mArcWidth(3),
	mSidesRsc(0),
	mArcRsc(0),
	hArc(0),
	mUpdateObjects(true)
{
	redraw();
}

Map2::MapSectorObject::~MapSectorObject()
{
	if(hArc > 0)
	{
		mapFreeObject(hArc);
	}
}

void Map2::MapSectorObject::setAngle(qreal value)
{
	value = fmod(value, 360);
	if(mAngle == value)
	{
		return;
	}

	mAngle = value;
	redraw();
}

void Map2::MapSectorObject::setAngle(qreal from, qreal to)
{
	if(from > to)
	{
		to += 360.;
	}

	mAzimuth = from + (to - from)/2;
	mAzimuth = fmod(mAzimuth, 360.);

	mAngle = to - from;
	mAngle = fmod(mAngle, 360.);

	redraw();
}

void Map2::MapSectorObject::setStyle(const Map2::MapSectorObject::SectorStyle &value)
{
	if(mStyle == value)
	{
		return;
	}

	mStyle = value;

	mUpdateObjects = true;
	redraw();
}

void Map2::MapSectorObject::setColor(QColor color)
{
	if(mSidesColor == color && mArcColor == color)
	{
		return;
	}

	mSidesColor = color;
	mArcColor = color;

	// Вызвать обновление, только если части сектора выводятся с использованием цвета
	if(mStyle.testFlag(SidesColor) || mStyle.testFlag(ArcColor))
	{
		mUpdateObjects = true;
		redraw();
	}
}

void Map2::MapSectorObject::setSidesColor(QColor color)
{
	if(mSidesColor == color)
	{
		return;
	}

	mSidesColor = color;
	if(mStyle.testFlag(SidesColor))
	{
		mUpdateObjects = true;
		redraw();
	}
}

void Map2::MapSectorObject::setArcColor(QColor color)
{
	if(mArcColor == color)
	{
		return;
	}

	mArcColor = color;

	if(mStyle.testFlag(ArcColor))
	{
		mUpdateObjects = true;
		redraw();
	}
}

void Map2::MapSectorObject::setWidth(qreal width)
{
	if(mSidesWidth == width && mArcWidth == width)
	{
		return;
	}

	mSidesWidth = width;
	mArcWidth = width;

	if(mStyle.testFlag(SidesColor) || mStyle.testFlag(ArcColor))
	{
		mUpdateObjects = true;
		redraw();
	}
}

void Map2::MapSectorObject::setSidesWidth(qreal width)
{
	if(mSidesWidth == width)
	{
		return;
	}

	mSidesWidth = width;

	if(mStyle.testFlag(SidesColor))
	{
		mUpdateObjects = true;
		redraw();
	}
}

void Map2::MapSectorObject::setArcWidth(qreal width)
{
	if(mArcWidth == width)
	{
		return;
	}

	mArcWidth = width;

	if(mStyle.testFlag(ArcColor))
	{
		mUpdateObjects = true;
		redraw();
	}
}

void Map2::MapSectorObject::setRscCode(long rscCode)
{
	if(mSidesRsc== rscCode && mArcRsc == rscCode)
	{
		return;
	}

	mSidesRsc = rscCode;
	mArcRsc = rscCode;

	if(mStyle.testFlag(SidesRsc) || mStyle.testFlag(ArcRsc))
	{
		mUpdateObjects = true;
		redraw();
	}
}

void Map2::MapSectorObject::setSidesCode(long rscCode)
{
	if(mSidesRsc== rscCode)
	{
		return;
	}

	mSidesRsc = rscCode;

	if(mStyle.testFlag(SidesRsc))
	{
		mUpdateObjects = true;
		redraw();
	}
}

void Map2::MapSectorObject::setArcCode(long rscCode)
{
	if(mArcRsc == rscCode)
	{
		return;
	}

	mArcRsc = rscCode;

	if(mStyle.testFlag(ArcRsc))
	{
		mUpdateObjects = true;
		redraw();
	}
}

void Map2::MapSectorObject::setAzimuth(const qreal &value)
{
	mAzimuth = fmod(value, 360);
	redraw();
}

void Map2::MapSectorObject::setRadius(const qreal &meters)
{
	mRadius = meters;
	redraw();
}

void Map2::MapSectorObject::setCenter(const Map2::Coord &value)
{
	mCenter = value;
	redraw();
}

void Map2::MapSectorObject::redraw()
{
	if(!mapLayer())
	{
		return;
	}

	clearMetrics();

	if(mUpdateObjects)
	{
		clearObjects();

		if(!hArc)
		{
			hArc = mapCreateSiteObject( mapLayer()->mapHandle(), mapLayer()->siteHandle());
		}

		updateObjectsStyles();
		mUpdateObjects = false;
	}

	QPolygonF sidesPoints = getSidesPolygon();
	QPolygonF arcPoints = getArcPolygon();

	foreach(const QPointF &p, sidesPoints)
	{
		mapAppendPointPlane(handle(), p.x(), p.y());
	}

	foreach(const QPointF &p, arcPoints)
	{
		mapAppendPointPlane(hArc, p.x(), p.y());
	}

	mapCommitObject(hArc);
	commit();
}

QPolygonF Map2::MapSectorObject::getArcPolygon() const
{
	if(style().testFlag(NoArc))
	{
		return QPolygonF();
	}

	Q_ASSERT(mapLayer());
	Map2::MapHelper *helper = mapLayer()->mapView()->helper();

	QPointF center = helper->geoToPlane(mCenter).toPointF();

	qreal lineAngle = -(azimuth() + angle()/2.);

	QLineF line(center, center+QPointF(1,1));
	line.setLength(mRadius);
	line.setAngle( lineAngle );

	QPolygonF result;

	for(qreal i = angle(); i > 0; --i)
	{
		line.setAngle( lineAngle + i);
		result << line.p2();
	}

	line.setAngle( -(azimuth() + angle()/2.) );

	result << line.p2();

	return result;
}

QPolygonF Map2::MapSectorObject::getSidesPolygon() const
{
	if(angle() == 360 || style().testFlag(NoSides))
	{
		// Не рисовать радиус, если сектор представляет собой окружность.
		return QPolygonF();
	}

	// Т.к. градусы считаются в противоположные стороны. нужно преобразовать азимут к кутишному виду

	Q_ASSERT(mapLayer());
	Map2::MapHelper *helper = mapLayer()->mapView()->helper();


	QPointF center = helper->geoToPlane(mCenter).toPointF();

	QLineF left(center, center+QPointF(1,1));
	QLineF right(center, center+QPointF(1,1));

	left.setLength(mRadius);
	right.setLength(mRadius);

	left.setAngle( -azimuth() - angle()/2.);
	right.setAngle( -azimuth() + angle()/2);

	QPolygonF result;
	result << left.p2() << left.p1() << right.p2();

	return result;
}

void Map2::MapSectorObject::clearObjects()
{
	Q_ASSERT(mapLayer());

	///TODO: Подумать, можно ли обойтись без пересоздания объекта
	mapDeleteObject(handle());
	mObjHandle = mapCreateSiteObject(mapLayer()->mapHandle(), mapLayer()->siteHandle());
	mMapKey = -1; // Обнулить ключ объекта, чтобы при следующем обращении он его заново вычитал с карты

	if(hArc)
	{
		mapDeleteObject(hArc);
		mapFreeObject(hArc);
		hArc = 0;
	}
}

void Map2::MapSectorObject::updateObjectsStyles() const
{
	updateSides();
	updateArc();
}

void Map2::MapSectorObject::updateSides() const
{
	if(style().testFlag(SidesColor))
	{
		appendDraw(handle(), mSidesColor, mSidesWidth);
	}
	else if(style().testFlag(SidesRsc))
	{
		registerObject(handle(), mSidesRsc);
	}
}

void Map2::MapSectorObject::updateArc() const
{
	if(style().testFlag(ArcColor))
	{
		appendDraw(hArc, mArcColor, mArcWidth);
	}
	else if(style().testFlag(ArcRsc))
	{
		registerObject(hArc, mArcRsc);
	}
}

void Map2::MapSectorObject::appendDraw(HMAP handle, QColor color, qreal width) const
{
	Q_ASSERT(mapLayer());
	Map2::MapHelper *helper = mapLayer()->mapView()->helper();

	IMGLINE parmLine;
	memset(&parmLine, 0x0, sizeof(IMGLINE));
	parmLine.Thick = (ulong)helper->px2mkm( width );
	parmLine.Color = RGB(color.red(), color.green(), color.blue());

	mapAppendDraw(handle, IMG_LINE, (char*)&parmLine);
}

void Map2::MapSectorObject::registerObject(HMAP handle, int rscKey) const
{
	mapRegisterObject(handle, rscKey, LOCAL_LINE);
}

void Map2::MapSectorObject::clearMetrics()
{
	for(int i = mapPointCount(handle(), 0); i > 0; --i)
	{
		mapDeletePointPlane(handle(), i);
	}

	if(hArc > 0)
	{
		for(int i = mapPointCount(hArc, 0); i > 0; --i)
		{
			mapDeletePointPlane(hArc, i);
		}
	}
}
