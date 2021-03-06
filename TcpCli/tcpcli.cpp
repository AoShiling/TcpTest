#include "tcpcli.h"

TcpCli::TcpCli()
	: QObject()
{
	QObject::connect(&tcpCli, SIGNAL(connected()), this, SIGNAL(sgConnected()));
	QObject::connect(&tcpCli, SIGNAL(disconnected()), this, SIGNAL(sgDisconnected()));
}

TcpCli::~TcpCli() {

}

void TcpCli::slConnect() {
	tcpCli.connectToHost(srvAddr, srvPort);
}

void TcpCli::slDisconnect() {
	tcpCli.disconnectFromHost();
}

void TcpCli::slTransmit() {
	int bytes = tcpCli.write(data);

	if (bytes != data.size())
		emit sgTransmissionError();
	else
		emit sgTransmissionDone();
}

const QString TcpCli::getHostAddr() const {
	return tcpCli.localAddress().toString();
}

const QString TcpCli::getHostPort() const {
	return QString::number(tcpCli.localPort());
}

void TcpCli::slSetSrvAddr(const QString& addr) {
	srvAddr = QHostAddress(addr);
}

void TcpCli::slSetSrvPort(const QString& port) {
	srvPort = port.toInt();
}

void TcpCli::slSetMessage(const QString& msg) {
	data = msg.toUtf8();
}

void TcpCli::slSetRaw(const QByteArray &raw) {
	data = raw;
}
