#ifndef QHTTPRESPONSE_H
#define QHTTPRESPONSE_H
#include <QObject>
#include <QString>
#include <QMap>
#include <QByteArray>
#include <QIODevice>
#include <QTextStream>

class QHttpResponse : public QObject
{
private:
	QString httpVersion;
	int statusCode;
	QString status;
	QMap<QString,QString> headers;
	QByteArray body;
	void initialize(QTextStream& stream);
public:
	explicit QHttpResponse(QObject *parent = nullptr);
	explicit QHttpResponse(const QByteArray& input, QObject *parent = nullptr);
	explicit QHttpResponse(QIODevice& input, QObject *parent = nullptr);

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

	void toString(QTextStream& stream, bool writeBody = true) const;
	QString toString(bool writeBody = true) const;
	void toBytes(QIODevice& device, bool writeBody = true) const;
	QByteArray toBytes(bool writeBody = true) const;
	void writeStream(QIODevice& device, QIODevice& inDevice) const;
	int getStatusCode() const;
	void setStatusCode(int newStatusCode);
	const QString& getStatus() const;
	void setStatus(const QString& newStatus);
};

#endif // QHTTPRESPONSE_H
