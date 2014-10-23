#include "tcpcligui.h"

TcpCliGui::TcpCliGui(QWidget *parent)
	: QMainWindow(parent),

	  pbConnect(new QPushButton("Connect")),
	  pbDisconnect(new QPushButton("Disconnect")),
	  lbStatus(new QLabel("<status>")),

	  leAddr(new QLineEdit("<address>")),
	  lePort(new QLineEdit("<port>")),

	  lbCli(new QLabel("<addr>:<port>")),
	  sCLI("This host: "),

	  leMsg(new QLineEdit("<message>")),
	  pbTransmit(new QPushButton("Transmit"))
{
	initMembers();
	initForm();
	initConnections();
}

TcpCliGui::~TcpCliGui() {

}

void TcpCliGui::initMembers() {
	int szConns = 96;
	pbConnect->setFixedWidth(szConns);
	pbDisconnect->setFixedWidth(szConns);
	pbTransmit->setFixedWidth(szConns);

	lbStatus->setFixedWidth(szConns);

	leAddr->setFixedWidth(192);
	lePort->setFixedWidth(96);

	leMsg->setFixedWidth(192);
}

void TcpCliGui::initForm() {
	QHBoxLayout* hbxConnect = new QHBoxLayout;
	hbxConnect->addWidget(pbConnect);
	hbxConnect->addWidget(pbDisconnect);
	hbxConnect->addWidget(lbStatus);

	QHBoxLayout* hbxParams = new QHBoxLayout;
	hbxParams->addWidget(leAddr);
	hbxParams->addWidget(lePort);

	QHBoxLayout* hbxMsg = new QHBoxLayout;
	hbxMsg->addWidget(leMsg);
	hbxMsg->addWidget(pbTransmit);

	QVBoxLayout* vbxMain = new QVBoxLayout;
	vbxMain->addLayout(hbxConnect);
	vbxMain->addLayout(hbxParams);
	vbxMain->addWidget(lbCli);
	vbxMain->addLayout(hbxMsg);

	setCentralWidget(new QWidget);
	centralWidget()->setLayout(vbxMain);
	setWindowTitle("TCP Client");
}

void TcpCliGui::initConnections() {
	connect(pbConnect, SIGNAL(clicked()), this, SLOT(slConnect()));
	connect(pbDisconnect, SIGNAL(clicked()), this, SLOT(slDisconnect()));
	connect(pbTransmit, SIGNAL(clicked()), this, SLOT(slTransmit()));
	connect(tcpCli.getClient(), SIGNAL(connected()), this, SLOT(slArferConnection()));
}

void TcpCliGui::slConnect() {
	tcpCli.connect(leAddr->text(), lePort->text().toInt());
}

void TcpCliGui::slDisconnect() {
	tcpCli.disconnect();
}

void TcpCliGui::slTransmit() {
	tcpCli.transmit();
}

void TcpCliGui::slArferConnection() {
	lbStatus->setText("Connected");

	QString sAddr = tcpCli.getAddr();
	QString sPort = QString::number(tcpCli.getPort());
	lbCli->setText(sCLI + sAddr + ":" + sPort);
}
