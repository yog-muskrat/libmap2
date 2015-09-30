#ifndef RSCSELECTDIALOG_H
#define RSCSELECTDIALOG_H

#include <QDialog>

namespace Ui {
class RscSelectDialog;
}

class QStandardItemModel;

class RscSelectDialog : public QDialog
{
	Q_OBJECT
public:
	explicit RscSelectDialog(QWidget *parent = 0);
	~RscSelectDialog();

	QString selectedRsc() const;

private:
	void fillModel();

	Ui::RscSelectDialog *ui;
	QStandardItemModel *pModel;
};

#endif // RSCSELECTDIALOG_H
