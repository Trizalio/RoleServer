#ifndef CJSONSERIALIZABLE_H
#define CJSONSERIALIZABLE_H

#include <string>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

class CJsonSerializable
{
public:
    CJsonSerializable();

    QByteArray getJson();
    virtual QJsonObject getJsonObject() = 0;
};

#endif // CJSONSERIALIZABLE_H
