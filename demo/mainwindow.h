#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "map2/structs.h"

namespace Ui {
class MainWindow;
}

class QLabel;
class MapView;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void onScaleChanged(double scale);
	void onCoordChanged(Coord coord);

	void on_pbAddLayer_clicked();

	void on_pbRemoveLayer_clicked();

	void on_layersTable_clicked(const QModelIndex &index);

	void on_pbAddObject_clicked();

	void on_pbRemoveObject_clicked();

private:
	Ui::MainWindow *ui;
	QLabel *pScaleLabel;
	QLabel *pCoordLabel;

	MapView *pView;
};

#endif // MAINWINDOW_H
