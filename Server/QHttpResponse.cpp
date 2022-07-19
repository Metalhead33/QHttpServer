#include "QHttpResponse.hpp"
#include <QBuffer>

const QMap<QString, QString>& QHttpResponse::getHeaders() const
{
	return headers;
}

QMap<QString, QString>& QHttpResponse::getHeaders()
{
	return headers;
}

const QString QHttpResponse::getHeader(const QString& key) const
{
	return headers[key];
}

void QHttpResponse::setHeader(const QString& key, const QString& value)
{
	headers.insert(key,value);
}

const QString& QHttpResponse::getHttpVersion() const
{
	return httpVersion;
}

void QHttpResponse::setHttpVersion(const QString& newHttpVersion)
{
	httpVersion = newHttpVersion;
}

const QByteArray& QHttpResponse::getBody() const
{
	return body;
}

void QHttpResponse::setBody(const QByteArray& newBody)
{
	body = newBody;
}

void QHttpResponse::toString(QTextStream& stream, bool writeBody) const
{
	stream << httpVersion << ' ' << statusCode << ' ' << status << "\r\n";
	for(auto it = std::begin(headers); it != std::end(headers); ++it)
	{
		stream << it.key() << ": " << it.value() << "\r\n";
	}
	stream << "\r\n";
	if(writeBody) stream << QString::fromUtf8(body);
	stream.flush();
}

QString QHttpResponse::toString(bool writeBody) const
{
	QString tmp;
	QTextStream stream(&tmp, QIODevice::WriteOnly);
	toString(stream,writeBody);
	return tmp;
}

void QHttpResponse::toBytes(QIODevice& device, bool writeBody) const
{
	QTextStream stream(&device);
	stream << httpVersion << ' ' << statusCode << ' ' << status << "\r\n";
	for(auto it = std::begin(headers); it != std::end(headers); ++it)
	{
		stream << it.key() << ": " << it.value() << "\r\n";
	}
	stream << "\r\n";
	stream.flush();
	device.write(body);
}

QByteArray QHttpResponse::toBytes(bool writeBody) const
{
	QByteArray tmp;
	tmp.reserve(8192);
	QBuffer buffer(&tmp);
	buffer.open(QBuffer::ReadWrite);
	toBytes(buffer,writeBody);
	buffer.close();
	return tmp;
}

void QHttpResponse::writeStream(QIODevice& device, QIODevice& inDevice) const
{
	{
		QByteArray header;
		header.reserve(8192);
		QBuffer buffer(&header);
		buffer.open(QBuffer::ReadWrite);
		toBytes(buffer,false);
		buffer.close();
		device.write(header);
	}
	QByteArray tmp(0xFFFF,0);
	qint64 readAmount = 0;
	do {
		readAmount = inDevice.read(tmp.data(),0xFFFF);
		device.write(tmp.data(),readAmount);
	} while(readAmount);
}

int QHttpResponse::getStatusCode() const
{
	return statusCode;
}

void QHttpResponse::setStatusCode(int newStatusCode)
{
	statusCode = newStatusCode;
}

const QString& QHttpResponse::getStatus() const
{
	return status;
}

void QHttpResponse::setStatus(const QString& newStatus)
{
	status = newStatus;
}

void QHttpResponse::initialize(QTextStream& stream)
{
	QIODevice* input = stream.device();
	QString tmpStr;
	stream.readLineInto(&tmpStr);
	QStringList headerStart = tmpStr.split(' ');
	if(headerStart.size() >= 1) this->httpVersion = headerStart[0];
	if(headerStart.size() >= 3) {
		this->statusCode = headerStart[1].toInt();
		this->status = headerStart[2];
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

QHttpResponse::QHttpResponse(QObject *parent) : QObject(parent), statusCode(404)
{

}

QHttpResponse::QHttpResponse(const QByteArray& input, QObject* parent) : QObject(parent)
{
	QTextStream stream(input);
	initialize(stream);
}

QHttpResponse::QHttpResponse(QIODevice& input, QObject* parent) : QObject(parent)
{
	QTextStream stream(&input);
	initialize(stream);
}
