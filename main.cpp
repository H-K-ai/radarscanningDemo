#include "RadarScanning.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	RadarScanning w;
    w.resize(600,600);
   // w.showFullScreen();
    w.show();
	return a.exec();
}
