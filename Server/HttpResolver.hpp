#ifndef HTTPRESOLVER_H
#define HTTPRESOLVER_H
#include "QHttpRequest.hpp"
#include "QHttpResponse.hpp"

class HttpResolver
{
public:
	virtual ~HttpResolver() = default;
	virtual void fillResponse(const QHttpRequest& request, QHttpResponse& response, QIODevice** iodev = nullptr, QObject *parent = nullptr) = 0;
};

#endif // HTTPRESOLVER_H
