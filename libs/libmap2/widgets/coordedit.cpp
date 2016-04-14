#include "widgets/coordedit.h"

#include "qmath.h"
#include <QDebug>
#include <QLayout>
#include <QLineEdit>
#include <QDoubleSpinBox>

using namespace Map2;

CoordEdit::CoordEdit(Map2::Coord coord, Map2::CoordEdit::Mode m, QWidget *parent) :
	QWidget(parent), mCoordinate(coord), mMode(m)
{
	setFocusPolicy(Qt::StrongFocus);

	QHBoxLayout *mainLay = new QHBoxLayout(this);
	mainLay->setContentsMargins( QMargins() );
	mainLay->setSpacing(2);

	leLat = new QLineEdit();
	leLat->setValidator( new QRegExpValidator( QRegExp("\\d{0,2}\\.\\d{0,2}\\.\\d{0,2}[NnSs]")) );
	leLat->setText("00.00.00N");

	leLng = new QLineEdit();
	leLng->setValidator( new QRegExpValidator( QRegExp("\\d{0,3}\\.\\d{0,2}\\.\\d{0,2}[EeWw]")) );
	leLng->setText("000.00.00E");

	dsbLat = new QDoubleSpinBox();
	dsbLat->setRange(-90., 90.);
	dsbLng = new QDoubleSpinBox();
	dsbLng->setRange(-180., 180.);

	mainLay->addWidget(leLat);
	mainLay->addWidget(dsbLat);
	mainLay->addWidget(leLng);
	mainLay->addWidget(dsbLng);

	connect(leLat, SIGNAL(editingFinished()), this, SLOT(onEdit()));
	connect(leLng, SIGNAL(editingFinished()), this, SLOT(onEdit()));
	connect(dsbLat, SIGNAL(editingFinished()), this, SLOT(onEdit()));
	connect(dsbLng, SIGNAL(editingFinished()), this, SLOT(onEdit()));

	setMode(mMode);
}

Map2::Coord CoordEdit::coordinate() const
{
	return mCoordinate;
}

void CoordEdit::setCoordinate(Map2::Coord arg)
{
	if (mCoordinate == arg)
	{
		return;
	}

	mCoordinate = arg;

	updateEditors();

	emit changed(arg);
}
Map2::CoordEdit::Mode CoordEdit::mode() const
{
	return mMode;
}

void CoordEdit::setMode(const Mode &value)
{
	mMode = value;

	updateEditors();

	leLat->setVisible( mMode == String );
	leLng->setVisible( mMode == String );

	dsbLat->setVisible( mMode == Decimal );
	dsbLng->setVisible( mMode == Decimal );
}

void CoordEdit::onEdit()
{
	if(mMode == Decimal)
	{
		mCoordinate.lat = dsbLat->value();
		mCoordinate.lng = dsbLng->value();
	}
	else if(mMode == String)
	{
		mCoordinate.lat = stringToDouble( leLat->text());
		mCoordinate.lng = stringToDouble( leLng->text());
	}

	setFocus();

	emit changed( mCoordinate );
}

void CoordEdit::updateEditors()
{
	dsbLat->setValue( mCoordinate.lat );
	dsbLng->setValue( mCoordinate.lng );

	QString lat = doubleToString(mCoordinate.lat);
	lat += mCoordinate.lat < 0 ? "S" : "N";

	QString lng = doubleToString(mCoordinate.lng);
	lng += mCoordinate.lng < 0 ? "W" : "E";

	leLat->setText(lat);
	leLng->setText(lng);
}

double CoordEdit::stringToDouble(const QString &s) const
{
	QStringList sl = s.split(".");

	if(sl.count() != 3)
	{
		qDebug()<<"*** "<< objectName()<<": Ошибка при обработке координаты"<<s;
		return 0.;
	}

	QString letter = sl[2].right(1);

	double degree = sl[0].toDouble();
	degree += sl[1].toDouble() / 60. + sl[2].left(2).toDouble() / 3600.;

	if( letter.contains( QRegExp("[SsWw]")) )
	{
		degree *= -1;
	}

	return degree;
}

QString CoordEdit::doubleToString(double d) const
{
	double degree = 0.;
	double mins = 0.;
	double secs = 0.;

	double fract = modf(d, &degree) * 60;
	fract = modf(fract, &mins) * 60;
	fract = modf(fract, &secs);

	QString s = QString("%0.%1.%2").arg((int)degree).arg((int)mins, 2, 10, QChar('0')).arg((int)secs, 2, 10, QChar('0'));

	return s;
}
