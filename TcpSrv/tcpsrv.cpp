#include "tcpsrv.h"

TcpSrv::TcpSrv() : QObject() {
	QObject::connect(&tcpSrv, SIGNAL(newConnection()), this, SLOT(slAcceptConnection()));
}

TcpSrv::~TcpSrv() {
	tcpSrv.close();
	tcpConnection->close();
}

bool TcpSrv::listen() {
	return tcpSrv.listen();
}

void TcpSrv::close() {
	tcpSrv.close();
	tcpConnection->close();
}

const QString TcpSrv::getSrvAddr() const {
	return tcpSrv.serverAddress().toString();
}

quint16 TcpSrv::getSrvPort() const {
	return tcpSrv.serverPort();
}

const QString TcpSrv::getCliAddr() const {
	return tcpConnection->peerAddress().toString();
}

quint16 TcpSrv::getCliPort() const {
	return tcpConnection->peerPort();
}

const QTcpServer* TcpSrv::getServer() const {
	return &tcpSrv;
}

void TcpSrv::slAcceptConnection() {
	tcpConnection = tcpSrv.nextPendingConnection();
	tcpSrv.close();

	emit sgAccepted();
}
