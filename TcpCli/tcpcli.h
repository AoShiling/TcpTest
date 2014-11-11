#ifndef TCPCLI_H
#define TCPCLI_H

#include <QTcpSocket>
#include <QHostAddress>
#include <QObject>

class TcpCli : public QObject {
	Q_OBJECT

public:
	TcpCli();
	~TcpCli();

	const QString getHostAddr() const;
	const QString getHostPort() const;

public slots:
	void slConnect();
	void slDisconnect();
	void slTransmit();

	void slSetSrvAddr(const QString& addr);
	void slSetSrvPort(const QString& port);
	void slSetMessage(const QString& msg);
	void slSetRaw(const QByteArray& raw);

signals:
	void sgConnected();
	void sgDisconnected();
	void sgTransmissionError();
	void sgTransmissionDone();

private:
	QTcpSocket tcpCli;
	QHostAddress srvAddr;
	quint16 srvPort;

	QByteArray data;
};

#endif // TCPCLI_H
