#include "groups/mapformulargroup.h"
#include "objects/mapvectorobject.h"
#include "objects/maptextobject.h"
#include "maplayer.h"
#include "maphelper.h"
#include "mapview.h"
#include "gis.h"

#include <QRect>
#include <QDebug>

Map2::MapFormularGroup::MapFormularGroup(Map2::MapVectorObject *parent, QColor borderColor) :
	Map2::MapGroup(parent),
	mBorderWidthPx(2),
	mPaddingPx(0),
	mSpacingPx(0),
	mOffset( QPoint(70, -35)),
	mBorderColor(borderColor),
	hObj(0)
{
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

	mInitialCoordinates[child] = child->coordinate();
	updateChildrenDisplayCoordinates();
	return true;
}

void Map2::MapFormularGroup::setChildrenVisible(bool visible)
{
	mChildrenVisible = visible;

	HSITE hSite = parent()->mapLayer()->siteHandle();
	HMAP hMap = parent()->mapLayer()->mapHandle();
	HSELECT hSelect = parent()->mapLayer()->selectHandle();
	int list = mapGetListNumber( hObj );
	int key = mapObjectKey(hObj);

	if(!visible)
	{
		mapInvertSample(hSelect);
		mapSelectSampleByList(hSelect, list, key);
		mapInvertSample(hSelect);
	}
	else
	{
		mapSelectSampleByList(hSelect, list, key);
	}

	mapSetSiteViewSelect(hMap, hSite, hSelect);

	foreach(Map2::MapObject *obj, mChildren)
	{
		if(visible)
		{
			obj->show();
			if(mObjectsLabels.contains(obj))
			{
				mObjectsLabels[obj]->show();
			}
		}
		else
		{
			obj->hide();
			if(mObjectsLabels.contains(obj))
			{
				mObjectsLabels[obj]->hide();
			}
		}
	}
}

void Map2::MapFormularGroup::updateChildrenDisplayCoordinates()
{
	MapVectorObject *parentObj = vectorParent();
	Q_ASSERT(parentObj);

	Map2::MapHelper *helper = pParent->mapLayer()->mapView()->helper();

	HMAP hMap = pParent->mapLayer()->mapHandle();

	QPoint origin = helper->planeToPicture(parentObj->coordinatesPlane()) + mOffset + QPoint(mPaddingPx, -mPaddingPx);

	QRectF frameRect( origin.x() - mPaddingPx, origin.y() + mPaddingPx, 0, 0 );

	///TODO: Это тут временно. Нужно перенести, скорее всего, в MapView.
	double scale = mapGetMapScale(hMap) / parentObj->mapLayer()->mapView()->scale();
	if(scale > 1)
	{
		scale = 1;
	}

	qDebug()<<"Form origin="<<origin<<"scale="<<scale;

	foreach(Map2::MapObject *child, mChildren)
	{
		MapVectorObject *mvo = dynamic_cast<MapVectorObject*>(child);
		Q_ASSERT(mvo);

		if(!mObjectsLabels.contains(mvo))
		{
			QString name = mvo->name();

			mObjectsLabels[mvo] = new MapTextObject(mvo->mapLayer(), name, mvo->coordinate());
			mvo->setName("");
		}

		MapTextObject *lblObj = mObjectsLabels[mvo];

		QRectF childRect = mvo->sizePix();
		QRectF lblRect = lblObj->sizePix();

		qDebug()<<"    FormChild "<<lblObj->text()<<"rect="<<childRect<<"label="<<lblRect;

		QPoint childPos = origin;
		childPos.rx() += (childRect.x() + (childRect.width() - childRect.x()))* scale;
		childPos.ry() -= (childRect.height() - childRect.y()) * scale;

		Map2::CoordPlane childCoord = helper->pictureToPlane(childPos);
		mvo->setCoordinates(childCoord);
		mvo->setRotation( 90 );

		QPoint lblPos = origin;
		lblPos.rx() += mSpacingPx + (childRect.width() + (childRect.width() - childRect.x()))* scale;
		lblPos.ry()-= childRect.height()*scale - childRect.y()*scale;

		Map2::CoordPlane lblCoord = helper->pictureToPlane(lblPos);
		lblObj->setCoordinate(lblCoord);

		origin.ry() -= mSpacingPx + childRect.height()*scale;

		if( frameRect.width() > ((childRect.width() + lblRect.width())*scale + 2 * mPaddingPx + mSpacingPx) )
		{
			frameRect.setTopLeft( QPointF(frameRect.x(), origin.y() + mPaddingPx) );
		}
		else
		{
			frameRect.setTopRight( QPointF(frameRect.x() + 2*mPaddingPx + mSpacingPx + (childRect.width() + lblRect.width())*scale, origin.y() + mPaddingPx) );
		}
	}

	updateBorderCoords(frameRect);
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
			mvo->setName( mObjectsLabels[mvo]->text() );
			MapObject *lblObj = mObjectsLabels.take(mvo);
			lblObj->remove();
		}
	}
}

