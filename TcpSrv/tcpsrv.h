#ifndef TCPSRV_H
#define TCPSRV_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>

class TcpSrv : public QObject {
	Q_OBJECT

public:
	TcpSrv();
	~TcpSrv();

	const QString getSrvAddr() const;
	const QString getSrvPort() const;

	const QString getCliAddr() const;
	const QString getCliPort() const;

public slots:
	void slAcceptConnection();
	void slReadFromSocket();

	void slListen();
	void slClose();

signals:
	void sgAccepted();
	void sgListen();
	void sgNotAccepted();
	void sgNotListen();
	void sgDisconnected();
	void sgRecvData(const QByteArray& data, const int bytes);

private:
	QTcpServer tcpSrv;
	QTcpSocket* tcpConnection;

	QByteArray data;
	int bytes;
};

#endif // TCPSRV_H
