#include <QtCore/QCoreApplication>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCommandLineOption>

#include "echoserver.h"
#include "console.h"
#include "cplanetthread.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription("QtWebSockets example: echoserver");
    parser.addHelpOption();

    QCommandLineOption dbgOption(QStringList() << "d" << "debug",
            QCoreApplication::translate("main", "Debug output [default: off]."));
    parser.addOption(dbgOption);
    QCommandLineOption portOption(QStringList() << "p" << "port",
            QCoreApplication::translate("main", "Port for echoserver [default: 1234]."),
            QCoreApplication::translate("main", "port"), QLatin1Literal("1991"));
    parser.addOption(portOption);
    parser.process(a);
    bool debug = true;//parser.isSet(dbgOption);
    int port = parser.value(portOption).toInt();

    EchoServer *server = new EchoServer(port, debug);
    QObject::connect(server, &EchoServer::closed, &a, &QCoreApplication::quit);

    Console console;
    console.run();
    QObject::connect(&console, SIGNAL(quit()), &a, SLOT(quit()));
    QObject::connect(&console, SIGNAL(send()), server, SLOT(send()));
    QObject::connect(&console, SIGNAL(play()), server, SLOT(play()));

    CPlanetThread PlanetThread;
    PlanetThread.start();

    return a.exec();
}
