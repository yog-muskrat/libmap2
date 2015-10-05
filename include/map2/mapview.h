#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QWidget>

#include "structs.h"
#include "gis.h"

class QLabel;
class MapLayer;
class QToolBar;
class MapCanvas;
class MapObject;
class QScrollBar;
class LayersModel;
class MapNavigation;

/*!
 * \brief Виджет для отображения карты
 */
class MapView : public QWidget
{
	Q_OBJECT
public:
	/*!
	 * \brief Картографические инструменты
	 */
	enum Tools
	{
		None,
		MoveObject,
		DeleteObject,
		AddVectorObject,
		AddZoneObject,
		AddLineObject,
		Ruler, //!< Измерение расстояний
		RectZoom //!< Приблизить область
	};

	/*!
	 * \brief Конструктор класса.
	 * \param sitDir Каталог для sit-файлов создаваемых для слоев карты.
	 * \param rscDir Каталог классификаторов.
	 * \param parent Родительский виджет.
	 */
	MapView(QString sitDir, QString rscDir, QWidget *parent = 0);
	~MapView();

	/*!
	 * \brief Загружает указанную карту.
	 * \param mapFullPath Полный путь к файлу карты.
	 */
	void openMap(QString mapFullPath);

	/*!
	 * \brief Создает новый картографический слой, использующий заданный классификатор знаков.
	 * Если классификатор не задан, будет вызван диалог выбора классификатора.
	 * Слой автоматически добавляется к карте и попадает в список ее слоев.
	 * \param rscName Классификатор знаков.
	 * \return Указатель на созданный слой.
	 */
	MapLayer *createLayer(QString rscName = "", QString name = "");

	/*!
	 * \brief Возвращает идентификатор открытой карты.
	 * \return Идентификатор карты.
	 */
	HMAP mapHandle() const {return mMapHandle;}

	LayersModel * layersModel() {return mLayersModel; }

	/*!
	 * \brief Возвращает текущий масштаб карты.
	 * \return Масштаб карты.
	 */
	double scale();

	QString rscDir() const {return mRscDir;}
	QString sitDir() const {return mSitDir;}

	QWidget * detachNavigation();
	void attachNavigation();

	/*!
	 * \brief Ищет объекты в заданной точке.
	 */
	QList<MapObject*> objectsAtPoint(QPoint point, double radiusPx = 10);

	HSELECT selectContext() {return mSelect;}

	QToolBar * toolBar();

public slots:
	/*!
	 * \brief Устанавливает масштаб карты.
	 * \param scale - Новое значение масштаба карты.
	 */
	void setScale(double scale);

	void setNavigationVisible(bool visible = true);

	void setCenter(QPoint pictureCoord);
	void setCenter(Coord geoCoord);
	void setCenter(CoordPlane planeCoord);

	/*!
	 * \brief Устанавливает режим редактирования карты.
	 * В зависимости от режима будут иначе обрабатываться действия мыши.
	 * \param tool
	 */
	void setCurrentTool(MapView::Tools tool) {mTool = tool;}

signals:
	/*!
	 * \brief Сигнал об изменении масштаба карты.
	 * \param scale Новое значение масштаба
	 */
	void scaleChanged(double scale);

	/*!
	 * \brief Сигнал о перемещении курсора мыши.
	 * \param coord Географические координаты точки под курсором.
	 */
	void coordChanged(Coord coord);
protected:
	bool eventFilter(QObject *obj, QEvent *e);
	void keyPressEvent(QKeyEvent *keyEvent);
	void resizeEvent(QResizeEvent *e);

private slots:
	/*!
	 * \brief Обработки прокрутки карты при помощи скроллбаров.
	 */
	void onScrollMap();

	/*!
	 * \brief Обновление диапазонов значений скроллбаров на основании полного размера карты в пикселях.
	 */
	void adjustScrollSize();

	/*!
	 * \brief Обновление значений скроллбаров на основании отображаемого участка карты.
	 */
	void adjustScrollValues();

	void adjustNavigation();

	/*!
	 * \brief Перемещает верхний левый угол отображаемого участка карты.
	 * \param pos - Новое положение верхнего левого угла отображаемого участка карты в пикселах.
	 */
	void moveMapTopLeft(QPoint pos);

private:
	/*!
	 * \brief Изменение масштаба карты при помощи колеса мыши.
	 */
	void processWheelEvent(QEvent *e);
	void processMousePressEvent(QEvent *e);
	void processMouseMoveEvent(QEvent *e);
	void processMouseReleaseEvent(QEvent *e);
	void processMouseDoubleClickEvent(QEvent *e);

	/*!
	 * \brief Возвращает полный размер карты в пикселях.
	 * \return Размер карты в пикселях.
	 */
	QSize mapSizePx() const;

	/*!
	 * \brief Прокручивает карту на указанные величины.
	 * \param dx, dy - сдвиги карты по горизонтали и вертикали.
	 */
	void scrollMapTopLeft(int dx, int dy);
	void createNavigation();

	/*!
	 * \brief Проверяет наличие директорий для классификаторов и пользовательских карт.
	 * При отсутствии указанных директорий они будут созданы.
	 * \return Признак успешности.
	 */
	bool checkDirs();

	void zoomToRect( const QRect &rect );

	QScrollBar *pHorizontalScroll;
	QScrollBar *pVerticalScroll;
	MapCanvas *pCanvas;

	MapNavigation *pNavigation; //!< Виджет навигации.
	QToolBar * pToolBar; //!< Панель инструментов карты.

	HMAP mMapHandle;
	HSELECT mSelect;
	bool mIsDragged;
	QPoint mDragStartPoint;

	LayersModel *mLayersModel; //!< Модель с перечнем слоев карты.

	quint16 mLastLayerId;

	QString mRscDir; //!< Каталог классификаторов.
	QString mSitDir; //!< Каталог пользовательских карт (слоев).

	Tools mTool; //!< Текущий инструмент карты.
};

Q_DECLARE_METATYPE(MapView::Tools)

#endif // MAPVIEW_H
