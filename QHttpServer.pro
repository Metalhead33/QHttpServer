QT += gui network
CONFIG += c++2a console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        Serializable/QSerializableArray.cpp \
        Serializable/QSerializableObject.cpp \
        Server/QHttpRequest.cpp \
        Server/QHttpResolutionTask.cpp \
        Server/QHttpResponse.cpp \
        Server/QTcpHttpServer.cpp \
        Server/QUdpHttpServer.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
	Serializable/QSerializable.hpp \
	Serializable/QSerializableArray.hpp \
	Serializable/QSerializableObject.hpp \
	Server/HttpResolver.hpp \
	Server/QHttpRequest.hpp \
	Server/QHttpResolutionTask.hpp \
	Server/QHttpResponse.hpp \
	Server/QTcpHttpServer.hpp \
	Server/QUdpHttpServer.hpp

DISTFILES += \
	LICENSE \
	README.md
