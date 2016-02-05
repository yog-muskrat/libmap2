#include "mainwindow.h"
#include <QTextCodec>
#include <QApplication>

int main(int argc, char *argv[])
{
	QTextCodec::setCodecForCStrings( QTextCodec::codecForName("utf-8"));

	QApplication a(argc, argv);
	MainWindow w;
	w.show();

	return a.exec();
}
