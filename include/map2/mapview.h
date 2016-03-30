#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QWidget>

#include "mapstructs.h"

class QLabel;
class QToolBar;
class QScrollBar;

namespace Map2
{

class MapLayer;
class MapHelper;
class MapCanvas;
class MapObject;
class MapToolBar;
class LayersModel;
class MapLineObject;

/*!
 * \brief Виджет для отображения карты
 */
class MapView : public QWidget
{
	Q_OBJECT
public:
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
	 * Если параметр key не задан, то ключ будет создан автоматически с испольованием QUUID.
	 * Если ключ задан, ноуже существует другой слой с таким же ключом, будет возвращен 0.
	 * \param rscName Классификатор знаков.
	 * \param key Ключ слоя.
	 * \param name Имя слоя.
	 * \param temp Признак временного слоя.
	 * \return Указатель на созданный слой или 0 в случае ошибки.
	 */
	Map2::MapLayer *createLayer(QString rscName = "", QString key = "", QString name = "", bool temp = false);

	/*!
	 * \brief Возвращает идентификатор открытой карты.
	 * \return Идентификатор карты.
	 */
	HMAP mapHandle() const {return mMapHandle;}

	Map2::LayersModel * layersModel() {return mLayersModel; }

	/*!
	 * \brief Возвращает текущий масштаб карты.
	 * \return Масштаб карты.
	 */
	double scale() const;

	/*!
	 * \brief Возвращает отношение масштаба отображения к базовому масштабу карты
	 */
	double scaleRatio() const;

	/*!
	 * \brief Возвращает координаты центра отображаемого участка карты.
	 */
	Map2::Coord screenCenterCoordinate();

	Map2::Coord coordinateAtPoint(const QPoint &screenCoord);

	QString rscDir() const {return mRscDir;}
	QString sitDir() const {return mSitDir;}

	/*!
	 * \brief Ищет объекты в заданной точке.
	 * \param point Координаты точки в пикселях.
	 * \param radiusPx Радиус поиска в пикселях.
	 */
	QList<Map2::MapObject*> objectsAtPoint(QPoint point, double radiusPx = 10);

	void addObjectToSelection(Map2::MapObject *obj);
	QList<Map2::MapObject*> selectedObjects(){return mSelectedObjects;}

	Map2::MapCanvas* canvas(){return pCanvas;}

	QToolBar* toolBar();

	/*!
	 * \brief Делает снимок текущего состояния карты.
	 * \param width Желаемая ширина изображения в пикселях.
	 * Высота будет расчитана пропорционально.
	 * \return
	 */
	QPixmap mapPreview(int width);

	/*!
	 * \brief Возвращает полный размер карты в пикселях.
	 * \return Размер карты в пикселях.
	 */
	QSize mapSizePx() const;

	/*!
	 * \brief Возвращает указатель на экземпляр класса-помощника, инициализированный дескриптором текущей карты.
	 */
	Map2::MapHelper* helper();

	/*!
	 * \brief Возвращает прямоугольник, соответствующий видимой области карты в пикселях
	 */
	QRect visibleRect() const;

public slots:
	/*!
	 * \brief Устанавливает масштаб карты.
	 * \param scale - Новое значение масштаба карты. При scale == -1 устанавливается базовый масштаб карты.
	 */
	void setScale(double scale = -1);

	/*!
	 * \brief Центрирует область отображения в заданной точке.
	 * \param pictureCoord Координаты точки в пикселях.
	 */
	void setCenter(QPoint pictureCoord);

	/*!
	 * \brief Перегрузка предыдущей функции.
	 * \param geoCoord Координаты точки в градусах с десятой частью.
	 */
	void setCenter(Map2::Coord geoCoord);

	/*!
	 * \brief Перегрузка предыдущей функции.
	 * \param planeCoord Координаты в метрах.
	 */
	void setCenter(Map2::CoordPlane planeCoord);

	/*!
	 * \brief Очищает список выделенных объектов и снимает с них признак выделения.
	 */
	void clearSelection();

	void setActiveLayer(Map2::MapLayer *layer);
	void setActiveLayer(int index);
	Map2::MapLayer* activeLayer();

	void zoomToRect( const QRect &rect );

	void calibrate();

	void zoomIn();

	void zoomOut();

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
	void coordChanged(Map2::Coord coord);

	void mapCenterScrolled(Map2::Coord coord);

	void mouseLeftClick(QPoint point);
	void mouseRightClick(QPoint point);

	void toolTipRequest(QPoint point, Map2::MapObject*topObject);

	void resized(QSize newSize);

	void mapLoaded();

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
	 * \brief Прокручивает карту на указанные величины.
	 * \param dx, dy - сдвиги карты по горизонтали и вертикали.
	 */
	void scrollMapTopLeft(int dx, int dy);

	/*!
	 * \brief Проверяет наличие директорий для классификаторов и пользовательских карт.
	 * При отсутствии указанных директорий они будут созданы.
	 * \return Признак успешности.
	 */
	bool checkDirs();

	QScrollBar *pHorizontalScroll;
	QScrollBar *pVerticalScroll;
	MapCanvas *pCanvas;

	MapToolBar * pTools; //!< Менеджер инструментов карты.

	HMAP mMapHandle;
	bool mIsDragged;
	QPoint mDragStartPoint;

	LayersModel *mLayersModel; //!< Модель с перечнем слоев карты.

	quint16 mLastLayerId;

	QString mRscDir; //!< Каталог классификаторов.
	QString mSitDir; //!< Каталог пользовательских карт (слоев).

	QList<MapObject*> mSelectedObjects;
	MapLayer *pActiveLayer;

	MapHelper *pHelper;
};
}
#endif // MAPVIEW_H
