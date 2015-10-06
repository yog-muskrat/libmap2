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
class MapLineObject;
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
	 * \param point Координаты точки в пикселях.
	 * \param radiusPx Радиус поиска в пикселях.
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

	/*!
	 * \brief Центрирует область отображения в заданной точке.
	 * \param pictureCoord Координаты точки в пикселях.
	 */
	void setCenter(QPoint pictureCoord);

	/*!
	 * \brief Перегрузка предыдущей функции.
	 * \param geoCoord Координаты точки в градусах с десятой частью.
	 */
	void setCenter(Coord geoCoord);

	/*!
	 * \brief Перегрузка предыдущей функции.
	 * \param planeCoord Координаты в метрах.
	 */
	void setCenter(CoordPlane planeCoord);

	/*!
	 * \brief Устанавливает режим редактирования карты.
	 * В зависимости от режима будут иначе обрабатываться действия мыши.
	 * \param tool
	 */
	void setCurrentTool(MapView::Tools tool);

	/*!
	 * \brief Очищает список выделенных объектов и снимает с них признак выделения.
	 */
	void clearSelection();


//	void setActiveLayer(MapLayer *layer);
//	void setActiveLayer(int index);

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
	 * \brief Обработка прокрутки колесика мыши над областью отображения карты.
	 */
	void processWheelEvent(QEvent *e);

	/*!
	 * \brief Обработка нажатия кнопки мыши над областью отображения карты.
	 */
	void processMousePressEvent(QEvent *e);

	/*!
	 * \brief Обработка перемещения мыши над областью отображения карты.
	 */
	void processMouseMoveEvent(QEvent *e);

	/*!
	 * \brief Обработка отжатия кнопки мыши над областью отображения карты.
	 */
	void processMouseReleaseEvent(QEvent *e);

	/*!
	 * \brief Обработка двойного щелчка мыши над областью отображения карты.
	 */
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

	QMap<QString, MapLayer*> mTempSites;

	QList<MapObject*> mSelectedObjects;

	MapLineObject *pRuler;
};

Q_DECLARE_METATYPE(MapView::Tools)

#endif // MAPVIEW_H
