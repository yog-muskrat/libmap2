#include "objects/maptextobject.h"
#include "maphelper.h"
#include "maplayer.h"
#include "mapview.h"

#include "gis.h"

#include <QColor>
#include <QTextCodec>

using namespace Map2;

MapTextObject::MapTextObject(QString text, Map2::Coord coord, int fontHeightMm, QColor color, MapLayer *layer)
	: MapObject(MO_Text, layer), mText(text), mCoord(coord), mFontHeightMm(fontHeightMm), mColor(color), hObj(0)
{
	if(layer)
	{
		hObj = mapCreateSiteObject(mapLayer()->mapHandle(), mapLayer()->siteHandle());
		mapRegisterDrawObject(hObj, 0, LOCAL_TITLE);
		updateDraw();
		CoordPlane cp = helper()->geoToPlane(mCoord);
		mapAppendPointPlane(hObj, cp.x, cp.y);
		setText(text);
		show();
	}
}

QString MapTextObject::text() const
{
	return mText;
}

void MapTextObject::setText(const QString &text)
{
	mText = text;

	QTextCodec *tc = QTextCodec::codecForName("koi8-r");

	mapPutText(hObj, tc->fromUnicode(mText).constData(), 0);
	mapPutTextHorizontalAlign(hObj, FA_LEFT | FA_TOP, 0);
	commit();
}

void MapTextObject::setCoordinatePlane(const Map2::CoordPlane &coord)
{
	if(!helper())
	{
		return;
	}

	setCoordinateGeo( helper()->planeToGeo(coord));
}

void MapTextObject::setCoordinateGeo(const Coord &coord)
{
	mCoord = coord;

	if(!helper())
	{
		return;
	}

	CoordPlane cp = helper()->geoToPlane(coord);

	mapUpdatePointPlane(hObj, cp.x, cp.y, 1);
	commit();
}

void MapTextObject::setColor(const QColor &value)
{
	mColor = value;
	updateDraw();
	commit();
}

void MapTextObject::setFontHeightMm(int value)
{
	mFontHeightMm = value;
	updateDraw();
	commit();
}

QRectF MapTextObject::sizePix() const
{
	if(!mapLayer())
	{
		return QRectF();
	}

	Map2::MapHelper *helper = mapLayer()->mapView()->helper();

	int mkmLength = mapGetTextLengthMkm(hObj, 0);
	int mkmHeight = mFontHeightMm * 1000 * (1 + mText.count("\n"));

	QRectF rect;
	rect.setWidth( helper->mkm2px(mkmLength) );
	rect.setHeight( helper->mkm2px(mkmHeight) );

	return rect;
}

void MapTextObject::repaint()
{
	if(!mapLayer())
	{
		return;
	}

	removeFromMap();

	hObj = mapCreateSiteObject(mapLayer()->mapHandle(), mapLayer()->siteHandle());
	mapRegisterDrawObject(hObj, 0, LOCAL_TITLE);
	updateDraw();
	CoordPlane cp = helper()->geoToPlane(mCoord);
	mapAppendPointPlane(hObj, cp.x, cp.y);
	commit();

	if(!mText.isEmpty())
	{
		setText(mText);
	}
}

void MapTextObject::updateDraw()
{
	mapClearDraw(hObj);

	IMGTRUETEXT trueText;
	trueText.Text.Color = RGB(mColor.red(), mColor.green(), mColor.blue());
	trueText.Text.BkgndColor = IMGC_TRANSPARENT;
	trueText.Text.Outline = 0;
	trueText.Text.ShadowColor = IMGC_TRANSPARENT;
	trueText.Text.Height = mFontHeightMm* 1000; /// TODO: Добавить домножение на масштаб.
	trueText.Text.CharSet = RUSSIAN_CHARSET;
	trueText.Text.Italic = 0;
	trueText.Text.Underline = 0;

	mapAppendDraw(hObj, IMG_TRUETEXT, (char*)&trueText);
}

void Map2::MapTextObject::moveBy(double dxPlane, double dyPlane)
{
	if(!helper())
	{
		return;
	}

	CoordPlane cp = helper()->geoToPlane(mCoord);

	cp += CoordPlane(dxPlane, dyPlane);

	setCoordinatePlane(cp);
}

QList<HOBJ *> Map2::MapTextObject::mapHandles()
{
	return QList<HOBJ*>() << &hObj;
}
