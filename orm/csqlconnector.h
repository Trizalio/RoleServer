#ifndef CSQLCONNECTOR_H
#define CSQLCONNECTOR_H

#include <QtCore/QDebug>

#include <mysql_connection.h>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include "orm/sql_objects/suser.h"

#define DATABASE_NAME "space_base"

class CSqlConnector
{
public:
    CSqlConnector(std::string sHost, std::string sLogin, std::string sPassword);
    ~CSqlConnector();
    const CSqlConnector& operator=( const CSqlConnector& );

    void execute(std::string sQuery);
    sql::ResultSet* executeResult(std::string sQuery);
    sql::PreparedStatement* prepare(std::string sQuery);
private:


    void reconnect();
    bool connect();

    sql::Driver* m_pDriver;
    sql::Connection *m_pConnection;

    std::string m_sHost;
    std::string m_sLogin;
    std::string m_sPassword;

};

#endif // CSQLCONNECTOR_H
