#include "orm/csqlconnector.h"

CSqlConnector::CSqlConnector(std::string sHost, std::string sLogin, std::string sPassword):
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

void CSqlConnector::execute(std::string sQuery)
{
    if(!m_pConnection)
    {
        reconnect();
    }
    sql::Statement* pStatement = m_pConnection->createStatement();
    pStatement->execute(sQuery);
    delete pStatement;
}

sql::ResultSet* CSqlConnector::executeResult(std::string sQuery)
{
    if(!m_pConnection)
    {
        reconnect();
    }
    sql::Statement* pStatement = m_pConnection->createStatement();
    sql::ResultSet* pResult = pStatement->executeQuery(sQuery);
    delete pStatement;
    return pResult;
}

sql::PreparedStatement* CSqlConnector::prepare(std::string sQuery)
{
    if(!m_pConnection)
    {
        reconnect();
    }
    sql::PreparedStatement* pPreparedStatement = m_pConnection->prepareStatement(sQuery);
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
            qDebug() << m_sHost.c_str() << m_sLogin.c_str() << m_sPassword.c_str();
            m_pConnection = m_pDriver->connect(m_sHost, m_sLogin, m_sPassword);
            m_pConnection->setSchema(DATABASE_NAME);
            qDebug() << "Connected";
        }
        catch(sql::SQLException e)
        {
            qDebug() << "Failed to connect";
        }
    }
    else
    {
        qDebug() << "Reconnection is not nessesary, skipped";
    }

    return (bool)m_pConnection;
}
