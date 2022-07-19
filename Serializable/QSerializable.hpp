#ifndef QSERIALIZABLE_HPP
#define QSERIALIZABLE_HPP
#include <QJsonValue>
#include <QCborValue>

class QSerializable {
public:
	virtual ~QSerializable() = default;
	virtual QJsonValue toJsonValue(void) const = 0;
	virtual QCborValue toCborValue(void) const = 0;
	virtual void fromJsonValue(const QJsonValue& json) = 0;
	virtual void fromCborValue(const QCborValue& cbor) = 0;
};

#endif // QSERIALIZABLE_HPP
