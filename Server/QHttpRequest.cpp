#include "QHttpRequest.hpp"
#include <QBuffer>

const QMap<QString, QString>& QHttpRequest::getHeaders() const
{
	return headers;
}

QMap<QString, QString>& QHttpRequest::getHeaders()
{
	return headers;
}

const QString QHttpRequest::getHeader(const QString& key) const
{
	return headers[key];
}

void QHttpRequest::setHeader(const QString& key, const QString& value)
{
	headers.insert(key,value);
}

const QString& QHttpRequest::getMethod() const
{
	return method;
}

void QHttpRequest::setMethod(const QString& newMethod)
{
	method = newMethod;
}

const QString& QHttpRequest::getPath() const
{
	return path;
}

void QHttpRequest::setPath(const QString& newPath)
{
	path = newPath;
}

const QString& QHttpRequest::getHttpVersion() const
{
	return httpVersion;
}

void QHttpRequest::setHttpVersion(const QString& newHttpVersion)
{
	httpVersion = newHttpVersion;
}

const QByteArray& QHttpRequest::getBody() const
{
	return body;
}

void QHttpRequest::setBody(const QByteArray& newBody)
{
	body = newBody;
}

void QHttpRequest::toString(QTextStream& stream) const
{
	stream << method << ' ' << path << ' ' << httpVersion << "\r\n";
	for(auto it = std::begin(headers); it != std::end(headers); ++it)
	{
		stream << it.key() << ": " << it.value() << "\r\n";
	}
	stream << "\r\n" << QString::fromUtf8(body);
	stream.flush();
}

QString QHttpRequest::toString() const
{
	QString tmp;
	QTextStream stream(&tmp, QIODevice::WriteOnly);
	toString(stream);
	return tmp;
}

void QHttpRequest::toBytes(QIODevice& device) const
{
	QTextStream stream(&device);
	stream << method << ' ' << path << ' ' << httpVersion << "\r\n";
	for(auto it = std::begin(headers); it != std::end(headers); ++it)
	{
		stream << it.key() << ": " << it.value() << "\r\n";
	}
	stream << "\r\n";
	stream.flush();
	device.write(body);
}

QByteArray QHttpRequest::toBytes() const
{
	QByteArray tmp;
	QBuffer buffer(&tmp);
	buffer.open(QBuffer::ReadWrite);
	toBytes(buffer);
	buffer.close();
	return tmp;
}

void QHttpRequest::initialize(QTextStream& stream)
{
	QIODevice* input = stream.device();
	QString tmpStr;
	stream.readLineInto(&tmpStr);
	QStringList headerStart = tmpStr.split(' ');
	if(headerStart.size() >= 1) this->method = headerStart[0];
	if(headerStart.size() >= 3) {
		this->path = headerStart[1];
		this->httpVersion = headerStart[2];
	} else if(headerStart.size() == 2) {
		this->httpVersion = headerStart[1];
	}
	qint64 currentIndex = 0;
	while(stream.readLineInto(&tmpStr)) {
		if(tmpStr.isEmpty()) break;
		qsizetype index = tmpStr.indexOf(QStringLiteral(": "));
		if(index == -1) break;
		QString key = tmpStr.left(index);
		QString value = tmpStr.mid(index+2);
		if(!key.isEmpty() && !value.isEmpty()) {
			headers.insert(key,value);
			currentIndex = stream.pos();
		}
	}
	input->seek(currentIndex+2);
	this->body = input->readAll();
}

QHttpRequest::QHttpRequest(QObject *parent) : QObject(parent)
{

}

QHttpRequest::QHttpRequest(const QByteArray& input, QObject* parent) : QObject(parent)
{
	QTextStream stream(input);
	initialize(stream);
}

QHttpRequest::QHttpRequest(QIODevice& input, QObject* parent) : QObject(parent)
{
	QTextStream stream(&input);
	initialize(stream);
}
