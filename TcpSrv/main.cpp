#include "tcpsrvgui.h"
#include <QApplication>

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	TcpSrvGui w;
	w.show();

	return a.exec();
}
