#ifndef CALIBRATIONDIALOG_H
#define CALIBRATIONDIALOG_H

#include <QDialog>
namespace Ui
{
class CalibrationDialog;
}

namespace Map2
{

class CalibrationDialog : public QDialog
{
	Q_OBJECT
public:
	explicit CalibrationDialog(QWidget *parent = 0);
	~CalibrationDialog();

	static double mkmInPx();
	static double dpm();

public slots:
	virtual void accept();

private slots:
	void refreshResolution();

	void on_dsbValue_editingFinished();
	void on_sbResolutionH_editingFinished();
	void on_sbResolutionV_editingFinished();
	void on_cbUnits_currentIndexChanged(int index);
	void on_cbDimension_currentIndexChanged(int index);

private:
	void updateRatio();
	void updateResults();

	static QString organization();
	static QString application();

	Ui::CalibrationDialog *ui;
	QSize mResolution;
	QSizeF mDimension;
	double mRatio;
	int mMkmInPx;
	int mDpm;
};
}

#endif // CALIBRATIONDIALOG_H
