#include "QHttpResolutionTask.hpp"
#include <QTcpSocket>
#include <QUdpSocket>

QHttpResolutionTask::QHttpResolutionTask(HttpResolver* resolv, qintptr socketAddr, SocketType socketType, QObject* parent) : QObject(parent), resolver(resolv)
{
	switch (socketType) {
		case TCP: socket = new QTcpSocket(this); break;
		case UDP: socket = new QUdpSocket(this); break;
		default: socket = nullptr;
	}
	if(!socket) {
		this->deleteLater();
		return;
	}
	QObject::connect(&timer,&QTimer::timeout,socket,&QAbstractSocket::abort);
	QObject::connect(socket,&QObject::destroyed,this,&QHttpResolutionTask::onDisconnectOrTimeout);
	QObject::connect(socket,&QAbstractSocket::disconnected,this,&QHttpResolutionTask::onDisconnectOrTimeout);
	QObject::connect(socket,&QAbstractSocket::readyRead,[this](){
		QByteArray arr = socket->readAll();
		QHttpRequest req(arr);
		QHttpResponse resp;
		QIODevice* iodev;
		resolver->fillResponse(req,resp,&iodev,this);
		if(iodev) {
			resp.writeStream(*socket,*iodev);
			iodev->deleteLater();
		}
		else socket->write(resp.toBytes());
		socket->flush();
		socket->close();
	});
	socket->setSocketDescriptor(socketAddr);
	timer.start(60000);
}

void QHttpResolutionTask::onDisconnectOrTimeout()
{
	emit disconnected();
	deleteLater();
}
