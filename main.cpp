#include <QCoreApplication>
#include "Server/QHttpRequest.hpp"
#include <QBuffer>
#include <QTextStream>
#include <QTextDocument>
#include <QTextCursor>
#include "Server/QTcpHttpServer.hpp"
#include "Server/QUdpHttpServer.hpp"
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QMap>

class HelloWorldResolver : public HttpResolver
{
private:
	QTextDocument document;
	QDir nativeDir;
	QMap<QString,QString> mimeTypes;
public:
	HelloWorldResolver();
	void fillResponse(const QHttpRequest& request, QHttpResponse& response, QIODevice** iodev = nullptr, QObject *parent = nullptr) override;
	const QTextDocument& getDocument() const;
};

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	HelloWorldResolver resolver;
	QTcpHttpServer server;
	server.setResolver(&resolver);
	if(!server.listen(QHostAddress::Any,8080)) {
		return -1;
	}
	/*QUdpHttpServer server(&resolver);
	if(!server.getSocket().bind(8080)) {
		return -1;
	}*/
	return a.exec();
}

HelloWorldResolver::HelloWorldResolver() : nativeDir(QCoreApplication::applicationDirPath()) {
	mimeTypes = {
		{ QStringLiteral("aac"), QStringLiteral("audio/aac")},
		{ QStringLiteral("abw"), QStringLiteral("application/x-abiword")},
		{ QStringLiteral("arc"), QStringLiteral("application/x-freearc")},
		{ QStringLiteral("avif"), QStringLiteral("image/avif")},
		{ QStringLiteral("avi"), QStringLiteral("video/x-msvideo")},
		{ QStringLiteral("azw"), QStringLiteral("application/vnd.amazon.ebook")},
		{ QStringLiteral("bin"), QStringLiteral("application/octet-stream")},
		{ QStringLiteral("bmp"), QStringLiteral("image/bmp")},
		{ QStringLiteral("bz"), QStringLiteral("application/x-bzip")},
		{ QStringLiteral("bz2"), QStringLiteral("application/x-bzip2")},
		{ QStringLiteral("cda"), QStringLiteral("application/x-cdf")},
		{ QStringLiteral("csh"), QStringLiteral("application/x-csh")},
		{ QStringLiteral("css"), QStringLiteral("text/css")},
		{ QStringLiteral("csv"), QStringLiteral("text/csv")},
		{ QStringLiteral("doc"), QStringLiteral("application/msword")},
		{ QStringLiteral("docx"), QStringLiteral("application/vnd.openxmlformats-officedocument.wordprocessingml.document")},
		{ QStringLiteral("eot"), QStringLiteral("application/vnd.ms-fontobject")},
		{ QStringLiteral("epub"), QStringLiteral("application/epub+zip")},
		{ QStringLiteral("gz"), QStringLiteral("application/gzip")},
		{ QStringLiteral("gif"), QStringLiteral("image/gif")},
		{ QStringLiteral("htm"), QStringLiteral("text/html")},
		{ QStringLiteral("html"), QStringLiteral("text/html")},
		{ QStringLiteral("ico"), QStringLiteral("image/vnd.microsoft.icon")},
		{ QStringLiteral("ics"), QStringLiteral("text/calendar")},
		{ QStringLiteral("jar"), QStringLiteral("application/java-archive")},
		{ QStringLiteral("jpeg"), QStringLiteral("image/jpeg")},
		{ QStringLiteral("jpg"), QStringLiteral("image/jpeg")},
		{ QStringLiteral("js"), QStringLiteral("text/javascript")},
		{ QStringLiteral("json"), QStringLiteral("application/json")},
		{ QStringLiteral("jsonld"), QStringLiteral("application/ld+json")},
		{ QStringLiteral("mid"), QStringLiteral("audio/midi")},
		{ QStringLiteral("midi"), QStringLiteral("audio/midi")},
		{ QStringLiteral("mjs"), QStringLiteral("text/javascript")},
		{ QStringLiteral("mp3"), QStringLiteral("audio/mpeg")},
		{ QStringLiteral("mp4"), QStringLiteral("video/mp4")},
		{ QStringLiteral("mpeg"), QStringLiteral("video/mpeg")},
		{ QStringLiteral("mpkg"), QStringLiteral("application/vnd.apple.installer+xml")},
		{ QStringLiteral("odp"), QStringLiteral("application/vnd.oasis.opendocument.presentation")},
		{ QStringLiteral("ods"), QStringLiteral("application/vnd.oasis.opendocument.spreadsheet")},
		{ QStringLiteral("odt"), QStringLiteral("application/vnd.oasis.opendocument.text")},
		{ QStringLiteral("oga"), QStringLiteral("audio/ogg")},
		{ QStringLiteral("ogv"), QStringLiteral("video/ogg")},
		{ QStringLiteral("ogx"), QStringLiteral("application/ogg")},
		{ QStringLiteral("opus"), QStringLiteral("audio/opus")},
		{ QStringLiteral("otf"), QStringLiteral("font/otf")},
		{ QStringLiteral("png"), QStringLiteral("image/png")},
		{ QStringLiteral("pdf"), QStringLiteral("application/pdf")},
		{ QStringLiteral("php"), QStringLiteral("application/x-httpd-php")},
		{ QStringLiteral("ppt"), QStringLiteral("application/vnd.ms-powerpoint")},
		{ QStringLiteral("pptx"), QStringLiteral("application/vnd.openxmlformats-officedocument.presentationml.presentation")},
		{ QStringLiteral("rar"), QStringLiteral("application/vnd.rar")},
		{ QStringLiteral("rtf"), QStringLiteral("application/rtf")},
		{ QStringLiteral("sh"), QStringLiteral("application/x-sh")},
		{ QStringLiteral("svg"), QStringLiteral("image/svg+xml")},
		{ QStringLiteral("swf"), QStringLiteral("application/x-shockwave-flash")},
		{ QStringLiteral("tar"), QStringLiteral("application/x-tar")},
		{ QStringLiteral("tif .tiff"), QStringLiteral("image/tiff")},
		{ QStringLiteral("ts"), QStringLiteral("video/mp2t")},
		{ QStringLiteral("ttf"), QStringLiteral("font/ttf")},
		{ QStringLiteral("txt"), QStringLiteral("text/plain")},
		{ QStringLiteral("vsd"), QStringLiteral("application/vnd.visio")},
		{ QStringLiteral("wav"), QStringLiteral("audio/wav")},
		{ QStringLiteral("weba"), QStringLiteral("audio/webm")},
		{ QStringLiteral("webm"), QStringLiteral("video/webm")},
		{ QStringLiteral("webp"), QStringLiteral("image/webp")},
		{ QStringLiteral("woff"), QStringLiteral("font/woff")},
		{ QStringLiteral("woff2"), QStringLiteral("font/woff2")},
		{ QStringLiteral("xhtml"), QStringLiteral("application/xhtml+xml")},
		{ QStringLiteral("xls"), QStringLiteral("application/vnd.ms-excel")},
		{ QStringLiteral("xlsx"), QStringLiteral("application/vnd.openxmlformats-officedocument.spreadsheetml.sheet")},
		{ QStringLiteral("xml"), QStringLiteral("application/xml")},
		{ QStringLiteral("xul"), QStringLiteral("application/vnd.mozilla.xul+xml")},
		{ QStringLiteral("zip"), QStringLiteral("application/zip")},
		{ QStringLiteral("3gp"), QStringLiteral("video/3gpp")},
		{ QStringLiteral("3g2"), QStringLiteral("video/3gpp2")},
		{ QStringLiteral("7z"), QStringLiteral("application/x-7z-compressed")}
	};
	QTextCursor* myCursor = new QTextCursor(&document);
	QTextBlockFormat format;
	format.setBackground(Qt::red);
	myCursor->setBlockFormat(format);
	myCursor->insertText("Hello, red world!");
	delete myCursor;
}

