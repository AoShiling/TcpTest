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

	bool listen();
	void close();

	const QString getSrvAddr() const;
	quint16 getSrvPort() const;

	const QString getCliAddr() const;
	quint16 getCliPort() const;

	const QTcpServer* getServer() const;

public slots:
	void slAcceptConnection();

signals:
	void sgAccepted();

private:
	QTcpServer tcpSrv;
	QTcpSocket* tcpConnection;

	int bytes;
};

#endif // TCPSRV_H
