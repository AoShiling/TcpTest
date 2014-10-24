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
	connect(pbConnect, SIGNAL(clicked()), &tcpCli, SLOT(slConnect()));
	connect(pbDisconnect, SIGNAL(clicked()), &tcpCli, SLOT(slDisconnect()));
	connect(pbTransmit, SIGNAL(clicked()), &tcpCli, SLOT(slTransmit()));

	connect(&tcpCli, SIGNAL(connected()), this, SLOT(slConnected()));
	connect(leAddr, SIGNAL(textEdited(QString)), &tcpCli, SLOT(slSetSrvAddr(QString)));
	connect(lePort, SIGNAL(textEdited(QString)), &tcpCli, SLOT(slSetSrvPort(QString)));
}

void TcpCliGui::slConnected() {
	lbStatus->setText("Connected");
	lbCli->setText(sCLI + tcpCli.getHostAddr() + ":" + tcpCli.getHostPort());
}
