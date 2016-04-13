#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMap>
#include <QMainWindow>

namespace Map2
{
class MapGroup;
class MapEditor;
class MapObject;
class MapSectorObject;
}

class QPushButton;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

protected:
	virtual void showEvent(QShowEvent *e);
	virtual void closeEvent(QCloseEvent *e);

private slots:
	void onTimer();

	void onScaleChanged();
	void onEditLayers();

	void onLeftClick(QPoint point);
	void onRightClick(QPoint point);

private:
	Map2::MapEditor *pMap;
	Map2::MapObject *pObj;
};

#endif // MAINWINDOW_H
