#include "tcpcligui.h"
#include <QApplication>

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	TcpCliGui w;
	w.show();

	return a.exec();
}
