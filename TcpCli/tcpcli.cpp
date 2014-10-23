#include "tcpcli.h"

TcpCli::TcpCli() {}

TcpCli::~TcpCli() {

}

void TcpCli::connect(const QString& srvAddr, const quint16 srvPort) {
	tcpCli.connectToHost(QHostAddress(srvAddr), srvPort);
}

void TcpCli::disconnect() {

}

void TcpCli::transmit() {

}

const QTcpSocket* TcpCli::getClient() const {
	return &tcpCli;
}

const QString TcpCli::getAddr() const {
	return tcpCli.localAddress().toString();
}
quint16 TcpCli::getPort() const {
	return tcpCli.localPort();
}
