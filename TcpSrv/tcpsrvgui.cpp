#include "tcpsrvgui.h"

TcpSrvGui::TcpSrvGui(QWidget *parent)
	: QMainWindow(parent),

	  sMSG("Message: "),
	  sSRV("srv: "),
	  sCLI("cli: "),
	  sBTS("Total bytes: "),

	  pbListen(new QPushButton("Listen")),
	  pbClose(new QPushButton("Close")),
	  lbStatus(new QLabel("<status>")),

	  lbMessage(new QLabel(sMSG)),
	  lbSrv(new QLabel(sSRV + "<addr>:<port>")),
	  lbCli(new QLabel(sCLI + "<addr>:<port>")),
	  lbBytes(new QLabel(sBTS + "0"))
{
	initMembers();
	initForm();
	initConnections();
}

TcpSrvGui::~TcpSrvGui() {

}

void TcpSrvGui::initMembers() {
	int szPushButton = 96;
	pbListen->setFixedWidth(szPushButton);
	pbClose->setFixedWidth(szPushButton);

	int szLabel = 128;
	lbStatus->setFixedWidth(szLabel);
}

void TcpSrvGui::initForm() {
	QHBoxLayout* hbxListen = new QHBoxLayout;
	hbxListen->addWidget(pbListen);
	hbxListen->addWidget(pbClose);
	hbxListen->addWidget(lbStatus);

	QVBoxLayout* vbxMain = new QVBoxLayout;
	vbxMain->addLayout(hbxListen);
	vbxMain->addWidget(lbSrv);
	vbxMain->addWidget(lbCli);
	vbxMain->addWidget(lbMessage);
	vbxMain->addWidget(lbBytes);

	setCentralWidget(new QWidget);
	centralWidget()->setLayout(vbxMain);
	setWindowTitle("TCP Server");
}

void TcpSrvGui::initConnections() {
	connect(pbListen, SIGNAL(clicked()), &tcpSrv, SLOT(slListen()));
	connect(pbClose, SIGNAL(clicked()), &tcpSrv, SLOT(slClose()));
	connect(pbClose, SIGNAL(clicked()), this, SLOT(slClosed()));

	connect(&tcpSrv, SIGNAL(sgListen()), this, SLOT(slListen()));
	connect(&tcpSrv, SIGNAL(sgAccepted()), this, SLOT(slAccepted()));
	connect(&tcpSrv, SIGNAL(sgNotListen()), this, SLOT(slError()));
	connect(&tcpSrv, SIGNAL(sgNotAccepted()), this, SLOT(slError()));
	connect(&tcpSrv, SIGNAL(sgDisconnected()), this, SLOT(slDisconnect()));
	connect(&tcpSrv, SIGNAL(sgRecvData(QByteArray,int)), this, SLOT(slGotData(QByteArray,int)));
}

void TcpSrvGui::slListen() {
	lbStatus->setText("Listening");

	QString sSrvAddr = tcpSrv.getSrvAddr();
	QString sSrvPort = tcpSrv.getSrvPort();
	lbSrv->setText(sSRV + sSrvAddr + ":" + sSrvPort);
}

void TcpSrvGui::slAccepted() {
	lbStatus->setText("Accepted");

	QString sCliAddr = tcpSrv.getCliAddr();
	QString sCliPort = tcpSrv.getCliPort();
	lbCli->setText(sCLI + sCliAddr + ":" + sCliPort);
}

void TcpSrvGui::slError() {
	QMessageBox::critical(this, "Error", "Some shit happened.");
}

void TcpSrvGui::slDisconnect() {
	lbStatus->setText("Host disconnected\nServer closed");
	lbSrv->setText(sSRV);
	lbCli->setText(sCLI);
}

void TcpSrvGui::slClosed() {
	lbStatus->setText("Server closed");
	lbSrv->setText(sSRV);
	lbCli->setText(sCLI);
}

void TcpSrvGui::slGotData(const QByteArray& data, const int bytes) {
	lbMessage->setText(sMSG + QString(data));
	lbBytes->setText(sBTS + QString::number(bytes));
}
