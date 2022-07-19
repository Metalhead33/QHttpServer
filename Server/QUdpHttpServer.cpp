#include "QUdpHttpServer.hpp"
#include <QNetworkDatagram>

const QUdpSocket& QUdpHttpServer::getSocket() const
{
	return socket;
}

QUdpSocket& QUdpHttpServer::getSocket()
{
	return socket;
}

void QUdpHttpServer::readPendingDatagrams()
{
	while (socket.hasPendingDatagrams()) {
		QNetworkDatagram datagram = socket.receiveDatagram();
		QHttpRequest req(datagram.data());
		QHttpResponse resp;
		resolver->fillResponse(req,resp,nullptr);
		socket.writeDatagram(resp.toBytes(),datagram.senderAddress(),datagram.senderPort());
	}
}

QUdpHttpServer::QUdpHttpServer(QObject* parent) : QObject(parent), resolver(nullptr)
{
	connect(&socket, &QUdpSocket::readyRead, this, &QUdpHttpServer::readPendingDatagrams);
}

QUdpHttpServer::QUdpHttpServer(HttpResolver* resolver, QObject* parent) : QObject(parent), resolver(resolver)
{
	connect(&socket, &QUdpSocket::readyRead, this, &QUdpHttpServer::readPendingDatagrams);
}

HttpResolver* QUdpHttpServer::getResolver() const
{
	return resolver;
}

void QUdpHttpServer::setResolver(HttpResolver* newResolver)
{
	resolver = newResolver;
}