const QTextDocument& HelloWorldResolver::getDocument() const
{
	return document;
}

void HelloWorldResolver::fillResponse(const QHttpRequest& request, QHttpResponse& response, QIODevice** iodev, QObject *parent) {
	//(void)request;
	if(iodev) *iodev = nullptr;
	QTextStream stream(stdout);
	request.toString(stream);

	QString dataType;
	qsizetype dataSize = 0;
	bool error = false;
	if(request.getPath().size() <= 1)
	{
		QByteArray doctext = document.toHtml().toUtf8();
		response.setBody(doctext);
		dataSize = doctext.size();
		dataType = QStringLiteral("text/html; charset=utf-8");
	}
	else {
		QFileInfo fileInfo(nativeDir.absoluteFilePath(request.getPath().mid(1)));
		if(fileInfo.exists()) {
			QFile* file = new QFile(fileInfo.absoluteFilePath());
			if(file->open(QFile::ReadOnly) && iodev)
			{
				*iodev = file;
				dataSize = fileInfo.size();

				auto found = mimeTypes.find(fileInfo.completeSuffix());
				if(found == std::end(mimeTypes)) dataType = QStringLiteral("application/octet-stream");
				else dataType = found.value();
			} else {
				delete file;
				error = true;
				dataSize = 0;
			}
		} else {
			error = true;
			QByteArray textToReturn = QStringLiteral("404 - FILE \"%1\" NOT FOUND!").arg(request.getPath()).toUtf8();
			dataType = QStringLiteral("text/plain");
			response.setBody(textToReturn);
			dataSize = textToReturn.size();
		}
	}

	response.setHttpVersion(QStringLiteral("HTTP/1.1"));
	if(error) {
		response.setStatusCode(404);
		response.setStatus(QStringLiteral("NOTFOUND"));
	} else {
		response.setStatusCode(200);
		response.setStatus(QStringLiteral("OK"));
	}
	response.setHeader(QStringLiteral("Location"),QStringLiteral("http://localhost:80").append(request.getHeader(QStringLiteral("Location"))));
	response.setHeader(QStringLiteral("Cache-Control"),QStringLiteral("no-cache"));
	response.setHeader(QStringLiteral("Connection"),QStringLiteral("Keep-Alive"));
	response.setHeader(QStringLiteral("Server"),QStringLiteral("QHttpServer"));
	if(!dataType.isEmpty()) response.setHeader(QStringLiteral("Content-Type"),dataType);
	response.setHeader(QStringLiteral("Content-Length"),QString::number(dataSize));
}
