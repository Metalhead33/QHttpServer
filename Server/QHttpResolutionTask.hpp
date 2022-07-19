#ifndef QHTTPRESOLUTIONTASK_HPP
#define QHTTPRESOLUTIONTASK_HPP
#include <QObject>
#include <QAbstractSocket>
#include <QTimer>
#include "HttpResolver.hpp"

class QHttpResolutionTask : public QObject
{
	Q_OBJECT
private:
	HttpResolver* resolver;
	QAbstractSocket* socket;
	QTimer timer;
public:
	enum SocketType {
		TCP,
		UDP
	};
	QHttpResolutionTask(HttpResolver* resolv, qintptr socketAddr, SocketType socketType, QObject* parent = nullptr);
public slots:
	void onDisconnectOrTimeout();
signals:
	void disconnected();
};

#endif // QHTTPRESOLUTIONTASK_HPP
