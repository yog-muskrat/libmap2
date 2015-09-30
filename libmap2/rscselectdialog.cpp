#include "rscselectdialog.h"
#include "ui_rscselectdialog.h"

#include "gis/mapapi.h"
#include "gis/rscapi.h"
#include "gis/maptype.h"

#include <QDir>
#include <QDebug>
#include <QStandardItemModel>

RscSelectDialog::RscSelectDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::RscSelectDialog)
{
	ui->setupUi(this);

	pModel = new QStandardItemModel(this);
	pModel->setColumnCount(1);
	pModel->setHeaderData(0, Qt::Horizontal, "Файл");

	ui->listView->setModel( pModel );

	fillModel();
}

RscSelectDialog::~RscSelectDialog()
{
	delete ui;
}

QString RscSelectDialog::selectedRsc() const
{
	if(!ui->listView->currentIndex().isValid())
	{
		return "";
	}

	return pModel->index( ui->listView->currentIndex().row(), 0).data().toString();
}

void RscSelectDialog::fillModel()
{
	pModel->setRowCount(0);

	QString path = QString::fromLocal8Bit( mapGetCommonRscPath() );

	QDir rscDir(path);
	if(!rscDir.exists())
	{
		qDebug()<<"*** ВЫБОР КЛАССИФИКАТОРА: Несуществующий каталог классификаторов"<<path;
		return;
	}

	QFileInfoList files = rscDir.entryInfoList(QStringList()<<"*.rsc", QDir::NoDotAndDotDot | QDir::Files);

	foreach(const QFileInfo &fi, files)
	{
		HRSC rscHnd = mapOpenRsc( fi.absoluteFilePath().toLocal8Bit().data() );

		if(rscHnd <=0 )
		{
			qDebug()<<"*** ВЫБОР КЛАССИФИКАТОРА: Ошибка открытия классификатора"<<fi.absoluteFilePath();
			continue;
		}

		pModel->appendRow(new QStandardItem(fi.fileName()));

		mapCloseRsc(rscHnd);
	}
}
