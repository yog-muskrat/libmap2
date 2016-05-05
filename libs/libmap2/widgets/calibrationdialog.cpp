#include "widgets/calibrationdialog.h"
#include "ui_calibrationdialog.h"

#include <qmath.h>
#include <QSettings>
#include <QApplication>
#include <QDesktopWidget>

Map2::CalibrationDialog::CalibrationDialog(QWidget *parent) : QDialog(parent), ui(new Ui::CalibrationDialog), mRatio(1.777)
{
	ui->setupUi(this);

	QString app = application();
	QString org = organization();

	QSettings set(org, app);
	mResolution = set.value("screen_resolution", QSize()).toSize();
	mDimension = set.value("screen_dimension", QSizeF()).toSizeF();
	mMkmInPx = set.value("screen_mkm_in_px", 255).toInt();
	mDpm = set.value("screen_dpm", 3000).toInt();

	ui->cbUnits->addItem("Дюймы", "inch");
	ui->cbUnits->addItem("Сантиметры", "cm");

	ui->cbDimension->addItem("Диагональ", "diagonal");
	ui->cbDimension->addItem("Ширина", "width");
	ui->cbDimension->addItem("Высота", "height");

	ui->sbResolutionH->setValue( mResolution.width() );
	ui->sbResolutionV->setValue( mResolution.height() );

	on_cbDimension_currentIndexChanged(0);

	ui->sbDpm->setValue( mDpm );
	ui->sbMkmInPx->setValue( mMkmInPx );

	updateRatio();
}

Map2::CalibrationDialog::~CalibrationDialog()
{

}

double Map2::CalibrationDialog::mkmInPx()
{
	QString app = application();
	QString org = organization();

	QSettings set(org, app);

	return set.value("screen_mkm_in_px", 255).toDouble();
}

double Map2::CalibrationDialog::dpm()
{
	QString app = application();
	QString org = organization();

	QSettings set(org, app);

	return set.value("screen_dpm", 3000).toDouble();
}

void Map2::CalibrationDialog::accept()
{
	QString app = application();
	QString org = organization();

	QSettings set(org, app);

	set.setValue("screen_resolution", mResolution);
	set.setValue("screen_dimension", mDimension);
	set.setValue("screen_mkm_in_px", mMkmInPx);
	set.setValue("screen_dpm", mDpm);

	QDialog::accept();
}

void Map2::CalibrationDialog::refreshResolution()
{
	QDesktopWidget *dw = QApplication::desktop();

	if(dw->screenCount() > 1)
	{
		QString comment = "Обнаружено несколько физических мониторов. "
						  "Калибровочные параметры необходимо задавать для одного из них. "
						  "Если параметры мониторов отличаются ― должны быть указаны параметры того, "
						  "на котором будет отображаться карта.";
		ui->lblComment->setText( comment );
	}
	else
	{
		ui->lblComment->clear();
	}

	mResolution = dw->screen( dw->primaryScreen() )->size();

	ui->sbResolutionH->setValue( mResolution.width() );
	ui->sbResolutionV->setValue( mResolution.height() );

	updateRatio();
	updateResults();
}

QString Map2::CalibrationDialog::organization()
{
	QString organization = qApp->organizationName();
	if(organization.isEmpty())
	{
		organization = "Mudbay";
	}

	return organization;
}

QString Map2::CalibrationDialog::application()
{
	QString application = qApp->applicationName();
	if(application.isEmpty())
	{
		application = "libmap2";
	}

	return application;
}

void Map2::CalibrationDialog::on_sbResolutionH_editingFinished()
{
	mResolution.setWidth( ui->sbResolutionH->value() );
	updateRatio();
	updateResults();
}

void Map2::CalibrationDialog::on_sbResolutionV_editingFinished()
{
	mResolution.setHeight( ui->sbResolutionV->value() );
	updateRatio();
	updateResults();
}

void Map2::CalibrationDialog::updateRatio()
{
	mRatio = (double)mResolution.width() / (double)mResolution.height();
}

void Map2::CalibrationDialog::updateResults()
{
	double dpmH = mResolution.width() * 100. / mDimension.width();
	double dpmV = mResolution.height() * 100. / mDimension.height();

	double mkmInPxH = mDimension.width() * 10000 / (double)mResolution.width();
	double mkmInPxV = mDimension.height() * 10000 / (double)mResolution.height();

	mDpm =  (int) ((dpmH + dpmV) / 2.);
	mMkmInPx = (int) ((mkmInPxH + mkmInPxV) / 2.);

	ui->sbDpm->setValue( mDpm );
	ui->sbMkmInPx->setValue( mMkmInPx );
}

void Map2::CalibrationDialog::on_dsbValue_editingFinished()
{
	int dimensionIndex = ui->cbDimension->currentIndex();
	QString dimension = ui->cbDimension->itemData(dimensionIndex).toString();

	int unitsIndex = ui->cbUnits->currentIndex();
	QString units = ui->cbUnits->itemData(unitsIndex).toString();

	double value = ui->dsbValue->value();

	if(units == "inch")
	{
		value *= 2.54;
	}

	if(dimension == "width")
	{
		mDimension.setWidth( value );
		mDimension.setWidth( value / mRatio );

	}
	else if(dimension == "height")
	{
		mDimension.setHeight( value );
		mDimension.setWidth( value*mRatio );
	}
	else if(dimension == "diagonal")
	{
		double h = qSqrt( qPow(value, 2) / (qPow(mRatio, 2) + 1) );
		double w = h * mRatio;

		mDimension.setWidth(w);
		mDimension.setHeight(h);
	}

	updateResults();
}

void Map2::CalibrationDialog::on_cbUnits_currentIndexChanged(int index)
{
	Q_UNUSED(index);

	int dimensionIndex = ui->cbDimension->currentIndex();
	QString dimension = ui->cbDimension->itemData(dimensionIndex).toString();

	int unitsIndex = ui->cbUnits->currentIndex();
	QString units = ui->cbUnits->itemData(unitsIndex).toString();

	double value = 0;

	if(dimension == "width")
	{
		value = mDimension.width();
	}
	else if(dimension == "height")
	{
		value = mDimension.height();
	}
	else if(dimension == "diagonal")
	{
		double w = mDimension.width();
		double h = mDimension.height();

		value = qSqrt( qPow(w, 2) + qPow(h, 2) );
	}

	if(units == "inch")
	{
		value /= 2.54;
	}

	ui->dsbValue->setValue( value );

	updateResults();
}

void Map2::CalibrationDialog::on_cbDimension_currentIndexChanged(int index)
{
	Q_UNUSED(index);

	int dimensionIndex = ui->cbDimension->currentIndex();
	QString dimension = ui->cbDimension->itemData(dimensionIndex).toString();

	int unitsIndex = ui->cbUnits->currentIndex();
	QString units = ui->cbUnits->itemData(unitsIndex).toString();

	double value = 0;

	if(dimension == "width")
	{
		value = mDimension.width();
	}
	else if(dimension == "height")
	{
		value = mDimension.height();
	}
	else if(dimension == "diagonal")
	{
		double w = mDimension.width();
		double h = mDimension.height();

		value = qSqrt( qPow(w, 2) + qPow(h, 2) );
	}

	if(units == "inch")
	{
		value /= 2.54;
	}

	ui->dsbValue->setValue( value );

	updateResults();
}
