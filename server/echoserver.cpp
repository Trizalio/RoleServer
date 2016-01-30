#include "echoserver.h"

QT_USE_NAMESPACE

EchoServer::EchoServer(CSqlConnector *pSqlConnector, quint16 port, bool debug, QObject *parent) :
    QObject(parent),
    m_ServerLogic(pSqlConnector),
    m_pWebSocketServer(new QWebSocketServer(QStringLiteral("Echo Server"),
                                            QWebSocketServer::NonSecureMode, this)),
    m_clients(),
    m_debug(debug)
//    m_Orm(new CSqlConnector("tcp://127.0.0.1:3306", "root", "3421Dark"))
{
    if (m_pWebSocketServer->listen(QHostAddress::Any, port)) {
        if (m_debug)
            qDebug() << "Echoserver listening on port" << port;
        connect(m_pWebSocketServer, &QWebSocketServer::newConnection,
                this, &EchoServer::onNewConnection);
        connect(m_pWebSocketServer, &QWebSocketServer::closed, this, &EchoServer::closed);
    }
}

EchoServer::~EchoServer()
{
    m_pWebSocketServer->close();
    qDeleteAll(m_clients.begin(), m_clients.end());
}

void EchoServer::send()
{
    for(QList<QWebSocket*>::iterator i = m_clients.begin(); i != m_clients.end(); ++i)
    {
        qDebug() << "client found";
        QFile File("/home/trizalio/QT/build-RoleServer-Desktop_Qt_Qt_Version_GCC_64bit-Debug/test_44100Hz_256bit.mp3");
        if(File.open(QIODevice::ReadOnly))
        {
            QByteArray FileData = File.readAll();
            (*i)->sendBinaryMessage(FileData);
            qDebug() << "sent";
            File.close();
        }
    }
}
void EchoServer::play()
{
    for(QList<QWebSocket*>::iterator i = m_clients.begin(); i != m_clients.end(); ++i)
    {
        qDebug() << "client found";
        QFile File("/home/trizalio/QT/build-RoleServer-Desktop_Qt_Qt_Version_GCC_64bit-Debug/test_44100Hz_256bit.mp3");
        if(File.open(QIODevice::ReadOnly))
        {
            QByteArray FileData = File.readAll();
            (*i)->sendTextMessage("play");
            qDebug() << "play";
            File.close();
        }
    }
}

void EchoServer::onNewConnection()
{
    qDebug() << "New connection";
    QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();\
    qDebug() << pSocket->peerAddress().toString() << pSocket->peerName() << pSocket->peerPort();

    connect(pSocket, &QWebSocket::textMessageReceived, this, &EchoServer::processTextMessage);
    connect(pSocket, &QWebSocket::binaryMessageReceived, this, &EchoServer::processBinaryMessage);
    connect(pSocket, &QWebSocket::disconnected, this, &EchoServer::socketDisconnected);

    m_clients << pSocket;
}

