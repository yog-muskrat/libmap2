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

public slots:
	virtual void accept();

private slots:
	void onDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);

private:
	void fillLayers();

	Ui::LayersSettingsDialog *ui;
	QStandardItemModel *pModel;
	HMAP hMap;
	HSELECT hSelect;
};

}

#endif // LAYERSSETTINGSDIALOG_H
