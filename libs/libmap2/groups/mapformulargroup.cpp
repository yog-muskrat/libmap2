#include "groups/mapformulargroup.h"
#include "objects/mapvectorobject.h"
#include "objects/maptextobject.h"
#include "maplayer.h"
#include "maphelper.h"
#include "mapview.h"
#include "rscviewer.h"
#include "gis.h"

#include <QRect>
#include <QDebug>
#include <QTextCodec>

Map2::MapFormularGroup::MapFormularGroup(Map2::MapVectorObject *parent, QColor borderColor) :
	Map2::MapGroup(parent),
	mBorderWidthPx(2),
	mPaddingPx(10),
	mSpacingPx(10),
	mBorderColor(borderColor),
	rectHobj(0),
	strutHobj(0)
{
}

Map2::MapFormularGroup::~MapFormularGroup()
{
	if(rectHobj > 0)
	{
		mapDeleteObject(rectHobj);
		mapClearObject(rectHobj);
		mapDeleteObject(strutHobj);
		mapClearObject(strutHobj);
	}

	restoreInitialChildrenCoordinates();
}

bool Map2::MapFormularGroup::addChild(Map2::MapObject *child)
{
	if(child->type() != MapObject::MO_Vector)
	{
		return false;
	}

	if(!MapGroup::addChild(child))
	{
		return false;
	}

	mInitialCoordinates[child] = child->coordinateGeo();

	updateChildrenDisplayCoordinates();

	return true;
}

void Map2::MapFormularGroup::setChildrenVisible(bool visible)
{
	Q_ASSERT(parent());

	mChildrenVisible = visible;

	HMAP hMap = parent()->mapLayer()->mapHandle();
	HSITE hSite = parent()->mapLayer()->siteHandle();
	HSELECT hSelect = parent()->mapLayer()->selectHandle();

	Map2::MapHelper *helper = parent()->mapLayer()->mapView()->helper();

	qDebug()<<"Toggling coordinage at"<<formularCoordinate().toString();

	if(visible)
	{
		helper->addObjectToSelection(hSelect, rectHobj);
		helper->addObjectToSelection(hSelect, strutHobj);
	}
	else
	{
		helper->removeObjectFromSelection(hSelect, rectHobj);
		helper->removeObjectFromSelection(hSelect, strutHobj);
	}

	mapSetSiteViewSelect(hMap, hSite, hSelect);

	foreach(Map2::MapObject *obj, mChildren)
	{
		obj->setHidden(!visible);
	}
}

void Map2::MapFormularGroup::updateChildrenDisplayCoordinates()
{
	arrangeChildren();
	updateBorderCoords();

//	qDebug() << "Updating children position for "<<parent()->name()<<mFormularCoord.toString();

	if(mFormularCoord.isValid())
	{
		setFormularCoordinate(mFormularCoord);
	}
	else
	{
		MapHelper *helper = parent()->mapLayer()->mapView()->helper();

		QPoint p = helper->geoToPicture( parent()->coordinateGeo() );
		p += QPoint(100, 50);
		setFormularCoordinate( helper->pictureToGeo(p));
	}
}

void Map2::MapFormularGroup::restoreInitialChildrenCoordinates()
{
	MapVectorObject *parentObj = vectorParent();
	Q_ASSERT(parentObj);

	foreach(Map2::MapObject *obj, mChildren)
	{
		MapVectorObject *mvo = dynamic_cast<MapVectorObject*>(obj);

		Q_ASSERT(mvo && mInitialCoordinates.contains(mvo));

		mvo->setCoordinates( mInitialCoordinates[mvo] );
		if(mObjectsLabels.contains(mvo))
		{
			mvo->setNameVisible(true);
			HOBJ hobj = mObjectsLabels.take(mvo);
			mvo->removeExtraHobj(hobj);
			mapDeleteObject(hobj);
			mapFreeObject(hobj);
		}
	}

	mFormularCoord = Coord();
}

