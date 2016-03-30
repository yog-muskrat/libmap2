#ifndef COORDEDIT_H
#define COORDEDIT_H

#include <QWidget>

#include "map2/mapstructs.h"

class QLineEdit;
class QDoubleSpinBox;
namespace Map2
{

class CoordEdit : public QWidget
{
	Q_PROPERTY(Map2::Coord coordinate READ coordinate WRITE setCoordinate NOTIFY changed USER true)
	Q_OBJECT
public:
	/*!
	 * \brief Режим редактора
	 */
	enum Mode
	{
		String, //!< В виде строк ГГГ.ММ.СС
		Decimal //!< В виде градусов с десятой частью
	};

	CoordEdit(Map2::Coord coord = Map2::Coord(), CoordEdit::Mode m = CoordEdit::Decimal, QWidget *parent = 0);
	~CoordEdit(){}

	Map2::Coord coordinate() const;
	Mode mode() const;

public slots:
	void setCoordinate(Map2::Coord arg);
	void setMode(const Mode &value);

signals:
	void changed(Map2::Coord arg);

private slots:
	void onEdit();

private:
	void updateEditors();

	double stringToDouble(const QString &s) const;
	QString doubleToString(double d) const;

	Map2::Coord mCoordinate;
	Mode mMode;

	QLineEdit *leLat;
	QLineEdit *leLng;

	QDoubleSpinBox *dsbLat;
	QDoubleSpinBox *dsbLng;
};

}
#endif // COORDEDIT_H
