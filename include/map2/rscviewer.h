#ifndef RSCVIEWER_H
#define RSCVIEWER_H

#include <QWidget>
#include <QModelIndex>

#include "mapstructs.h"

namespace Ui {
class RscViewer;
}

class QStandardItemModel;

namespace Map2
{

class RscViewer : public QWidget
{
	Q_OBJECT

public:
	enum DataRoles
	{
		ExCodeRole = Qt::UserRole + 1,
		KeyRole,
		ImageRole,
		LocalRole,
		LayerRole
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
	 * Если знак не выбран, будет возвращен 0.
	 */
	long selectedSignCode() const;

	/*!
	 * \brief Возвращает ключ выбранного знака.
	 * Если ключ не выбран, будет возвращена пустая строка.
	 */
	QString selectedSignKey() const;

	/*!
	 * \brief Возвращает изображение выбранного знака.
	 */
	QImage selectedSignImage() const;

	static QString selectKey(const QString &rscName, int localFilter = -1);
	static QString selectVectorKey(const QString &rscName);
	static QString selectLineKey(const QString &rscName);
	static QString selectZoneKey(const QString &rscName);
	static QString selectTextKey(const QString &rscName);
	static QImage image(const QString &key, const QString &rscName, const QSize &iconSize = QSize(64, 64));

	static QTextCodec *codec();

signals:
	void signSelected();

private slots:
	/*!
	 * \brief Показывает объекты слоя классификаторе.
	 * \param index Модельный индекс слоя классификатора.
	 */
	void showObjectsForRscLayer(const QModelIndex &index);

	void on_cbLocal_activated(int index);

	void on_objectsList_clicked(const QModelIndex &index);

private:
	/*!
	 * \brief Заполняет список слоев классификатора.
	 */
	void fillRscLayers();

	void hideFilter();

	int objectsCountForLayer(int layerSegmentNumber, int localType = -1);

	Ui::RscViewer *ui;

	QString mRscName; //!< Имя файла классификатора.
	HRSC mRscHandle; //!< Идентификатор классификатора.
	HSITE mTmpSiteHandle; //!< Идентификатор временной пользовательской карты.

	QStandardItemModel *pRscLayersModel;
	QStandardItemModel *pRscObjectsModel;
	long mMapBitDepth;
	int mLocalFilter;
};
}
#endif // RSCVIEWER_H
