#ifndef RSCVIEWER_H
#define RSCVIEWER_H

#include <QWidget>
#include <QModelIndex>

#include "gis.h"

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
	 * \brief Фильтрует знаки по типу локализации.
	 */
	void setLocalFilter(int local);

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

	static long selectExCode(QString rscName, int localFilter = -1);
	static long selectVectorExCode(QString rscName);
	static long selectLineExCode(QString rscName);
	static long selectAreaExCode(QString rscName);
	static long selectTextExCode(QString rscName);

signals:
	void signSelected();

private slots:
	/*!
	 * \brief Показывает объекты слоя классификаторе.
	 * \param index Модельный индекс слоя классификатора.
	 */
	void showObjectsForRscLayer(const QModelIndex &index);

	void on_cbLocal_activated(int index);

private:
	/*!
	 * \brief Заполняет список слоев классификатора.
	 */
	void fillRscLayers();

	void hideFilter();

	Ui::RscViewer *ui;

	QString mRscName; //!< Имя файла классификатора.
	HRSC mRscHandle; //!< Идентификатор классификатора.
	HSITE mTmpSiteHandle; //!< Идентификатор временной пользовательской карты.

	QStandardItemModel *pRscLayersModel;
	QStandardItemModel *pRscObjectsModel;
	long mMapBitDepth;
	int mLocalFilter;
};

#endif // RSCVIEWER_H
