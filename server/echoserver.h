#ifndef ECHOSERVER_H
#define ECHOSERVER_H

#include <unordered_map>

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QByteArray>
#include <QtCore/QFile>

#include "QtWebSockets/qwebsocketserver.h"
#include "QtWebSockets/qwebsocket.h"
#include <QtCore/QDebug>

QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)

#include "orm/corm.h"
#include "cplanetjson.h"
#include "cserverlogic.h"

class EchoServer : public QObject
{
    Q_OBJECT
public:
    explicit EchoServer(CSqlConnector* pSqlConnector, quint16 port, bool debug = false, QObject *parent = Q_NULLPTR);
    ~EchoServer();


public Q_SLOTS:
    void send();
    void play();

Q_SIGNALS:
    void closed();

private Q_SLOTS:
    void onNewConnection();
    void processTextMessage(QString message);
    void processBinaryMessage(QByteArray message);
    void socketDisconnected();

private:

    std::unordered_map<QWebSocket*, int> m_ConnectionToPlayerId;
    QWebSocketServer *m_pWebSocketServer;
    QList<QWebSocket *> m_clients;
    bool m_debug;
//    COrm m_Orm;

    QString m_sValue;
    CServerLogic m_ServerLogic;
};

#endif //ECHOSERVER_H