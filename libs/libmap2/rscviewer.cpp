#include "rscviewer.h"
#include "ui_rscviewer.h"

#include "gis.h"

#include <QDebug>
#include <QDialog>
#include <QLayout>
#include <QSettings>
#include <QFileInfo>
#include <QTextCodec>
#include <QPushButton>
#include <QStandardItemModel>

using namespace Map2;

RscViewer::RscViewer(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::RscViewer), mRscHandle(0), mTmpSiteHandle(0), mMapBitDepth(mapGetMapScreenDepth()), mLocalFilter(-1)
{
	ui->setupUi(this);

	pRscLayersModel = new QStandardItemModel(this);
	pRscObjectsModel = new QStandardItemModel(this);

	pRscLayersModel->setColumnCount(1);
	pRscLayersModel->setHeaderData(0, Qt::Horizontal, "Слои классификатора");
	ui->rscLayerList->setModel(pRscLayersModel);

	pRscObjectsModel->setColumnCount(1);
	pRscObjectsModel->setHeaderData(0, Qt::Horizontal, "Объекты слоя");
	ui->objectsList->setModel(pRscObjectsModel);

	ui->cbLocal->addItem("Все", -1);
	ui->cbLocal->addItem("Векторный", static_cast<int>(LOCAL_VECTOR));
	ui->cbLocal->addItem("Линия", static_cast<int>(LOCAL_LINE));
	ui->cbLocal->addItem("Площадной", static_cast<int>(LOCAL_SQUARE));
	ui->cbLocal->addItem("Подпись", static_cast<int>(LOCAL_TITLE));

	connect(ui->objectsList, SIGNAL(doubleClicked(QModelIndex)), this, SIGNAL(signSelected()));
}

RscViewer::~RscViewer()
{
	delete ui;

	if(mTmpSiteHandle > 0)
	{
		mapCloseData(mTmpSiteHandle);
	}
}

void RscViewer::setRsc(QString rscName)
{
	if(mTmpSiteHandle > 0)
	{
		mapCloseData(mTmpSiteHandle);
		mTmpSiteHandle = 0;
		mRscHandle = 0;
	}

	mRscName = rscName;

	ui->lblTitle->setText(mRscName);

	QString path;
	if(QFileInfo(mRscName).isRelative())
	{
		path = codec()->toUnicode( mapGetCommonRscPath() ) + "/" + mRscName;
	}
	mTmpSiteHandle = mapCreateTempSite(path.toLocal8Bit().data() );
	mapSetBackColor(mTmpSiteHandle, -1);

	mRscHandle = mapGetRscIdent(mTmpSiteHandle, mTmpSiteHandle);

	if( mRscHandle <= 0)
	{
		qDebug()<<"*** ПРОСМОТР КЛАССИФИКАТОРА: Ошибка открытия классификатора"<<rscName;
		return;
	}

	fillRscLayers();
}

void RscViewer::setLocalFilter(int local)
{
	if(local == mLocalFilter)
	{
		return;
	}

	mLocalFilter = local;

	ui->cbLocal->setCurrentIndex(-1);
	for(int i = 0; i < ui->cbLocal->count(); ++i)
	{
		if(ui->cbLocal->itemData(i).toInt() == i)
		{
			ui->cbLocal->setCurrentIndex(i);
			break;
		}
	}

	fillRscLayers();
}

long RscViewer::selectedSignCode() const
{
	QModelIndex idx = ui->objectsList->currentIndex();
	if(!idx.isValid())
	{
		return 0;
	}

	return idx.data(ExCodeRole).toInt();
}

QString RscViewer::selectedSignKey() const
{
	QModelIndex idx = ui->objectsList->currentIndex();
	if(!idx.isValid())
	{
		return 0;
	}

	return idx.data(KeyRole).toString();
}

QImage RscViewer::selectedSignImage() const
{
	QModelIndex idx = ui->objectsList->currentIndex();
	if(!idx.isValid())
	{
		return QImage();
	}

	return idx.data(ImageRole).value<QImage>();
}

QString RscViewer::selectKey(const QString &rscName, int localFilter)
{
	QDialog d;
	d.setWindowTitle("Выбор знака");

	QPushButton pbOk("Готово");
	QPushButton pbCancel("Отмена");

	RscViewer view;
	view.setRsc(rscName);
	view.setLocalFilter(localFilter);
	if(localFilter >= 0)
	{
		view.hideFilter();
	}

	connect(&pbOk, SIGNAL(clicked()), &d, SLOT(accept()));
	connect(&view, SIGNAL(signSelected()), &d, SLOT(accept()));
	connect(&pbCancel, SIGNAL(clicked()), &d, SLOT(reject()));

	QVBoxLayout *main = new QVBoxLayout(&d);

	main->addWidget( &view );

	QHBoxLayout *btnlay = new QHBoxLayout();
	btnlay->addStretch();
	btnlay->addWidget( &pbOk );
	btnlay->addWidget( &pbCancel );

	main->addLayout(btnlay);

	QSettings set(qApp->organizationName(), qApp->applicationName());

	d.restoreGeometry( set.value("rscviewer_geometry").toByteArray() );

	bool ok = d.exec();

	set.setValue("rscviewer_geometry", d.saveGeometry() );

	if(!ok)
	{
		return 0;
	}

	return view.selectedSignKey();
}