void Map2::MapFormularGroup::updateBorderCoords(const QRectF newRect)
{
	MapVectorObject *parentObj = vectorParent();
	Q_ASSERT(parentObj);

	Map2::MapHelper *helper = pParent->mapLayer()->mapView()->helper();

	HMAP hMap = parentObj->mapLayer()->mapHandle();

	if(hObj == 0)
	{
		createBorderObject();
	}

	QList<QPointF> screenPoints;

	/// В зависимости от положения формуляра относительно родительского объекта
	if(mOffset.x() < 0 && mOffset.y() <= 0)
	{ // TOP-LEFT
		screenPoints << newRect.bottomRight() <<newRect.bottomLeft() <<newRect.topLeft() <<newRect.topRight() <<newRect.bottomRight();
	}
	else if(mOffset.x() >= 0 && mOffset.y() <= 0)
	{ // TOP-RIGHT
		screenPoints << newRect.bottomLeft() <<newRect.topLeft() <<newRect.topRight() <<newRect.bottomRight() <<newRect.bottomLeft();
	}
	else if(mOffset.x() < 0 && mOffset.y() > 0)
	{ // BOTTOM-LEFT
		screenPoints << newRect.topRight() << newRect.bottomRight() <<newRect.bottomLeft() <<newRect.topLeft() <<newRect.topRight();
	}
	else
	{ // BOTTOM-RIGHT... right?
		screenPoints << newRect.topLeft() <<newRect.topRight() <<newRect.bottomRight() <<newRect.bottomLeft() <<newRect.topLeft();
	}

	QList<Map2::CoordPlane> coords;
	coords << parentObj->coordinatesPlane();

	foreach(const QPointF &point, screenPoints)
	{
		coords << helper->pictureToPlane(point.toPoint());
	}

	for(int i = 0; i < coords.count(); ++i)
	{
		mapUpdatePointPlane(hObj, coords[i].x, coords[i].y, i+1);
	}

	mapCommitObject(hObj);
}

void Map2::MapFormularGroup::createBorderObject()
{
	Map2::MapHelper *helper = pParent->mapLayer()->mapView()->helper();

	IMGLINE parmLine;
	memset(&parmLine, 0x0, sizeof(IMGLINE));
	parmLine.Thick = helper->pix2mkm( mBorderWidthPx );
	parmLine.Color = RGB(mBorderColor.red(), mBorderColor.green(), mBorderColor.blue());

	HMAP hMap = pParent->mapLayer()->mapHandle();

	hObj = mapCreateSiteObject(hMap, pParent->mapLayer()->siteHandle(), IDDOUBLE2, 1);
	mapAppendDraw(hObj, IMG_LINE, (char*)&parmLine);

	for(int i = 0; i < 6; ++i)
	{
		mapAppendPointGeo(hObj, 0, 0, 0);
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

void Map2::MapFormularGroup::setSpacingPx(double value)
{
	mSpacingPx = value;
	update();
}

void Map2::MapFormularGroup::setPaddingPx(double value)
{
	mPaddingPx = value;
	update();
}

void Map2::MapFormularGroup::setBorderWidthPx(double value)
{
	mBorderWidthPx = value;
	update();
}

void Map2::MapFormularGroup::setOffset(const QPoint &offset)
{
	mOffset = offset;
	update();
}
