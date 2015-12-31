#ifndef CPLANETJSON_H
#define CPLANETJSON_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include "cplanetmap.h"

class CPlanetJson
{
public:
    CPlanetJson(const CPlanetMap& pMap);
    QByteArray getJson();

private:
    //QJsonObject m_JsonObject;
    //QJsonDocument m_jDocument;
    QByteArray m_aJson;
};

#endif // CPLANETJSON_H
