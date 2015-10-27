#ifndef MAPTOOLS_H
#define MAPTOOLS_H

#include <QMap>
#include <QPoint>
#include <QObject>
#include <QElapsedTimer>

class MapView;
class QAction;
class QToolBar;
class MapLayer;
class MapRuler;
class MapObject;
class QMouseEvent;

class MapTools : public QObject
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

	explicit MapTools(MapView *view);
	~MapTools();

	QToolBar * toolBar();

	bool processMousePressEvent(QMouseEvent *mouseEvent);
	bool processMouseMoveEvent(QMouseEvent *mouseEvent);
	bool processMouseReleaseEvent(QMouseEvent *mouseEvent);
	bool processMouseDoubleClickEvent(QMouseEvent *mouseEvent);

private slots:
	void onActionTriggered(QAction *act);

private:
	void setCurrentTool(MapTools::Tools tool);
	QAction* addActionWithData( QAction *act, QVariant data);

	MapView *pView;
	QToolBar *pToolBar;
	Tools mTool;
	QMap<QString, MapLayer*> mTempSites;
	MapRuler *pRuler;
	MapObject *pTempObject;
	bool mIsDragged;
	QPoint mDragStartPoint;
	QElapsedTimer mClickTi;
};
Q_DECLARE_METATYPE(MapTools::Tools)

#endif // MAPTOOLS_H
