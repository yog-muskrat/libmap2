#include "widgets/layerssettingsdialog.h"
#include "ui_layerssettingsdialog.h"
#include "rscviewer.h"

#include "gis.h"

#include <QDebug>
#include <QSettings>
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
}

Map2::LayersSettingsDialog::~LayersSettingsDialog()
{
	mapDeleteSelectContext(hSelect);
}

QList<int> Map2::LayersSettingsDialog::hiddenLayers()
{
	QString app = application();
	QString org = organization();
	QSettings set(org, app);

	QVariantList vl = set.value("hidden_layers").toList();

	QList<int> result;

	foreach(const QVariant &v, vl)
	{
		result << v.toInt();
	}

	return result;
}

void Map2::LayersSettingsDialog::setHiddenLayers(HMAP hmap, QList<int> layers)
{
	HSELECT select = mapCreateMapSelectContext(hmap);
	int count = mapGetLayerCount(hmap);

	QVariantList vl;

	for(int i = 0; i < count; ++i)
	{
		int check = layers.contains(i) ? 0 : 1;
		mapSelectLayer(select, i, check);

		if(check == 0)
		{
			vl << i;
		}
	}
	mapSetViewSelect(hmap, select);

	QString app = application();
	QString org = organization();
	QSettings set(org, app);
	set.setValue("hidden_layers", vl);
}

QStringList Map2::LayersSettingsDialog::mapLayers(HMAP hMap)
{
	QStringList result;

	QTextCodec *tc = RscViewer::codec();

	int count = mapGetLayerCount(hMap);

	for(int i = 0; i < count; ++i)
	{
		QByteArray ba = mapGetLayerName(hMap, i);
		result << tc->toUnicode(ba);
	}

	return result;
}

void Map2::LayersSettingsDialog::accept()
{
	QVariantList vl;

	for(int i = 0; i < pModel->rowCount(); ++i)
	{
		QStandardItem *item = pModel->item(i);

		int layer = item->data().toInt();
		int check = item->data(Qt::CheckStateRole).toInt() == Qt::Checked ? 1 : 0;

		mapSelectLayer(hSelect, layer, check);

		if(check == 0)
		{
			vl << i;
		}
	}

	mapSetViewSelect(hMap, hSelect);

	QString app = application();
	QString org = organization();
	QSettings set(org, app);
	set.setValue("hidden_layers", vl);

	QDialog::accept();
}

void Map2::LayersSettingsDialog::fillLayers()
{
	pModel->clear();

	mapGetViewSelect(hMap, hSelect);

	QTextCodec *tc = RscViewer::codec();

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

QString Map2::LayersSettingsDialog::organization()
{
	QString organization = qApp->organizationName();
	if(organization.isEmpty())
	{
		organization = "Mudbay";
	}

	return organization;
}

QString Map2::LayersSettingsDialog::application()
{
	QString application = qApp->applicationName();
	if(application.isEmpty())
	{
		application = "libmap2";
	}

	return application;
}
