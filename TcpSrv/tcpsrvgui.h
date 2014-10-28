#ifndef TCPSRVGUI_H
#define TCPSRVGUI_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

#include "tcpsrv.h"

class TcpSrvGui : public QMainWindow {
	Q_OBJECT

public:
	TcpSrvGui(QWidget *parent = 0);
	~TcpSrvGui();

public slots:
	void slListen();
	void slAccepted();
	void slError();
	void slDisconnect();

private:
	void initMembers();
	void initForm();
	void initConnections();

	const QString sMSG;
	const QString sSRV;
	const QString sCLI;
	const QString sBTS;

	QPushButton* pbListen;
	QPushButton* pbClose;
	QLabel* lbStatus;

	QLabel* lbMessage;
	QLabel* lbSrv;
	QLabel* lbCli;
	QLabel* lbBytes;

	TcpSrv tcpSrv;
};

#endif // TCPSRVGUI_H
