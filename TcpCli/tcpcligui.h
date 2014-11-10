#ifndef TCPCLIGUI_H
#define TCPCLIGUI_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QMessageBox>

#include "tcpcli.h"

class TcpCliGui : public QMainWindow {
	Q_OBJECT

public:
	TcpCliGui(QWidget *parent = 0);
	~TcpCliGui();

public slots:
	void slConnected();
	void slDisconnected();

	void slTransmissionError();

private:
	void initMembers();
	void initForm();
	void initConnections();

	const QString sCLI;
	const QString sCLIAP;
	const QString sADDR;
	const QString sPORT;
	const QString sFILE;

	QPushButton* pbConnect;
	QPushButton* pbDisconnect;
	QLabel* lbStatus;

	QLabel* lbServer;
	QLineEdit* leAddr;
	QLineEdit* lePort;

	QLabel* lbCli;

	QLineEdit* leMsg;
	QPushButton* pbTransmit;

	QLabel* lbFile;
	QPushButton* pbFile;

	TcpCli tcpCli;
};

#endif // TCPCLIGUI_H
