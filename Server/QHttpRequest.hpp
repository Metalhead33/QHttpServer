#ifndef QHTTPREQUEST_H
#define QHTTPREQUEST_H
#include <QObject>
#include <QString>
#include <QMap>
#include <QByteArray>
#include <QIODevice>
#include <QTextStream>
#include "../Serializable/QSerializableObject.hpp"

class QHttpRequest : public QObject
{
	Q_OBJECT
private:
	QString method;
	QString path;
	QString httpVersion;
	QMap<QString,QString> headers;
	QByteArray body;
	void initialize(QTextStream& stream);
public:
	explicit QHttpRequest(QObject *parent = nullptr);
	explicit QHttpRequest(const QByteArray& input, QObject *parent = nullptr);
	explicit QHttpRequest(QIODevice& input, QObject *parent = nullptr);

	const QMap<QString, QString>& getHeaders() const;
	QMap<QString, QString>& getHeaders();
	const QString getHeader(const QString& key) const;
	void setHeader(const QString& key, const QString& value);

	const QString& getMethod() const;
	void setMethod(const QString& newMethod);

	const QString& getPath() const;
	void setPath(const QString& newPath);

	const QString& getHttpVersion() const;
	void setHttpVersion(const QString& newHttpVersion);

	const QByteArray& getBody() const;
	void setBody(const QByteArray& newBody);

	void toString(QTextStream& stream) const;
	QString toString(void) const;
	void toBytes(QIODevice& device) const;
	QByteArray toBytes(void) const;
};

#endif // QHTTPREQUEST_H
