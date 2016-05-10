#include "shash.h"

int SHash::m_nHashsGenerated = 0;
SHash SHash::generateRandomHash()
{
    QString sTime = QString::number(QDateTime::currentMSecsSinceEpoch() + m_nHashsGenerated++);
    QString sHash = QCryptographicHash::hash(sTime.toUtf8(), QCryptographicHash::Md5).toHex();
    return SHash(sHash.toStdString());
}

SHash::SHash()
{

}

SHash::SHash(std::string sHash):
    m_sHash(sHash)
{

}

SHash::SHash(int nId, std::string sHash):
    m_nId(nId),
    m_sHash(sHash)
{

}

QJsonObject SHash::getJsonObject()
{
    QJsonObject jHash;

    jHash.insert("value", m_sHash.c_str());

    return jHash;
}

