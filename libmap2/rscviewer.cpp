#include "rscviewer.h"
#include "ui_rscviewer.h"

#include "gis.h"

#include <QDebug>
#include <QLayout>
#include <QTextCodec>
#include <QStandardItemModel>
#include <QDialog>
#include <QPushButton>

RscViewer::RscViewer(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::RscViewer), mRscHandle(0), mTmpSiteHandle(0), mMapBitDepth(mapGetMapScreenDepth())
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

	QString path = QTextCodec::codecForName("koi8r")->toUnicode( mapGetCommonRscPath() ) + "/" + mRscName;
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

long RscViewer::selectExCode(QString rscName)
{
	QDialog d;
	d.setWindowTitle("Выбор знака");

	QPushButton pbOk("Готово");
	QPushButton pbCancel("Отмена");

	RscViewer view;
	view.setRsc(rscName);

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

	if(!d.exec())
	{
		return 0;
	}

	return view.selectedSignCode();
}

void RscViewer::showObjectsForRscLayer(const QModelIndex &index)
{
	QTextCodec *codec = QTextCodec::codecForName("koi8r");

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
		int colors = mapGetSiteColorsCount(mTmpSiteHandle, mTmpSiteHandle);
		COLORREF *colorimage = new COLORREF[colors];
		mapGetSitePalette(mTmpSiteHandle, mTmpSiteHandle, colorimage, colors);

		mapPaintExampleObjectByFuncToXImage(mTmpSiteHandle, &ximage, &rect, function, params, colors, colorimage, QByteArray(name).data(), local);

		delete colorimage;

		QString keyString = codec->toUnicode( key );
		QString nameString = codec->toUnicode( name );

		QImage img = QImage((uchar *) dataBytes, iconSize.width(), iconSize.height(), QImage::Format_RGB32).copy();

		pRscObjectsModel->appendRow( new QStandardItem( nameString ) );

		QModelIndex idx = pRscObjectsModel->index( pRscObjectsModel->rowCount() - 1, 0);
		pRscObjectsModel->setData( idx, img, Qt::DecorationRole);
		pRscObjectsModel->setData( idx, keyString, KeyRole);
		pRscObjectsModel->setData( idx, QVariant::fromValue(excode), ExCodeRole);
		pRscObjectsModel->setData( idx, img, ImageRole);

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
		QString rscLayerName = QTextCodec::codecForName("koi8r")->toUnicode( mapGetRscSegmentName( mRscHandle, i) );

		pRscLayersModel->appendRow( new QStandardItem(rscLayerName) );
		pRscLayersModel->setData( pRscLayersModel->index(i, 0), i, Qt::UserRole + 1);
	}
}