void Map2::MapFormularGroup::arrangeChildren()
{
	MapVectorObject *parentObj = vectorParent();
	Q_ASSERT(parentObj);

	Map2::MapHelper *helper = pParent->mapLayer()->mapView()->helper();

	double scale = parentObj->mapLayer()->mapView()->scaleRatio();
	if(scale > 1)
	{
		scale = 1;
	}

	double padding = mPaddingPx * scale;
	double spacing = mSpacingPx * scale;

	QPoint origin = helper->planeToPicture(parentObj->coordinatePlane()) + QPoint(padding, -padding);

	QRect rect = QRect( origin.x() - padding, origin.y() + padding, 0, 0 );

	foreach(Map2::MapObject *child, mChildren)
	{
		MapVectorObject *mvo = dynamic_cast<MapVectorObject*>(child);
		Q_ASSERT(mvo);

		HOBJ textHobj = 0;

		if(!mObjectsLabels.contains(mvo))
		{
			textHobj = createText(mvo->mapLayer(), mvo->coordinateGeo(), mvo->name());
			mvo->setNameVisible(false);
			mvo->addExtraHobj(textHobj);
			mObjectsLabels[mvo] = textHobj;
		}

		textHobj = mObjectsLabels[mvo];

		QRectF childRect = mvo->sizePix();
		QRectF lblRect = textRect(textHobj);

		QPoint childPos = origin;
		childPos.rx() += (childRect.x() + (childRect.width() - childRect.x()))* scale;
		childPos.ry() -= (childRect.height() - childRect.y()) * scale;

		Map2::CoordPlane childCoord = helper->pictureToPlane(childPos);
		mvo->setCoordinates(childCoord);
		mvo->setRotationUse(false);

		QPoint lblPos = origin;
		lblPos.rx() += spacing + (childRect.width() + (childRect.width() - childRect.x()))* scale;
		lblPos.ry() -= childRect.height()*scale - childRect.y()*scale;

		Map2::CoordPlane lblCoord = helper->pictureToPlane(lblPos);
		mapUpdatePointPlane(textHobj, lblCoord.x, lblCoord.y, 1);
		mapCommitObject(textHobj);

		origin.ry() -= spacing + childRect.height()*scale;

		if( rect.width() > ((childRect.width() + lblRect.width())*scale + 2 * padding + spacing) )
		{
			rect.setTopLeft( QPoint(rect.x(), origin.y() - padding) );
		}
		else
		{
			rect.setTopRight( QPoint(rect.x() + 2 * padding + spacing + (childRect.width() + lblRect.width()) * scale, origin.y() - padding - childRect.y() * scale) );
		}
	}

	mBottomLeft = helper->pictureToPlane(rect.bottomLeft());
	mBottomRight = helper->pictureToPlane(rect.bottomRight());
	mTopLeft = helper->pictureToPlane(rect.topLeft());
	mTopRight = helper->pictureToPlane(rect.topRight());
}

void Map2::MapFormularGroup::updateBorderCoords()
{
	MapVectorObject *parentObj = vectorParent();
	Q_ASSERT(parentObj);

	if(rectHobj == 0)
	{
		createBorderObject();
	}

	QList<Map2::CoordPlane> coords;
	coords << mTopLeft;
	coords << mTopRight;
	coords << mBottomRight;
	coords << mBottomLeft;
	coords << coords.first();

	for(int i = 0; i < coords.count(); ++i)
	{
		mapUpdatePointPlane(rectHobj, coords[i].x, coords[i].y, i+1);
	}

	mapCommitObject(rectHobj);

	updateStrutCoords();
}

void Map2::MapFormularGroup::updateStrutCoords()
{
	CoordPlane pointA = parent()->coordinatePlane();
	CoordPlane pointB;

	Qt::Alignment align = formularAlignment();

	if(align.testFlag( Qt::AlignTop) && align.testFlag( Qt::AlignLeft))
	{
		pointB = mBottomRight;
	}
	else if(align.testFlag( Qt::AlignTop) && align.testFlag( Qt::AlignRight))
	{
		pointB = mBottomLeft;
	}
	else if(align.testFlag( Qt::AlignBottom) && align.testFlag( Qt::AlignLeft))
	{
		pointB = mTopRight;
	}
	else if(align.testFlag( Qt::AlignBottom) && align.testFlag( Qt::AlignRight))
	{
		pointB = mTopLeft;
	}
	else
	{
		return;
	}

	mapUpdatePointPlane(strutHobj, pointA.x, pointA.y, 1);
	mapUpdatePointPlane(strutHobj, pointB.x, pointB.y, 2);

	mapCommitObject(strutHobj);
}

