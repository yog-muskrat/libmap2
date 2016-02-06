#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMap>
#include <QMainWindow>

namespace Map2
{
class MapGroup;
class MapEditor;
class MapObject;
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
	void toggleObj(bool visible);
	void toggleGroup(bool visible);
	void onScaleChanged();

private:
	Map2::MapEditor *pMap;
	QMap<QPushButton *, Map2::MapObject*> mObjButtons;
	Map2::MapGroup *pStackGroup;
	Map2::MapGroup *pFormGroup;
};

#endif // MAINWINDOW_H
