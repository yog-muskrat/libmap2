#include "objects/mapsectorobject.h"

#include "maplayer.h"
#include "mapview.h"
#include "maphelper.h"
#include "rscviewer.h"

#include "gis.h"

#include <QLineF>
#include <QDebug>
#include <qmath.h>
#include <QTextCodec>

using namespace Map2;

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
	hSides(0),
	hArc(0),
	mUpdateObjects(true)
{
	if(pLayer)
	{
		refresh();
	}
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
	refresh();
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

	refresh();
}

void Map2::MapSectorObject::setStyle(const Map2::MapSectorObject::SectorStyle &value)
{
	if(mStyle == value)
	{
		return;
	}

	mStyle = value;

	mUpdateObjects = true;
	refresh();
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
		refresh();
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
		refresh();
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
		refresh();
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
		refresh();
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
		refresh();
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
		refresh();
	}
}

void Map2::MapSectorObject::setRscKey(QString rscKey)
{
	if(mSidesRscKey== rscKey && mArcRscKey == rscKey)
	{
		return;
	}

	mSidesRscKey = rscKey;
	mArcRscKey = rscKey;

	if(mStyle.testFlag(SidesRsc) || mStyle.testFlag(ArcRsc))
	{
		mUpdateObjects = true;
		refresh();
	}
}

void Map2::MapSectorObject::setSidesRscKey(QString rscKey)
{
	if(mSidesRscKey== rscKey)
	{
		return;
	}

	mSidesRscKey = rscKey;

	if(mStyle.testFlag(SidesRsc))
	{
		mUpdateObjects = true;
		refresh();
	}
}

void Map2::MapSectorObject::setArcRscKey(QString rscKey)
{
	if(mArcRscKey == rscKey)
	{
		return;
	}

	mArcRscKey = rscKey;

	if(mStyle.testFlag(ArcRsc))
	{
		mUpdateObjects = true;
		refresh();
	}
}

void Map2::MapSectorObject::setAzimuth(const qreal &value)
{
	mAzimuth = fmod(value, 360);
	refresh();
}

void Map2::MapSectorObject::setRadius(const qreal &meters)
{
	mRadius = meters;
	refresh();
}

void Map2::MapSectorObject::setCenter(const Map2::Coord &value)
{
	mCenter = value;
	refresh();
}

void MapSectorObject::setCenter(const CoordPlane &value)
{
	if(!helper())
	{
		return;
	}

	setCenter( helper()->planeToGeo(value) );
}

void Map2::MapSectorObject::repaint()
{
	if(!mapLayer())
	{
		return;
	}

	helper()->clearMetrics(hSides);
	helper()->clearMetrics(hArc);

	if(mUpdateObjects)
	{
		removeFromMap();

		hSides = mapCreateSiteObject( mapLayer()->mapHandle(), mapLayer()->siteHandle());
		hArc = mapCreateSiteObject( mapLayer()->mapHandle(), mapLayer()->siteHandle());

		updateSides();
		updateArc();

		mUpdateObjects = false;
	}

	QPolygonF sidesPoints = getSidesPolygon();
	QPolygonF arcPoints = getArcPolygon();

	foreach(const QPointF &p, sidesPoints)
	{
		mapAppendPointPlane(hSides, p.x(), p.y());
	}

	foreach(const QPointF &p, arcPoints)
	{
		mapAppendPointPlane(hArc, p.x(), p.y());
	}

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

void Map2::MapSectorObject::updateSides() const
{
	if(style().testFlag(SidesColor))
	{
		appendDraw(hSides, mSidesColor, mSidesWidth);
	}
	else if(style().testFlag(SidesRsc))
	{
		registerObject(hSides, mSidesRscKey);
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
		registerObject(hArc, mArcRscKey);
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

void Map2::MapSectorObject::registerObject(HMAP handle, QString rscKey) const
{
	QTextCodec *tc = RscViewer::codec();
	mapRegisterObjectByKey(handle, tc->fromUnicode(rscKey).data());
}

void Map2::MapSectorObject::moveBy(double dxPlane, double dyPlane)
{
	if(!mapLayer())
	{
		return;
	}

	CoordPlane cp = coordinatePlane();

	cp += CoordPlane(dxPlane, dyPlane);

	setCenter( cp );
}

QRectF Map2::MapSectorObject::sizePix() const
{
	if(!mapLayer())
	{
		return QRectF();
	}

	return QRectF();
}

QList<HOBJ*> MapSectorObject::mapHandles()
{
	return QList<HOBJ*>() << &hSides << &hArc;
}