QString RscViewer::selectVectorKey(const QString &rscName)
{
	return selectKey(rscName, LOCAL_VECTOR);
}

QString RscViewer::selectLineKey(const QString &rscName)
{
	return selectKey(rscName, LOCAL_LINE);
}

QString RscViewer::selectZoneKey(const QString &rscName)
{
	return selectKey(rscName, LOCAL_SQUARE);
}

QString RscViewer::selectTextKey(const QString &rscName)
{
	return selectKey(rscName, LOCAL_TITLE);
}

QImage RscViewer::image(const QString &key, const QString &rscName, const QSize &iconSize)
{
	QString path;
	if(QFileInfo(rscName).isRelative())
	{
		path = codec()->toUnicode( mapGetCommonRscPath() ) + "/" + rscName;
	}
	HSITE hSite = mapCreateTempSite(path.toLocal8Bit().data() );
	mapSetBackColor(hSite, -1);

	HRSC hRsc = mapGetRscIdent(hSite, hSite);

	if( hRsc <= 0)
	{
		mapCloseData(hSite);
		qDebug()<<"*** ПРОСМОТР КЛАССИФИКАТОРА: Ошибка открытия классификатора"<<rscName;
		return QImage();
	}

	int bitDepth = mapGetMapScreenDepth();

	int bytesPerLine = static_cast<int>( (double)iconSize.width() * (double)bitDepth / 8.);
	long dataSize = bytesPerLine * iconSize.height();

	char *dataBytes = AllocateTheMemory(dataSize);
	memset(dataBytes, 0x0, dataSize);

	long incode = mapGetRscObjectKeyIncode(hRsc, codec()->fromUnicode(key).data());
	const char* name =  mapGetRscObjectName(hRsc, incode);
	long function = mapGetRscObjectFunction(hRsc, incode);
	char* params = const_cast<char*>(mapGetRscObjectParameters(hRsc,incode ));

	///TODO: Доделать!!
	//long local = mapGetRscObjectLocalInLayer(hRsc, segmentNumber, i);
	long local = LOCAL_VECTOR;

	XIMAGEDESC ximage;
	ximage.Point = dataBytes;
	ximage.Width = iconSize.width();
	ximage.Height = iconSize.height();
	ximage.Depth = bitDepth;
	ximage.CellSize = (double)bitDepth / 8;
	ximage.RowSize = bytesPerLine;

	RECT rect;
	rect.top = 0;
	rect.left = 0;
	rect.bottom = iconSize.height();
	rect.right = iconSize.width();

	int colors = mapGetSiteColorsCount(hSite, hSite);
	COLORREF colorimage[colors];
	mapGetSitePalette(hSite, hSite, colorimage, colors);

	mapPaintExampleObjectByFuncToXImage(hSite, &ximage, &rect, function, params, colors, colorimage, QByteArray(name).data(), local);

	QImage img = QImage((uchar *) dataBytes, iconSize.width(), iconSize.height(), QImage::Format_RGB32).copy();

	FreeTheMemory(dataBytes);
	mapCloseData(hSite);

	return img;
}

QTextCodec *RscViewer::codec()
{
	return QTextCodec::codecForName("koi8r");
}

