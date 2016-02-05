#include "objects/maptextobject.h"
#include "maphelper.h"
#include "maplayer.h"
#include "mapview.h"

#include "gis.h"

#include <QColor>
#include <QTextCodec>

using namespace Map2;

MapTextObject::MapTextObject(Map2::MapLayer *layer, QString text, Map2::CoordPlane coord, int fontHeightMm, QColor color)
	: MapObject(MO_Text, layer), mText(text), mCoord(coord), mFontHeightMm(fontHeightMm), mColor(color)
{
	mapRegisterDrawObject(handle(), 0, LOCAL_TITLE);
	updateDraw();
	mapAppendPointPlane(handle(), coord.x, coord.y);
	commit();

	if(!text.isEmpty())
	{
		setText(text);
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

	mapPutText(handle(), tc->fromUnicode(mText).constData(), 0);
	mapPutTextHorizontalAlign(handle(), FA_LEFT | FA_TOP, 0);
	commit();
}

void MapTextObject::setCoordinate(const Map2::CoordPlane &coord)
{
	mCoord = coord;

	mapUpdatePointPlane(handle(), coord.x, coord.y, 1);
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
	Q_ASSERT(mapLayer());

	Map2::MapHelper *helper = mapLayer()->mapView()->helper();

	int mkmLength = mapGetTextLengthMkm(handle(), 0);
	int mkmHeight = mFontHeightMm * 1000 * (1 + mText.count("\n"));

	QRectF rect;
	rect.setWidth( helper->mkm2pix(mkmLength) );
	rect.setHeight( helper->mkm2pix(mkmHeight) );

	return rect;
}

void MapTextObject::updateDraw()
{
	mapClearDraw(handle());

	IMGTRUETEXT trueText;
	trueText.Text.Color = RGB(mColor.red(), mColor.green(), mColor.blue());
	trueText.Text.BkgndColor = IMGC_TRANSPARENT;
	trueText.Text.Outline = 0;
	trueText.Text.ShadowColor = IMGC_TRANSPARENT;
	trueText.Text.Height = mFontHeightMm* 1000; /// TODO: Добавить домножение на масштаб.
	trueText.Text.CharSet = RUSSIAN_CHARSET;
	trueText.Text.Italic = 0;
	trueText.Text.Underline = 0;

	mapAppendDraw(handle(), IMG_TRUETEXT, (char*)&trueText);
}
