#ifndef TCPCLI_H
#define TCPCLI_H

#include <QTcpSocket>
#include <QHostAddress>
#include <QObject>

class TcpCli {
public:
	TcpCli();
	~TcpCli();

	void connect(const QString& srvAddr, const quint16 srvPort);
	void disconnect();
	void transmit();

	const QTcpSocket* getClient() const;

	const QString getAddr() const;
	quint16 getPort() const;

private:
	QTcpSocket tcpCli;
};

#endif // TCPCLI_H
