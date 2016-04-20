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
#include <QDateTime>

QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)

#include "orm/corm.h"
#include "cplanetjson.h"
#include "cserverlogic.h"

struct SConnection
{
    SConnection(int nId, bool bAdmin):
        m_nId(nId),
        m_bAdmin(bAdmin)
    {}
    SConnection()
    {}
    int m_nId = 0;
    bool m_bAdmin = false;
    int m_nConnectedId = 0;
};

class EchoServer : public QObject
{
    Q_OBJECT
public:
    explicit EchoServer(COrm *pOrm, quint16 port, bool debug = false, QObject *parent = Q_NULLPTR);
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

    std::unordered_map<std::string, int> m_HashToPlayerId;
    std::unordered_map<QWebSocket*, SConnection> m_ConnectionToPlayerConnection;
    std::unordered_map<int, QWebSocket*> m_PlayerIdToConnection;
    QWebSocketServer *m_pWebSocketServer;
    QList<QWebSocket *> m_clients;
    bool m_debug;
//    COrm m_Orm;

    QString m_sValue;
    CServerLogic m_ServerLogic;

    qint64 m_HashGenerated;
};

#endif //ECHOSERVER_H