void Map2::MapFormularGroup::createBorderObject()
{
	Map2::MapHelper *helper = pParent->mapLayer()->mapView()->helper();

	IMGLINE lineParm;
	memset(&lineParm, 0x0, sizeof(IMGLINE));
	lineParm.Thick = helper->px2mkm( mBorderWidthPx );
	lineParm.Color = RGB(mBorderColor.red(), mBorderColor.green(), mBorderColor.blue());

	IMGPOLYGONGLASS polygonParm;
	memset(&polygonParm, 0x0, sizeof(IMGPOLYGONGLASS));
	polygonParm.Color = RGB(255,255,255);
	polygonParm.Bright = 0;
	polygonParm.Contrast = 0;
	polygonParm.Transparency = 90;

	HMAP hMap = pParent->mapLayer()->mapHandle();

	rectHobj = mapCreateSiteObject(hMap, pParent->mapLayer()->siteHandle());
	mapAppendDraw(rectHobj, IMG_POLYGONGLASS, (char*)&polygonParm);
	mapAppendDraw(rectHobj, IMG_LINE, (char*)&lineParm);

	for(int i = 0; i < 5; ++i)
	{
		mapAppendPointGeo(rectHobj, 0, 0);
	}

	strutHobj = mapCreateSiteObject(hMap, pParent->mapLayer()->siteHandle());
	mapAppendDraw(strutHobj, IMG_LINE, (char*)&lineParm);
	mapAppendPointGeo(strutHobj, 0, 0);
	mapAppendPointGeo(strutHobj, 0, 0);

	if(childrenVisible())
	{
		mapCommitObject(rectHobj);
		mapCommitObject(strutHobj);

		HSELECT hSelect = parent()->mapLayer()->selectHandle();

		helper->addObjectToSelection(hSelect, rectHobj);
		helper->addObjectToSelection(hSelect, strutHobj);

		HMAP hMap = parent()->mapLayer()->mapHandle();
		HSITE hSite = parent()->mapLayer()->siteHandle();

		mapSetSiteViewSelect(hMap, hSite, hSelect);
	}
}

Map2::MapVectorObject *Map2::MapFormularGroup::vectorParent()
{
	MapVectorObject *parentObj = dynamic_cast<MapVectorObject*>(parent());
	if(!parentObj)
	{
		return 0;
	}

	return parentObj;
}

HOBJ Map2::MapFormularGroup::createText(Map2::MapLayer *layer, Map2::Coord coordinate, const QString &text)
{
	double ratio = layer->mapView()->scaleRatio();
	if(ratio > 1)
	{
		ratio = 1;
	}

	HOBJ hobj = mapCreateSiteObject(layer->mapHandle(), layer->siteHandle(), IDDOUBLE2, 1);

	mapRegisterDrawObject(hobj, 0, LOCAL_TITLE);
	IMGTRUETEXT trueText;
	memset(&trueText, 0x0, sizeof(IMGTRUETEXT));
	trueText.Text.Color = RGB(mBorderColor.red(), mBorderColor.green(), mBorderColor.blue());
	trueText.Text.BkgndColor = IMGC_TRANSPARENT;
	trueText.Text.ShadowColor = IMGC_TRANSPARENT;
	trueText.Text.Height = 4 * 1000 * ratio;
	trueText.Text.CharSet = RUSSIAN_CHARSET;
	trueText.Text.Horizontal = 1;

	CoordPlane cp = layer->mapView()->helper()->geoToPlane( coordinate );

	mapAppendDraw(hobj, IMG_TRUETEXT, (char*)&trueText);
	mapAppendPointPlane(hobj, cp.x, cp.y);

	QTextCodec *tc = Map2::RscViewer::codec();

	mapPutText(hobj, tc->fromUnicode(text).constData(), 0);
	mapPutTextHorizontalAlign(hobj, FA_LEFT, 0);
	mapPutTextVerticalAlign(hobj, FA_MIDDLE, 0);

	mapCommitObject(hobj);

	return hobj;
}

