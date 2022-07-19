#ifndef QTCPHTTPSERVER_H
#define QTCPHTTPSERVER_H
#include <QTcpServer>
#include "HttpResolver.hpp"

class QTcpHttpServer : public QTcpServer
{
	Q_OBJECT
private:
	HttpResolver* resolver;
public:
	QTcpHttpServer(QObject *parent = nullptr);
	QTcpHttpServer(HttpResolver* resolver, QObject *parent = nullptr);
	virtual ~QTcpHttpServer() override;
	void incomingConnection(qintptr socketDescriptor) override;
	HttpResolver* getResolver() const;
	void setResolver(HttpResolver* newResolver);
};

#endif // QTCPHTTPSERVER_H
