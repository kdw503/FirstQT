#include "firstqt.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FirstQT w1;
	w1.show();
	return a.exec();
}
