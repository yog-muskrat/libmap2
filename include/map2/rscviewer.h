#ifndef RSCVIEWER_H
#define RSCVIEWER_H

#include <QWidget>
#include "gis/maptype.h"

namespace Ui {
class RscViewer;
}

class QStandardItemModel;

class RscViewer : public QWidget
{
	Q_OBJECT

public:
	enum DataRoles
	{
		ExCodeRole = Qt::UserRole + 1,
		KeyRole,
		ImageRole
	};

	explicit RscViewer(QWidget *parent = 0);
	~RscViewer();

	/*!
	 * \brief Показать содержимое классификатора.
	 * \param rscName Имя RSC-файла в общем каталое классификаторов.
	 */
	void setRsc(QString rscName);

	/*!
	 * \brief Возвращает код выбранного знака.
	 * Если знак не выбра, будет возвращен 0.
	 */
	long selectedSignCode() const;

	/*!
	 * \brief Возвращает ключ выбранного знака.
	 * Если ключ не выбран, будет возвращена пустая строка.
	 */
	QString selectedSignKey() const;

private slots:
	/*!
	 * \brief Показывает объекты слоя классификаторе.
	 * \param index Модельный индекс слоя классификатора.
	 */
	void showObjectsForRscLayer(const QModelIndex &index);

private:
	/*!
	 * \brief Заполняет список слоев классификатора.
	 */
	void fillRscLayers();

	Ui::RscViewer *ui;

	QString mRscName; //!< Имя файла классификатора.
	HRSC mRscHandle; //!< Идентификатор классификатора.
	HSITE mTmpSiteHandle; //!< Идентификатор временной пользовательской карты.

	QStandardItemModel *pRscLayersModel;
	QStandardItemModel *pRscObjectsModel;
	long mMapBitDepth;
};

#endif // RSCVIEWER_H
