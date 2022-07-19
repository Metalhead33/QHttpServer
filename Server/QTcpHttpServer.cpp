#include "QTcpHttpServer.hpp"
#include <QTcpSocket>
#include "QHttpRequest.hpp"
#include "QHttpResolutionTask.hpp"

HttpResolver* QTcpHttpServer::getResolver() const
{
	return resolver;
}

void QTcpHttpServer::setResolver(HttpResolver* newResolver)
{
	resolver = newResolver;
}

QTcpHttpServer::QTcpHttpServer(QObject* parent) : QTcpServer(parent)
{

}

QTcpHttpServer::QTcpHttpServer(HttpResolver* resolver, QObject* parent) : QTcpServer(parent), resolver(resolver)
{

}

QTcpHttpServer::~QTcpHttpServer()
{

}

void QTcpHttpServer::incomingConnection(qintptr socketDescriptor)
{
	QHttpResolutionTask* task = new QHttpResolutionTask(resolver,socketDescriptor,QHttpResolutionTask::TCP, this);
}
