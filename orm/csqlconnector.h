
#define _GLIBCXX_USE_CXX11_ABI 0

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
    CSqlConnector(QString sHost, QString sLogin, QString sPassword);
    ~CSqlConnector();
    const CSqlConnector& operator=( const CSqlConnector& );

    void execute(QString sQuery);
    sql::ResultSet* executeResult(QString sQuery);
    sql::PreparedStatement* prepare(QString sQuery);
private:


    void reconnect();
    bool connect();

    sql::Driver* m_pDriver;
    sql::Connection *m_pConnection;

    QString m_sHost;
    QString m_sLogin;
    QString m_sPassword;

};

#endif // CSQLCONNECTOR_H
