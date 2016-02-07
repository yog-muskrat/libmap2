#include "widgets/layerssettingsdialog.h"
#include "ui_layerssettingsdialog.h"

#include "gis.h"

#include <QDebug>
#include <QTextCodec>
#include <QStandardItemModel>

Map2::LayersSettingsDialog::LayersSettingsDialog(HMAP hmap, QWidget *parent) :
	QDialog(parent), ui(new Ui::LayersSettingsDialog), hMap(hmap)
{
	ui->setupUi( this );
	pModel = new QStandardItemModel(this);

	ui->listView->setModel(pModel);

	hSelect = mapCreateMapSelectContext(hMap);

	fillLayers();

	connect(pModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(onDataChanged(QModelIndex, QModelIndex)));
}

Map2::LayersSettingsDialog::~LayersSettingsDialog()
{
	mapDeleteSelectContext(hSelect);
}

void Map2::LayersSettingsDialog::accept()
{
	for(int i = 0; i < pModel->rowCount(); ++i)
	{
		QStandardItem *item = pModel->item(i);

		int layer = item->data().toInt();
		int check = item->data(Qt::CheckStateRole).toInt() == Qt::Checked ? 1 : 0;

		mapSelectLayer(hSelect, layer, check);
	}

	mapSetViewSelect(hMap, hSelect);

	QDialog::accept();
}

void Map2::LayersSettingsDialog::onDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{
	for(int i = topLeft.row(); i <= bottomRight.row(); ++i )
	{
		QStandardItem *item = pModel->item(i);
		int layer = item->data().toInt();
		int check = item->data(Qt::CheckStateRole).toInt() == Qt::Checked ? 1 : 0;

		mapSelectLayer(hSelect, layer, check);
	}

	mapSetViewSelect(hMap, hSelect);
}

void Map2::LayersSettingsDialog::fillLayers()
{
	pModel->clear();

	mapGetViewSelect(hMap, hSelect);

	QTextCodec *tc = QTextCodec::codecForName("koi8-r");

	int count = mapGetLayerCount(hMap);

	for(int i = 0; i < count; ++i)
	{
		QByteArray ba = mapGetLayerName(hMap, i);

		int check = mapCheckLayer(hSelect, i);

		Qt::CheckState cs = (check == 0 ? Qt::Unchecked : Qt::Checked);

		QStandardItem *item = new QStandardItem( tc->toUnicode(ba) );
		item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
		item->setData(cs, Qt::CheckStateRole);
		item->setData(i); // Номер слоя
		pModel->appendRow(item);
	}
}
