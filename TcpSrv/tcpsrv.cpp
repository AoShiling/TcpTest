#include "tcpsrv.h"

TcpSrv::TcpSrv()
	: QObject(),
	  tcpConnection(nullptr),
	  bytes(0)
{
	QObject::connect(&tcpSrv, SIGNAL(newConnection()), this, SLOT(slAcceptConnection()));
//	QObject::connect(&tcpSrv, SIGNAL(acceptError()), this, SIGNAL(sgNotAccepted()));
}

TcpSrv::~TcpSrv() {
	tcpSrv.close();

	if (tcpConnection != nullptr)
		tcpConnection->close();
}

void TcpSrv::slListen() {
	if (tcpSrv.listen())
		emit sgListen();
	else
		emit sgNotListen();
}

void TcpSrv::slClose() {
	tcpSrv.close();

	if (tcpConnection != nullptr)
		tcpConnection->close();
}

const QString TcpSrv::getSrvAddr() const {
	return tcpSrv.serverAddress().toString();
}

const QString TcpSrv::getSrvPort() const {
	return QString::number(tcpSrv.serverPort());
}

const QString TcpSrv::getCliAddr() const {
	return tcpConnection->peerAddress().toString();
}

const QString TcpSrv::getCliPort() const {
	return QString::number(tcpConnection->peerPort());
}

void TcpSrv::slAcceptConnection() {
	tcpConnection = tcpSrv.nextPendingConnection();
	QObject::connect(tcpConnection, SIGNAL(disconnected()), this, SIGNAL(sgDisconnected()));
	QObject::connect(tcpConnection, SIGNAL(readyRead()), this, SLOT(slReadFromSocket()));

	tcpSrv.close();

	emit sgAccepted();
}

void TcpSrv::slReadFromSocket() {
	data = tcpConnection->readAll();
	bytes += data.size();

	emit sgRecvData(data, bytes);
}
