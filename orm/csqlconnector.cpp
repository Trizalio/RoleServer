#include "orm/csqlconnector.h"

CSqlConnector::CSqlConnector(QString sHost, QString sLogin, QString sPassword):
    m_pDriver(0),
    m_pConnection(0),

    m_sHost(sHost),
    m_sLogin(sLogin),
    m_sPassword(sPassword)
{
    connect();
}

CSqlConnector::~CSqlConnector()
{
    if(m_pConnection)
    {
        delete m_pConnection;
    }
}

const CSqlConnector &CSqlConnector::operator=(const CSqlConnector &)
{
    return CSqlConnector(m_sHost, m_sLogin, m_sPassword);
}

void CSqlConnector::execute(QString sQuery)
{
    if(!m_pConnection)
    {
        reconnect();
    }
    sql::Statement* pStatement = m_pConnection->createStatement();
    pStatement->execute(sQuery.toStdString());
    delete pStatement;
}

sql::ResultSet* CSqlConnector::executeResult(QString sQuery)
{
    if(!m_pConnection)
    {
        reconnect();
    }
    sql::Statement* pStatement = m_pConnection->createStatement();
    sql::ResultSet* pResult = pStatement->executeQuery(sQuery.toStdString());
    delete pStatement;
    return pResult;
}

sql::PreparedStatement* CSqlConnector::prepare(QString sQuery)
{
    if(!m_pConnection)
    {
        reconnect();
    }
    sql::PreparedStatement* pPreparedStatement = m_pConnection->prepareStatement(sQuery.toStdString());
    return pPreparedStatement;
}



void CSqlConnector::reconnect()
{
    if(!connect())
    {
        qDebug() << "FATAL: Reconnection failed, no connection available";
        assert(0);
    }
}

bool CSqlConnector::connect()
{
    if(!m_pDriver)
    {
        m_pDriver = get_driver_instance();
    }
    if(!m_pConnection)
    {
        try
        {
            qDebug() << m_sHost << m_sLogin << m_sPassword;
            m_pConnection = m_pDriver->connect(m_sHost.toStdString(), m_sLogin.toStdString(), m_sPassword.toStdString());
            m_pConnection->setSchema(DATABASE_NAME);
            qDebug() << "Connected";
        }
        catch(sql::SQLException e)
        {
            qDebug() << "Failed to connect" << e.getErrorCode() << e.getSQLState().c_str() << e.getSQLStateCStr() << e.what();
        }
    }
    else
    {
        qDebug() << "Reconnection is not nessesary, skipped";
    }

    return (bool)m_pConnection;
}
