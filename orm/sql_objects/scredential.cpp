#include "scredential.h"
#include <QCryptographicHash>
#include <QDebug>

std::string SCredential::getPassHash(std::string sPassword)
{
    QString sHash = QCryptographicHash::hash(sPassword.c_str(), QCryptographicHash::Md5).toHex();
    qDebug() << sHash.toStdString().c_str();
    return sHash.toStdString();
}

SCredential::SCredential(){}

SCredential::SCredential(int nPlayerId, std::string sLogin, std::string sPasswordHash):
    m_nId(nPlayerId),
    m_sLogin(sLogin),
    m_sPasswordHash(sPasswordHash)
{}
