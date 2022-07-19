#include "QSerializableArray.hpp"

QJsonArray QSerializableArray::toJsonArray() const
{
	QJsonArray tmp;
	toJsonArray(tmp);
	return tmp;
}

QCborArray QSerializableArray::toCborArray() const
{
	QCborArray tmp;
	toCborArray(tmp);
	return tmp;
}

QJsonValue QSerializableArray::toJsonValue() const
{
	QJsonArray tmp;
	toJsonArray(tmp);
	return tmp;
}

QCborValue QSerializableArray::toCborValue() const
{
	QCborArray tmp;
	toCborArray(tmp);
	return std::move(tmp);
}

void QSerializableArray::fromJsonValue(const QJsonValue& json)
{
	if(json.isArray()) fromJsonArray(json.toArray());
}

void QSerializableArray::fromCborValue(const QCborValue& cbor)
{
	if(cbor.isArray()) fromCborArray(cbor.toArray());
}
