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
	int szLstn = 96;
	pbListen->setFixedWidth(szLstn);
	pbClose->setFixedWidth(szLstn);
	lbStatus->setFixedWidth(szLstn);
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

	connect(&tcpSrv, SIGNAL(sgListen()), this, SLOT(slListen()));
	connect(&tcpSrv, SIGNAL(sgAccepted()), this, SLOT(slAccepted()));
	connect(&tcpSrv, SIGNAL(sgNotListen()), this, SLOT(slError()));
	connect(&tcpSrv, SIGNAL(sgNotAccepted()), this, SLOT(slError()));
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
