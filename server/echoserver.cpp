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
        qDebug() << QDateTime::currentMSecsSinceEpoch() << "Message received:" << (message.length() < 300 ? message : "too long to display");
    if (pClient)
    {
        QString sCommand = message.section(" ", 0, 0);
        QString sValue = message.section(" ", 1, 1);
        SConnection Connection;
        if(m_ConnectionToPlayerId.count(pClient))
        {
            Connection = m_ConnectionToPlayerId[pClient];
        }
        int nId = Connection.m_nId; /// TODO: remove legacy
        qDebug() << "Command:" << sCommand << "sValue:" << sValue;

        if(sCommand == "post")
        {
            if(sValue == "login")
            {
                QString sLogin = message.section(" ", 2, 2);
                QString sPasswordHash = message.section(" ", 3, 3);
                SPlayer Player = m_ServerLogic.login(sLogin.toStdString(), sPasswordHash.toStdString());
                int nNewId = Player.m_nId;
                if(nNewId)
                {
                    m_ConnectionToPlayerId[pClient] = SConnection(nNewId, Player.m_bAdmin);
                    QByteArray aAnswer = "login ok:";
                    if(Player.m_bAdmin)
                    {
                        aAnswer.append("admin");

                    }
                    pClient->sendTextMessage(aAnswer);
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
                m_ConnectionToPlayerId.erase(pClient);
                pClient->sendTextMessage("logout ok:");
            }
            else if(sValue == "user")
            {
                if(Connection.m_bAdmin)
                {
                    QString sOperation = message.section(" ", 2, 2);
                    if(sOperation == "add")
                    {
                        QByteArray sData = message.section(" ", 3).toUtf8();
                        bool bResult = m_ServerLogic.addUser(sData);
                        if(bResult)
                        {
                            pClient->sendTextMessage("user added:");
                        }
                        else
                        {
                            pClient->sendTextMessage("user manage fail:data process error");
                        }
                    }
                    /*else if(sOperation == "delete")
                    {
                        int nUserId = message.section(" ", 3).toInt();;
                        bool bResult = m_ServerLogic.addUser(sData);
                        if(bResult)
                        {
                            pClient->sendTextMessage("user added:");
                        }
                        else
                        {
                            pClient->sendTextMessage("user manage fail:data process error");
                        }
                    }*/
                    else if(sOperation == "update")
                    {
                        QByteArray sData = message.section(" ", 3).toUtf8();
                        bool bResult = m_ServerLogic.updateUser(sData);
                        if(bResult)
                        {
                            pClient->sendTextMessage("user updated:");
                        }
                        else
                        {
                            pClient->sendTextMessage("user manage fail:data process error");
                        }
                    }
                    else
                    {
                        pClient->sendTextMessage("user manage fail:no such command");
                    }
                }
                else
                {
                    pClient->sendTextMessage("not allowed:");
                    qDebug() << "unauthorized access to manage user data";
                }
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
//                    qDebug() << aJson;
//                    qDebug() << "{\n    \"BirthDate\": \"2074-09-03\",\n    \"Description\": \"\xD0\x9E\xD0\xB1\xD1\x80\xD0\xB0\xD1\x89\xD0\xB0\xD1\x82\xD1\x8C\xD1\x81\xD1\x8F \xD1\x87\xD0\xB5\xD1\x80\xD0\xB5\xD0\xB7 \xD1\x81\xD0\xB5\xD0\xBA\xD1\x80\xD0\xB5\xD1\x82\xD0\xB0\xD1\x80\xD1\x8F\",\n    \"Groups\": [\n        {\n            \"Description\": \"\xD0\x9F\xD1\x80\xD0\xB8\xD0\xBD\xD0\xB8\xD0\xBC\xD0\xB0\xD0\xB5\xD1\x82 \xD0\xBD\xD0\xB0\xD0\xB8\xD0\xB1\xD0\xBE\xD0\xBB\xD0\xB5\xD0\xB5 \xD0\xB2\xD0\xB0\xD0\xB6\xD0\xBD\xD1\x8B\xD0\xB5 \xD1\x80\xD0\xB5\xD1\x88\xD0\xB5\xD0\xBD\xD0\xB8\xD1\x8F \xD0\xB2 \xD0\xB6\xD0\xB8\xD0\xB7\xD0\xBD\xD0\xB8 \xD0\xB1\xD0\xB0\xD0\xB7\xD1\x8B\",\n            \"Id\": 1,\n            \"Name\": \"\xD0\xA3\xD0\xBF\xD1\x80\xD0\xB0\xD0\xB2\xD0\xBB\xD0\xB5\xD0\xBD\xD0\xB8\xD0\xB5 \xD0\xB1\xD0\xB0\xD0\xB7\xD1\x8B\",\n            \"Type\": \"lab\"\n        }\n    ],\n    \"Id\": 1,\n    \"Name\": \"\xD0\x9E\xD0\xBB\xD0\xB5\xD0\xB3\",\n    \"Patronymic\": \"\xD0\x91\xD0\xBE\xD1\x80\xD0\xB8\xD1\x81\xD0\xBE\xD0\xB2\xD0\xB8\xD1\x87\",\n    \"Profession\": \"\xD0\x9D\xD0\xB0\xD1\x87\xD0\xB0\xD0\xBB\xD1\x8C\xD0\xBD\xD0\xB8\xD0\xBA \xD1\x82\xD0\xB5\xD1\x80\xD1\x80\xD0\xB0\xD1\x84\xD0\xBE\xD1\x80\xD0\xBC\xD0\xB0\xD1\x86\xD0\xB8\xD0\xBE\xD0\xBD\xD0\xBD\xD0\xBE\xD0\xB9 \xD0\xB1\xD0\xB0\xD0\xB7\xD1\x8B\",\n    \"Surname\": \"\xD0\x9F\xD1\x87\xD1\x91\xD0\xBB\xD0\xBA\xD0\xB8\xD0\xBD\"\n}\n";
//                    qDebug() << "post user update {\"Name\":\"\u041E\u043B\u0435\u04332\",\"Surname\":\"\u041F\u0447\u0451\u043B\u043A\u0438\u043D\",\"Patronymic\":\"\u0411\u043E\u0440\u0438\u0441\u043E\u0432\u0438\u0447\",\"BirthDate\":\"2074-09-03\",\"Profession\":\"\u041D\u0430\u0447\u0430\u043B\u044C\u043D\u0438\u043A \u0442\u0435\u0440\u0440\u0430\u0444\u043E\u0440\u043C\u0430\u0446\u0438\u043E\u043D\u043D\u043E\u0439 \u0431\u0430\u0437\u044B\",\"Description\":\"\u041E\u0431\u0440\u0430\u0449\u0430\u0442\u044C\u0441\u044F \u0447\u0435\u0440\u0435\u0437 \u0441\u0435\u043A\u0440\u0435\u0442\u0430\u0440\u044F\",\"Id\":1}";

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
//
                    QByteArray aJson;
                    aJson = m_ServerLogic.getProjectsDataByWatcher(nId);
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
            if(sValue == "news")
            {
///                allowed while testing
///                if(nId > 0)
                if(true)
                {
                    /// TODO change for getProjectsDataForUser(...);
                    QByteArray aJson = m_ServerLogic.getNewsAllByWatcher(nId);
//                    QByteArray aJson = m_ServerLogic.getProjectsAllData();
                    QByteArray aAnswer = "news data:";
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
    m_ConnectionToPlayerId.erase(pClient);
    if (m_debug)
        qDebug() << "socketDisconnected:" << pClient;
    if (pClient) {
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    }
}