void EchoServer::processTextMessage(QString message)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (m_debug)
        qDebug() << QDateTime::currentMSecsSinceEpoch() << "Message received:" << (message.length() < 99 ? message : "");
    if (pClient)
    {
        QString sCommand = message.section(" ", 0, 0);
        QString sValue = message.section(" ", 1, 1);
        int nId = 0;
        if(m_ConnectionToPlayerId.count(pClient))
        {
            nId = m_ConnectionToPlayerId[pClient];
        }
        qDebug() << "Command:" << sCommand << "sValue:" << sValue;

        if(sCommand == "post")
        {
            if(sValue == "login")
            {
                QString sLogin = message.section(" ", 2, 2);
                QString sPasswordHash = message.section(" ", 3, 3);
                int nNewId = m_ServerLogic.login(sLogin.toStdString(), sPasswordHash.toStdString());
                if(nNewId)
                {
                    m_ConnectionToPlayerId[pClient] = nNewId;
                    pClient->sendTextMessage("login ok:");
                    qDebug() << "login ok:" << nNewId;
                }
                else
                {
                    pClient->sendTextMessage("login fail:");
                    qDebug() << "login fail";
                }
            }
            else if(sValue == "logout")
            {
                m_ConnectionToPlayerId[pClient] = 0;
                pClient->sendTextMessage("logout ok:");
            }
        }
        else if(sCommand == "get")
        {
            if(sValue == "player")
            {
                if(nId > 0)
                {
                    QByteArray aJson = m_ServerLogic.getPlayerData(nId);
                    QByteArray aAnswer = "player data:";
                    aAnswer.append(aJson);
                    pClient->sendTextMessage(aAnswer);
                }
                else
                {
                    pClient->sendTextMessage("no player:");
                    qDebug() << "unauthorized access to player data";
                }
            }
            if(sValue == "user")
            {
///                allowed while testing
///                if(nId > 0)
                if(true)
                {
                    int nTargetId = message.section(" ", 2, 2).toInt();
                    QByteArray aJson = m_ServerLogic.getUserDataByWatcher(nTargetId, nId);
                    QByteArray aAnswer = "user data:";
                    aAnswer.append(aJson);
                    pClient->sendTextMessage(aAnswer);
                }
                else
                {
                    pClient->sendTextMessage("auth required:");
                    qDebug() << "unauthorized access to user data";
                }
            }
            if(sValue == "people")
            {
///                allowed while testing
///                if(nId > 0)
                if(true)
                {
                    QByteArray aJson = m_ServerLogic.getUsersAllData();
                    QByteArray aAnswer = "people data:";
                    aAnswer.append(aJson);
                    pClient->sendTextMessage(aAnswer);
                }
                else
                {
                    pClient->sendTextMessage("auth required:");
                    qDebug() << "unauthorized access to people";
                }
            }
            if(sValue == "project")
            {
///                allowed while testing
///                if(nId > 0)
                if(true)
                {
                    int nTargetId = message.section(" ", 2, 2).toInt();
                    /// TODO access check
                    QByteArray aJson = m_ServerLogic.getProjectDataByWatcher(nTargetId, nId);
                    QByteArray aAnswer = "project data:";
                    aAnswer.append(aJson);
                    pClient->sendTextMessage(aAnswer);
                }
                else
                {
                    pClient->sendTextMessage("auth required:");
                    qDebug() << "unauthorized access to user data";
                }
            }
            if(sValue == "projects")
            {
///                allowed while testing
///                if(nId > 0)
                if(true)
                {
                    /// TODO change for getProjectsDataForUser(...);
                    QByteArray aJson = m_ServerLogic.getProjectsDataByWatcher(nId);
//                    QByteArray aJson = m_ServerLogic.getProjectsAllData();
                    QByteArray aAnswer = "projects data:";
                    aAnswer.append(aJson);
                    pClient->sendTextMessage(aAnswer);
                }
                else
                {
                    pClient->sendTextMessage("auth required:");
                    qDebug() << "unauthorized access to projects";
                }
            }
        }
        /*if(message == "test")
        {
            pClient->sendTextMessage("test passed");
        }
        else if(message == "get test audio")
        {
//        QFile File("/home/trizalio/Downloads/viper.ogg");
            QFile File("/home/trizalio/QT/build-RoleServer-Desktop_Qt_Qt_Version_GCC_64bit-Debug/test_44100Hz_256bit.mp3");
            if(File.open(QIODevice::ReadOnly))
            {
                QByteArray FileData = File.readAll();
                pClient->sendBinaryMessage(FileData);
                File.close();
            }
        }
        else if(message.length() >= 2 && message[0] == '{' && message[message.length() - 1] == '}')
        {

            QFile File("/home/trizalio/QT/build-RoleServer-Desktop_Qt_Qt_Version_GCC_64bit-Debug/ws.json");
            if(File.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
            File.write(message.toStdString().c_str(), message.length());
            qDebug() << m_sValue << "res:" << message.toStdString().find(m_sValue.toStdString().c_str());

            pClient->sendTextMessage("got test result");

        }
        else if(message == "get map")
        {
            CPlanetMap Map;
            Map.loadPlanetFromDB();
            CPlanetJson Json(Map);
            QByteArray aAnswer = "accept map:";
            aAnswer.append(Json.getJson());
            pClient->sendTextMessage(aAnswer);
        }
        else
        {
            m_sValue = message;
            size_t i = 0;
            while((i = m_sValue.toStdString().find(",")) < m_sValue.length())
            {
                m_sValue.remove(i, 1);
            }
        }*/
        //pClient->sendTextMessage("message");
    }
}

void EchoServer::processBinaryMessage(QByteArray message)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (m_debug)
        qDebug() << "Binary Message received:" << message;
    if (pClient) {
        pClient->sendBinaryMessage(message);
    }
}

void EchoServer::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if(m_ConnectionToPlayerId.count(pClient))
    {
        m_ConnectionToPlayerId[pClient] = 0;
    }
    if (m_debug)
        qDebug() << "socketDisconnected:" << pClient;
    if (pClient) {
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    }
}
