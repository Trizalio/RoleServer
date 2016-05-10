#include <QtCore/QCoreApplication>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCommandLineOption>

#include "server/echoserver.h"
#include "console.h"
#include "cplanetthread.h"
#include "cconnectionkeeper.h"
#include "tick/ctickmanager.h"

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
            QCoreApplication::translate("main", "Port for echoserver [default: 1991]."),
            QCoreApplication::translate("main", "port"), QLatin1Literal("1991"));
    parser.addOption(portOption);
    QCommandLineOption mysqlPortOption(QStringList() << "i" << "db_port",
            QCoreApplication::translate("main", "Port for mysql [default: 3306]."),
            QCoreApplication::translate("main", "db_port"), QLatin1Literal("3306"));
    parser.addOption(mysqlPortOption);
    QCommandLineOption mysqlLoginOption(QStringList() << "l" << "db_login",
            QCoreApplication::translate("main", "Login for mysql [default: root]."),
            QCoreApplication::translate("main", "db_login"), QLatin1Literal("root"));
    parser.addOption(mysqlLoginOption);
    QCommandLineOption mysqlPasswordOption(QStringList() << "s" << "db_pass",
            QCoreApplication::translate("main", "Password for mysql [default: root]."),
            QCoreApplication::translate("main", "db_pass"), QLatin1Literal("root"));
    parser.addOption(mysqlPasswordOption);
    parser.process(a);
    bool debug = true;//parser.isSet(dbgOption);
    int nWebSocketPort = parser.value(portOption).toInt();
    std::string sMysqlPort = parser.value(mysqlPortOption).toStdString();
    std::string sMysqlLogin = parser.value(mysqlLoginOption).toStdString();
    std::string sMysqlPass = parser.value(mysqlPasswordOption).toStdString();

    qDebug() << sMysqlPass.c_str();
    COrm* pOrm = new COrm(new CSqlConnector("tcp://127.0.0.1:" + sMysqlPort, sMysqlLogin, sMysqlPass));

    CConnectionKeeper* pConnectionKeeper = new CConnectionKeeper(pOrm);
    EchoServer *server = new EchoServer(pOrm, nWebSocketPort, debug);
    QObject::connect(server, &EchoServer::closed, &a, &QCoreApplication::quit);

    Console console;
    console.run();
    QObject::connect(&console, SIGNAL(quit()), &a, SLOT(quit()));
    QObject::connect(&console, SIGNAL(send()), server, SLOT(send()));
    QObject::connect(&console, SIGNAL(play()), server, SLOT(play()));

    CPlanetThread PlanetThread;
    PlanetThread.start();

    QTimer* pTimer = new QTimer();
    CTickManager* pTickManager =  new CTickManager(pOrm);
    QObject::connect(pTimer, SIGNAL(timeout()), pTickManager, SLOT(tick()));
    QObject::connect(pTickManager, SIGNAL(statusChange(QByteArray,int)), server, SLOT(sendStatusChange(QByteArray,int)));
    QObject::connect(pTickManager, SIGNAL(statusUpdate(int)), server, SLOT(sendStatusUpdate(int)));
    pTimer->start(1000);

    return a.exec();
}