void RscViewer::showObjectsForRscLayer(const QModelIndex &index)
{
	pRscObjectsModel->setRowCount(0);

	int segmentNumber = index.data(Qt::UserRole+1).toInt();


	int objCount = mapGetRscSegmentObjectCount(mRscHandle, segmentNumber);

	QSize iconSize = ui->objectsList->iconSize();

	int bytesPerLine = static_cast<int>( (double)iconSize.width() * (double)mMapBitDepth / 8.);
	long size = bytesPerLine * iconSize.height();

	char *dataBytes = AllocateTheMemory(size);

	XIMAGEDESC ximage;

	ximage.Point = dataBytes;
	ximage.Width = iconSize.width();
	ximage.Height = iconSize.height();
	ximage.Depth = mMapBitDepth;
	ximage.CellSize = (double)mMapBitDepth / 8;
	ximage.RowSize = bytesPerLine;

	RECT rect;
	rect.top = 0;
	rect.left = 0;
	rect.bottom = iconSize.height();
	rect.right = iconSize.width();

	QString tooltip = "<b>Знак:</b>%0<br><b>Ключ:</b>%1<br><b>Код:</b>%2";

	for(int i = 1; i <= objCount; ++i)
	{
		memset(dataBytes, 0x0, size);

		long incode = mapGetRscObjectCodeInLayer(mRscHandle, segmentNumber, i);
		long excode = mapGetRscObjectExcodeInLayer(mRscHandle, segmentNumber, i);
		const char* key = mapGetRscObjectKey(mRscHandle, incode);
		const char* name =  mapGetRscObjectName(mRscHandle, incode);
		long function = mapGetRscObjectFunction(mRscHandle, incode);
		char* params = const_cast<char*>(mapGetRscObjectParameters(mRscHandle,incode ));
		long local = mapGetRscObjectLocalInLayer(mRscHandle, segmentNumber, i);

		if(mLocalFilter >= 0 && local != mLocalFilter)
		{
			continue;
		}

		int colors = mapGetSiteColorsCount(mTmpSiteHandle, mTmpSiteHandle);
		COLORREF *colorimage = new COLORREF[colors];
		mapGetSitePalette(mTmpSiteHandle, mTmpSiteHandle, colorimage, colors);

		mapPaintExampleObjectByFuncToXImage(mTmpSiteHandle, &ximage, &rect, function, params, colors, colorimage, QByteArray(name).data(), local);

		delete[] colorimage;

		QImage img = QImage((uchar *) dataBytes, iconSize.width(), iconSize.height(), QImage::Format_RGB32).copy();

		QString keyString = codec()->toUnicode( key );
		QString nameString = codec()->toUnicode( name );

		pRscObjectsModel->appendRow( new QStandardItem( nameString ) );

		QModelIndex idx = pRscObjectsModel->index( pRscObjectsModel->rowCount() - 1, 0);
		pRscObjectsModel->setData( idx, img, Qt::DecorationRole);
		pRscObjectsModel->setData( idx, keyString, KeyRole);
		pRscObjectsModel->setData( idx, QVariant::fromValue(excode), ExCodeRole);
		pRscObjectsModel->setData( idx, img, ImageRole);
		pRscObjectsModel->setData( idx, QVariant::fromValue(local), LocalRole);
		pRscObjectsModel->setData( idx, index.data(), LayerRole);

		pRscObjectsModel->setData( idx, tooltip.arg(nameString, keyString).arg(excode), Qt::ToolTipRole);
	}

	FreeTheMemory(dataBytes);
}

void RscViewer::fillRscLayers()
{
	pRscObjectsModel->setRowCount(0);
	pRscLayersModel->setRowCount(0);

	int cnt = mapGetRscSegmentCount(mRscHandle);

	for(int i = 0; i < cnt; ++i)
	{
		if(objectsCountForLayer(i, mLocalFilter) <= 0)
		{
			continue;
		}

		QString rscLayerName = QTextCodec::codecForName("koi8r")->toUnicode( mapGetRscSegmentName( mRscHandle, i) );

		int row = pRscLayersModel->rowCount();

		pRscLayersModel->insertRow(row, new QStandardItem(rscLayerName) );
		pRscLayersModel->setData( pRscLayersModel->index( row, 0), i, Qt::UserRole + 1);
	}
}

void RscViewer::hideFilter()
{
	ui->lblLocal->hide();
	ui->cbLocal->hide();
}

int RscViewer::objectsCountForLayer(int layerSegmentNumber, int localType)
{
	int objCount = mapGetRscSegmentObjectCount(mRscHandle, layerSegmentNumber);

	int total = 0;

	for(int i = 1; i <= objCount; ++i)
	{
		long local = mapGetRscObjectLocalInLayer(mRscHandle, layerSegmentNumber, i);

		if(localType >= 0 && local != localType)
		{
			continue;
		}

		++total;
	}
	return total;
}

void RscViewer::on_cbLocal_activated(int index)
{
	setLocalFilter( ui->cbLocal->itemData(index).toInt() );
}

void Map2::RscViewer::on_objectsList_clicked(const QModelIndex &index)
{
	if(!index.isValid())
	{
		return;
	}

	ui->lblIcon->setPixmap( QPixmap::fromImage( index.data(ImageRole).value<QImage>()));
	ui->lblKey->setText(index.data(KeyRole).toString());
	ui->lblKod->setText( index.data(ExCodeRole).toString());
	ui->lblLocal->setText(index.data(LocalRole).toString());
	ui->lblLayer->setText(index.data(LayerRole).toString());
}
