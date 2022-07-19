#ifndef QUDPHTTPSERVER_HPP
#define QUDPHTTPSERVER_HPP
#include <QUdpSocket>
#include "HttpResolver.hpp"

class QUdpHttpServer : public QObject
{
	Q_OBJECT
private:
	HttpResolver* resolver;
	QUdpSocket socket;
public:
	QUdpHttpServer(QObject *parent = nullptr);
	explicit QUdpHttpServer(HttpResolver* resolver, QObject *parent = nullptr);
	HttpResolver* getResolver() const;
	void setResolver(HttpResolver* newResolver);
	const QUdpSocket& getSocket() const;
	QUdpSocket& getSocket();
public slots:
	void readPendingDatagrams();
};

#endif // QUDPHTTPSERVER_HPP
