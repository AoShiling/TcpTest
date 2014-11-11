#include "tcpcligui.h"

TcpCliGui::TcpCliGui(QWidget *parent)
	: QMainWindow(parent),

	  sCLI("This host: "),
	  sCLIAP("<addr>:<port>"),
	  sADDR("<server address>"),
	  sPORT("<server port>"),
	  sFILE("File: "),

	  pbConnect(new QPushButton("Connect")),
	  pbDisconnect(new QPushButton("Disconnect")),
	  lbStatus(new QLabel("<status>")),

	  lbServer(new QLabel("Server:")),
	  leAddr(new QLineEdit(sADDR)),
	  lePort(new QLineEdit(sPORT)),

	  lbCli(new QLabel(sCLI + sCLIAP)),

	  leMsg(new QLineEdit("<message>")),
	  pbTransmit(new QPushButton("Transmit")),

	  lbFile(new QLabel(sFILE + "<path for send>")),
	  pbFile(new QPushButton("File")),
	  sFile("")
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
	pbFile->setFixedWidth(szConns);

	lbStatus->setFixedWidth(szConns);

	leAddr->setFixedWidth(192);
	lePort->setFixedWidth(96);

	leMsg->setFixedWidth(192);
	lbFile->setFixedWidth(192);
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

	QHBoxLayout* hbxFile = new QHBoxLayout;
	hbxFile->addWidget(lbFile);
	hbxFile->addWidget(pbFile);

	QVBoxLayout* vbxMain = new QVBoxLayout;
	vbxMain->addLayout(hbxConnect);
	vbxMain->addWidget(lbServer);
	vbxMain->addLayout(hbxParams);
	vbxMain->addWidget(lbCli);
	vbxMain->addLayout(hbxMsg);
	vbxMain->addLayout(hbxFile);

	setCentralWidget(new QWidget);
	centralWidget()->setLayout(vbxMain);
	setWindowTitle("TCP Client");
}

void TcpCliGui::initConnections() {
	connect(pbConnect, SIGNAL(clicked()), &tcpCli, SLOT(slConnect()));
	connect(pbDisconnect, SIGNAL(clicked()), &tcpCli, SLOT(slDisconnect()));
	connect(pbTransmit, SIGNAL(clicked()), &tcpCli, SLOT(slTransmit()));
	connect(pbFile, SIGNAL(clicked()), this, SLOT(slFileSend()));

	connect(&tcpCli, SIGNAL(sgConnected()), this, SLOT(slConnected()));
	connect(&tcpCli, SIGNAL(sgDisconnected()), this, SLOT(slDisconnected()));
	connect(&tcpCli, SIGNAL(sgTransmissionError()), this, SLOT(slTransmissionError()));
	connect(&tcpCli, SIGNAL(sgTransmissionDone()), this, SLOT(slTransmissionDone()));

	connect(leAddr, SIGNAL(textEdited(QString)), &tcpCli, SLOT(slSetSrvAddr(QString)));
	connect(lePort, SIGNAL(textEdited(QString)), &tcpCli, SLOT(slSetSrvPort(QString)));
	connect(leMsg, SIGNAL(textEdited(QString)), &tcpCli, SLOT(slSetMessage(QString)));
}

void TcpCliGui::slConnected() {
	lbStatus->setText("Connected");
	lbCli->setText(sCLI + tcpCli.getHostAddr() + ":" + tcpCli.getHostPort());
}

void TcpCliGui::slDisconnected() {
	lbStatus->setText("Disconnected");
	lbCli->setText(sCLI + sCLIAP);
	leAddr->setText(sADDR);
	lePort->setText(sPORT);
}

void TcpCliGui::slFileSend() {
	sFile = QFileDialog::getOpenFileName(this, "Send file", sFile);

	if (sFile.isEmpty())
		return;

	const int pos = 22;
	if (sFile.size() > pos)
		lbFile->setText(sFILE + sFile.left(pos) + "...");
	else
		lbFile->setText(sFILE + sFile);

	QFile file(sFile);
	const QByteArray& data = file.readAll();

	if (data.isEmpty())
		return;

	tcpCli.slSetRaw(data);
	tcpCli.slTransmit();
}

void TcpCliGui::slTransmissionError() {
	QMessageBox::critical(this, "Transmission error", "Message is not entire");
}

void TcpCliGui::slTransmissionDone() {
	QMessageBox::about(this, "Transmission done", "Message transmitted");
}
