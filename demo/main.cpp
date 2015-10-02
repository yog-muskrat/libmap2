#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

#if QT_VERSION >= 0x050000
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf8"));
#else
	QTextCodec::setCodecForCStrings( QTextCodec::codecForName("utf8") );
#endif

	MainWindow w;
	w.show();

	return a.exec();
}