QRectF Map2::MapFormularGroup::textRect(HOBJ hobj) const
{
	Map2::MapHelper *helper = parent()->mapLayer()->mapView()->helper();

	int mkmLength = mapGetTextLengthMkm(hobj, 0);
	int mkmHeight = 4 * 1000;

	QRectF rect;
	rect.setWidth( helper->mkm2px(mkmLength) );
	rect.setHeight( helper->mkm2px(mkmHeight) );

	return rect;
}

void Map2::MapFormularGroup::setSpacingPx(double value)
{
	mSpacingPx = value;
	updateChildrenDisplayCoordinates();
}

Qt::Alignment Map2::MapFormularGroup::formularAlignment() const
{
	MapHelper *helper = parent()->mapLayer()->mapView()->helper();
	CoordPlane parentCoord = parent()->coordinatePlane();
	CoordPlane formularCoord = helper->geoToPlane( formularCoordinate() );

	Qt::Alignment align;

	if(formularCoord.x < parentCoord.x)
	{
		align |= Qt::AlignBottom;
	}
	else
	{
		align |= Qt::AlignTop;
	}

	if(formularCoord.y < parentCoord.y)
	{
		align |= Qt::AlignLeft;
	}
	else
	{
		align |= Qt::AlignRight;
	}

	return align;
}

Map2::Coord Map2::MapFormularGroup::formularCoordinate() const
{
//	Coord c;

//	if(mBottomLeft == CoordPlane(0,0) && mTopRight == CoordPlane(0,0))
//	{
//		c = Coord();
//	}
//	else
//	{
//		MapHelper *helper = parent()->mapLayer()->mapView()->helper();
//		c = helper->planeToGeo( CoordPlane(mBottomLeft.x + (mTopLeft.x - mBottomLeft.x)/2, mBottomLeft.y + (mBottomRight.y - mBottomLeft.y)/2) );
//	}

	return mFormularCoord;
}

void Map2::MapFormularGroup::setFormularCoordinate(Map2::Coord coord)
{
	Map2::MapHelper *helper = parent()->mapLayer()->mapView()->helper();

	QPoint newCoord = helper->geoToPicture( coord );
	QPoint oldCoord = helper->geoToPicture( formularCoordinate() );
	moveBy( newCoord - oldCoord );
}

void Map2::MapFormularGroup::setPaddingPx(double value)
{
	mPaddingPx = value;
	updateChildrenDisplayCoordinates();
}

void Map2::MapFormularGroup::setBorderWidthPx(double value)
{
	mBorderWidthPx = value;

	if(rectHobj > 0)
	{
		mapDeleteObject(rectHobj);
		mapDeleteObject(strutHobj);
		mapFreeObject(rectHobj);
		mapFreeObject(strutHobj);
		rectHobj = 0;
		strutHobj = 0;
	}

	createBorderObject();
}

void Map2::MapFormularGroup::moveBy(const QPoint &offset)
{
	Map2::MapHelper *helper = parent()->mapLayer()->mapView()->helper();

	CoordPlane oldCoord = helper->geoToPlane( formularCoordinate() );
	QPoint oldPoint = helper->planeToPicture(oldCoord);

	CoordPlane newCoord = helper->pictureToPlane( oldPoint + offset);

	DOUBLEPOINT dp;
	dp.x = newCoord.x - oldCoord.x;
	dp.y = newCoord.y - oldCoord.y;

	CoordPlane delta(dp.x, dp.y);

	mBottomLeft += delta;
	mBottomRight += delta;
	mTopLeft += delta;
	mTopRight += delta;

	foreach(MapObject*obj, mChildren)
	{
		obj->moveBy(dp.x, dp.y);

		mapRelocateObjectPlane(mObjectsLabels[obj], &dp);
		mapCommitObject(mObjectsLabels[obj]);
	}

	mFormularCoord = helper->planeToGeo(newCoord);
//	qDebug() << "move mFormularCoord for"<<parent()->name()<<mFormularCoord.toString();

	updateBorderCoords();
}
