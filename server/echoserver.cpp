#include "echoserver.h"

QT_USE_NAMESPACE

EchoServer::EchoServer(CSqlConnector *pSqlConnector, quint16 port, bool debug, QObject *parent) :
    QObject(parent),
    m_pWebSocketServer(new QWebSocketServer(QStringLiteral("Echo Server"),
                                            QWebSocketServer::NonSecureMode, this)),
    m_clients(),
    m_debug(debug),
    m_ServerLogic(pSqlConnector),
    m_HashGenerated(0)
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

        SConnection EmptyConnection;
        SConnection& Connection = EmptyConnection;
        if(m_ConnectionToPlayerConnection.count(pClient))
        {
            Connection = m_ConnectionToPlayerConnection[pClient];
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
                    m_ConnectionToPlayerConnection[pClient] = SConnection(nNewId, Player.m_bAdmin);
                    m_PlayerIdToConnection[nNewId] = pClient;
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
                m_ConnectionToPlayerConnection.erase(pClient);
                m_PlayerIdToConnection.erase(nId);
                pClient->sendTextMessage("logout ok:");
            }
            else if(sValue == "logas")
            {
                if(Connection.m_bAdmin)
                {
                    int nTargetId = message.section(" ", 2, 2).toInt();
                    SPlayer Player = m_ServerLogic.getPlayerById(nTargetId);
                    if(Player.m_nId > 0)
                    {
                        if(!Player.m_bAdmin)
                        {
                            m_ConnectionToPlayerConnection[pClient] = SConnection(Player.m_nId, false);
                            m_PlayerIdToConnection[Player.m_nId] = pClient;
                            pClient->sendTextMessage("logas ok:");
                        }
                        else
                        {
                            pClient->sendTextMessage("logas admin:");
                            qDebug() << "attempt to logas admin";
                        }
                    }
                    else
                    {
                        pClient->sendTextMessage("no player:");
                        qDebug() << "attempt to logas unexistant user";
                    }
                }
                else
                {
                    pClient->sendTextMessage("not allowed:");
                    qDebug() << "unauthorized access to logas";
                }
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
            else if(sValue == "player")
            {
                if(Connection.m_bAdmin)
                {
                    QString sOperation = message.section(" ", 2, 2);
                    if(sOperation == "add")
                    {
                        QByteArray sData = message.section(" ", 3).toUtf8();
                        bool bResult = m_ServerLogic.addPlayer(sData);
                        if(bResult)
                        {
                            pClient->sendTextMessage("player added:");
                        }
                        else
                        {
                            pClient->sendTextMessage("player manage fail:data process error");
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
                        bool bResult = m_ServerLogic.updatePlayer(sData);
                        if(bResult)
                        {
                            pClient->sendTextMessage("player updated:");
                        }
                        else
                        {
                            pClient->sendTextMessage("player manage fail:data process error");
                        }
                    }
                    else
                    {
                        pClient->sendTextMessage("player manage fail:no such command");
                    }
                }
                else
                {
                    pClient->sendTextMessage("not allowed:");
                    qDebug() << "unauthorized access to manage player data";
                }
            }
            else if(sValue == "credential")
            {
                if(Connection.m_bAdmin)
                {
                    QString sOperation = message.section(" ", 2, 2);
                    if(sOperation == "set")
                    {
                        QByteArray sData = message.section(" ", 3).toUtf8();
                        bool bResult = m_ServerLogic.updatePlayerCredential(sData);
                        if(bResult)
                        {
                            pClient->sendTextMessage("credential updated:");
                        }
                        else
                        {
                            pClient->sendTextMessage("credential manage fail:data process error");
                        }
                    }
                    else
                    {
                        pClient->sendTextMessage("credential manage fail:no such command");
                    }
                }
                else
                {
                    pClient->sendTextMessage("not allowed:");
                    qDebug() << "unauthorized access to manage credential data";
                }
            }
            else if(sValue == "qr")
            {
                qDebug() << "qr action";
                QString sAction = message.section(" ", 2);
                if(Connection.m_nConnectedId)
                {
                    if(m_PlayerIdToConnection.count(Connection.m_nConnectedId) > 0)
                    {
                        QWebSocket* pTargetConnection = m_PlayerIdToConnection[Connection.m_nConnectedId];
                        qDebug() << "sAction" << sAction;
                        if(sAction == "Взять анализ крови")
                        {
                            pTargetConnection->sendTextMessage("read: {\"text\": \"У Вас взяли анализ крови, Вы чувствуете лёгкую слабость ближайшие 15 минут\"}");
                            pClient->sendTextMessage("qr action accepted:");
                            qDebug() << "qr action accepted";
                        }
                        else
                        {
                            pClient->sendTextMessage("qr action unknown:");
                            qDebug() << "qr action unknown";
                        }
                    }
                    else
                    {
                        pClient->sendTextMessage("target not found:");
                        qDebug() << "target not found";
                    }
                }
                else
                {
                    pClient->sendTextMessage("no connection:");
                    qDebug() << "no connection";
                }
            }
            else
            {
                pClient->sendTextMessage("unrecognized type:");
                qDebug() << "unrecognized type";
            }
        }
        else if(sCommand == "get")
        {
            if(sValue == "player")
            {
                int nTargetId = message.section(" ", 2, 2).toInt();
                if(nTargetId > 0 && Connection.m_bAdmin)
                {
                    QByteArray aJson = m_ServerLogic.getPlayerData(nTargetId);
                    QByteArray aAnswer = "player data:";
                    aAnswer.append(aJson);
                    pClient->sendTextMessage(aAnswer);
                }
                else if(nId > 0)
                {
                    QByteArray aJson = m_ServerLogic.getPlayerData(nId);
                    QByteArray aAnswer = "self data:";
                    aAnswer.append(aJson);
                    pClient->sendTextMessage(aAnswer);
                }
                else
                {
                    pClient->sendTextMessage("no player:");
                    qDebug() << "unauthorized access to player data";
                }
            }
            if(sValue == "players")
            {
                if(Connection.m_bAdmin)
                {
                    QByteArray aJson = m_ServerLogic.getPlayersAll();
                    QByteArray aAnswer = "players data:";
                    aAnswer.append(aJson);
                    pClient->sendTextMessage(aAnswer);
                }
                else
                {
                    pClient->sendTextMessage("not allowed:");
                    qDebug() << "unauthorized access to players data";
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
            if(sValue == "users")
            {
///                allowed while testing
///                if(nId > 0)
                if(true)
                {
                    QByteArray aJson = m_ServerLogic.getUsersAllData();
                    QByteArray aAnswer = "users data:";
                    aAnswer.append(aJson);
                    pClient->sendTextMessage(aAnswer);
                }
                else
                {
                    pClient->sendTextMessage("auth required:");
                    qDebug() << "unauthorized access to people";
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
            if(sValue == "qr")
            {
                QString sData = message.section(" ", 2).toUtf8();
                if(sData.isEmpty())
                {
                    if(nId > 0)
                    {
                        QString sTime = QString::number(QDateTime::currentMSecsSinceEpoch() + m_HashGenerated++);
                        QString sHash = QCryptographicHash::hash(sTime.toUtf8(), QCryptographicHash::Md5).toHex();
                        m_HashToPlayerId[sHash.toStdString()] = nId;
                        pClient->sendTextMessage("qr data:{\"value\": \"" + sHash + "\"}");
                        qDebug() << "sent qr hash" << sHash;
                    }
                    else
                    {
                        pClient->sendTextMessage("auth required:");
                        qDebug() << "unauthorized access to qr";
                    }
                }
                else
                {
                    qDebug() << "qr red" << sData;
                    if(m_HashToPlayerId.count(sData.toStdString()))
                    {
                        int QrId = m_HashToPlayerId[sData.toStdString()];
                        m_ConnectionToPlayerConnection[pClient].m_nConnectedId = QrId;
                        SPlayer targetPlayer = m_ServerLogic.getPlayerById(QrId);
                        pClient->sendTextMessage(QString(("qr recognised:{\"object\": \"" + targetPlayer.m_sSurname
                                             + " "  + targetPlayer.m_sName
                                             + " "  + targetPlayer.m_sPatronymic
                                            + "\", \"data\": \"Человек\", \"actions\": [\"Взять анализ крови\", \"Оглушить\"]}").c_str()));
                    }
                    else
                    {
                        pClient->sendTextMessage("qr unrecognised:");
                    }

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
    m_ConnectionToPlayerConnection.erase(pClient);
    if (m_debug)
        qDebug() << "socketDisconnected:" << pClient;
    if (pClient) {
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    }
}
