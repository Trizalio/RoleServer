#include "cjsonserializable.h"

CJsonSerializable::CJsonSerializable()
{

}

QByteArray CJsonSerializable::getJson()
{
    QJsonObject jObject = getJsonObject();

    QJsonDocument jDocument;
    jDocument.setObject(jObject);
    QByteArray aJson = jDocument.toJson(QJsonDocument::Indented);

    return aJson;
}

