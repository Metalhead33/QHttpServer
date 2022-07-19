#include "QSerializableObject.hpp"
#include <QMetaProperty>

QJsonObject QSerializableObject::toJsonObject() const
{
	QJsonObject tmp;
	toJsonObject(tmp);
	return tmp;
}

QCborMap QSerializableObject::toCborMap() const
{
	QCborMap tmp;
	toCborMap(tmp);
	return tmp;
}

QJsonValue QSerializableObject::toJsonValue() const
{
	QJsonObject tmp;
	toJsonObject(tmp);
	return tmp;
}

QCborValue QSerializableObject::toCborValue() const
{
	QCborMap tmp;
	toCborMap(tmp);
	return std::move(tmp);
}

void QSerializableObject::fromJsonValue(const QJsonValue& json)
{
	if(json.isObject()) fromJsonObject(json.toObject());
}

void QSerializableObject::fromCborValue(const QCborValue& cbor)
{
	if(cbor.isMap()) fromCborMap(cbor.toMap());
}

void QSerializableObject::qobjectToJsonObject(const QObject* object, QJsonObject& json)
{
	if(!object) return;
	const QMetaObject *metaObj = object->metaObject();
	for (int i = metaObj->propertyOffset(); i < metaObj->propertyCount(); ++i)
	{
		const auto property = metaObj->property(i);
		if(property.isReadable()) json.insert(property.name(),QJsonValue::fromVariant(property.read(object)));
	}
}

QJsonObject QSerializableObject::qobjectToJsonObject(const QObject* object)
{
	QJsonObject tmp;
	qobjectToJsonObject(object,tmp);
	return tmp;
}

void QSerializableObject::qobjectToCborMap(const QObject* object, QCborMap& cbor)
{
	if(!object) return;
	const QMetaObject *metaObj = object->metaObject();
	for (int i = metaObj->propertyOffset(); i < metaObj->propertyCount(); ++i)
	{
		const auto property = metaObj->property(i);
		if(property.isReadable()) cbor.insert(QString::fromUtf8(property.name()),QCborValue::fromVariant(property.read(object)));
	}
}

QCborMap QSerializableObject::qobjectToCborMap(const QObject* object)
{
	QCborMap tmp;
	qobjectToCborMap(object,tmp);
	return tmp;
}

void QSerializableObject::jsonObjectToQObject(const QJsonObject& json, QObject* object)
{
	if(!object) return;
	const QMetaObject *metaObj = object->metaObject();
	for (int i = metaObj->propertyOffset(); i < metaObj->propertyCount(); ++i)
	{
		const auto property = metaObj->property(i);
		if(property.isWritable() && json.contains(property.name())) property.write(object, json[property.name()].toVariant());
	}
}

void QSerializableObject::cborMapToQObject(const QCborMap& cbor, QObject* object)
{
	if(!object) return;
	const QMetaObject *metaObj = object->metaObject();
	for (int i = metaObj->propertyOffset(); i < metaObj->propertyCount(); ++i)
	{
		const auto property = metaObj->property(i);
		if(property.isWritable()) {
			QString propertyName = QString::fromUtf8(property.name());
			property.write(object,cbor[propertyName].toVariant());
		}
	}
}
