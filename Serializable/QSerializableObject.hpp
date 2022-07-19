#ifndef QSERIALIZABLEOBJECT_HPP
#define QSERIALIZABLEOBJECT_HPP
#include "QSerializable.hpp"
#include <QJsonObject>
#include <QCborMap>
#include <QObject>

class QSerializableObject : public QSerializable
{
public:
	// Serialize
	virtual void toJsonObject(QJsonObject& json) const = 0;
	virtual void toCborMap(QCborMap& json) const = 0;
	QJsonObject toJsonObject(void) const;
	QCborMap toCborMap(void) const;
	QJsonValue toJsonValue() const override;
	QCborValue toCborValue() const override;
	// Unserialize
	virtual void fromJsonObject(const QJsonObject& json) = 0;
	virtual void fromCborMap(const QCborMap& json) = 0;
	void fromJsonValue(const QJsonValue& json) override;
	void fromCborValue(const QCborValue& cbor) override;
	// Other semi-related helper functions
	static void qobjectToJsonObject(const QObject* object, QJsonObject& json);
	static QJsonObject qobjectToJsonObject(const QObject* object);
	static void qobjectToCborMap(const QObject* object, QCborMap& cbor);
	static QCborMap qobjectToCborMap(const QObject* object);
	static void jsonObjectToQObject(const QJsonObject& json, QObject* object);
	static void cborMapToQObject(const QCborMap& cbor, QObject* object);
};

#endif // QSERIALIZABLEOBJECT_HPP
