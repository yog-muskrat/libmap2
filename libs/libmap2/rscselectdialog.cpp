#include "rscselectdialog.h"
#include "ui_rscselectdialog.h"

#include "gis.h"
#include "rscviewer.h"

#include <QDir>
#include <QDebug>
#include <QTextCodec>
#include <QStandardItemModel>

using namespace Map2;

RscSelectDialog::RscSelectDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::RscSelectDialog)
{
	ui->setupUi(this);

	pModel = new QStandardItemModel(this);
	pModel->setColumnCount(2);
	pModel->setHeaderData(0, Qt::Horizontal, "Файл");
	pModel->setHeaderData(1, Qt::Horizontal, "Название");

	ui->tableView->setModel( pModel );

	fillModel();
}

RscSelectDialog::~RscSelectDialog()
{
	delete ui;
}

QString RscSelectDialog::selectedRsc() const
{
	if(!ui->tableView->currentIndex().isValid())
	{
		return "";
	}

	return pModel->index( ui->tableView->currentIndex().row(), 0).data().toString();
}

void RscSelectDialog::fillModel()
{
	pModel->setRowCount(0);

	QTextCodec *codec = QTextCodec::codecForName("koi8r");

	QString path = codec->toUnicode( mapGetCommonRscPath() );

	QDir rscDir(path);
	if(!rscDir.exists())
	{
		qDebug()<<"*** ВЫБОР КЛАССИФИКАТОРА: Несуществующий каталог классификаторов"<<path;
		return;
	}

	QFileInfoList files = rscDir.entryInfoList(QStringList()<<"*.rsc", QDir::NoDotAndDotDot | QDir::Files);

	foreach(const QFileInfo &fi, files)
	{
		HRSC rscHnd = mapOpenRsc( codec->fromUnicode( fi.absoluteFilePath() ).data() );

		if(rscHnd <=0 )
		{
			qDebug()<<"*** ВЫБОР КЛАССИФИКАТОРА: Ошибка открытия классификатора"<<fi.absoluteFilePath();
			continue;
		}

		RSCCREATE rscCreate;
		PALETTE256 palette;

		mapGetRscDescribe(rscHnd, &rscCreate, &palette);

		QTextCodec *tc = RscViewer::codec();

		QString name = tc->toUnicode( QByteArray(rscCreate.Name) );

		pModel->appendRow( QList<QStandardItem*>() << new QStandardItem(fi.fileName()) << new QStandardItem(name) );

		mapCloseRsc(rscHnd);
	}
}
