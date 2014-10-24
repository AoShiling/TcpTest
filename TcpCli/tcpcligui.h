#ifndef TCPCLIGUI_H
#define TCPCLIGUI_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

#include "tcpcli.h"

class TcpCliGui : public QMainWindow {
	Q_OBJECT

public:
	TcpCliGui(QWidget *parent = 0);
	~TcpCliGui();

public slots:
	void slConnected();

private:
	void initMembers();
	void initForm();
	void initConnections();

	QPushButton* pbConnect;
	QPushButton* pbDisconnect;
	QLabel* lbStatus;

	QLineEdit* leAddr;
	QLineEdit* lePort;

	QLabel* lbCli;
	const QString sCLI;

	QLineEdit* leMsg;
	QPushButton* pbTransmit;

	TcpCli tcpCli;
};

#endif // TCPCLIGUI_H
