#ifndef LAYERSSETTINGSDIALOG_H
#define LAYERSSETTINGSDIALOG_H

#include <QDialog>
#include "map2/mapstructs.h"

namespace Ui
{
class LayersSettingsDialog;
}

class QModelIndex;
class QStandardItemModel;

namespace Map2 {

class LayersSettingsDialog : public QDialog
{
	Q_OBJECT
public:
	LayersSettingsDialog(HMAP hmap, QWidget *parent = 0);
	~LayersSettingsDialog();

	static QList<int> hiddenLayers();

	static void setHiddenLayers(HMAP hmap, QList<int> layers);

public slots:
	virtual void accept();

private:
	void fillLayers();
	static QString organization();
	static QString application();

	Ui::LayersSettingsDialog *ui;
	QStandardItemModel *pModel;
	HMAP hMap;
	HSELECT hSelect;
};

}

#endif // LAYERSSETTINGSDIALOG_H
