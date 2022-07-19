#ifndef QSERIALIZABLEARRAY_HPP
#define QSERIALIZABLEARRAY_HPP
#include "QSerializable.hpp"
#include <QJsonArray>
#include <QCborArray>

class QSerializableArray : public QSerializable
{
public:
	// Serialize
	virtual void toJsonArray(QJsonArray& json) const = 0;
	virtual void toCborArray(QCborArray& json) const = 0;
	QJsonArray toJsonArray(void) const;
	QCborArray toCborArray(void) const;
	QJsonValue toJsonValue() const override;
	QCborValue toCborValue() const override;
	// Unserialize
	virtual void fromJsonArray(const QJsonArray& json) = 0;
	virtual void fromCborArray(const QCborArray& json) = 0;
	void fromJsonValue(const QJsonValue& json) override;
	void fromCborValue(const QCborValue& cbor) override;
};

#endif // QSERIALIZABLEARRAY_HPP
