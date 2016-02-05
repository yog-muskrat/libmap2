#ifndef MAPTOOLBAR_H
#define MAPTOOLBAR_H

#include <QMap>
#include <QPoint>
#include <QObject>
#include <QVariant>
#include <QElapsedTimer>

class QAction;
class QToolBar;
class QMouseEvent;

namespace Map2
{
class MapView;
class MapLayer;
class MapRuler;
class MapAction;
class MapObject;

class MapToolBar : public QObject
{
	Q_OBJECT
public:
	/*!
	 * \brief Инструменты карты
	 */
	enum Tools
	{
		None, //!< Инструмент не выбран.
		MoveObject, //!< Перемещение объекта.
		DeleteObject, //!< Удаление объекта.
		AddVectorObject, //!< Добавление векторного объекта.
		AddZoneObject, //!< Добавление зоны.
		AddLineObject, //!< Добавление линии.
		RotateObject, //!< Вращение объекта. Только для векторных объектов.
		Ruler, //!< Измерение расстояний.
		RectZoom //!< Приблизить область.
	};

	explicit MapToolBar(Map2::MapView *view);
	~MapToolBar();

	QToolBar * toolBar();

	bool processMousePressEvent(QMouseEvent *mouseEvent);
	bool processMouseMoveEvent(QMouseEvent *mouseEvent);
	bool processMouseReleaseEvent(QMouseEvent *mouseEvent);
	bool processMouseDoubleClickEvent(QMouseEvent *mouseEvent);

signals:
	void rightClick(QPoint point);
	void leftClick(QPoint point);

private slots:
	void onActionTriggered(QAction *act);

private:
	void setCurrentTool(MapToolBar::Tools tool);
	QAction* addActionWithData( QAction *act, QVariant data);

	MapView *pView;
	QToolBar *pToolBar;
	Tools mCurrentTool;
	QMap<MapToolBar::Tools, MapAction*> mActions;

	bool mLeftBtnPressed;
	bool mRightBtnPressed;
	QElapsedTimer mLeftClickTi;
	QElapsedTimer mRightClickTi;

	static const int mClickInterval = 300;
};
}
Q_DECLARE_METATYPE(Map2::MapToolBar::Tools)

#endif // MAPTOOLBAR_H
