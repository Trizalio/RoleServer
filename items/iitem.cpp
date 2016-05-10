#include "iitem.h"



SItem IItem::toItem()
{
    QJsonObject jObject = getItemJson();

    QJsonDocument jDocument;
    jDocument.setObject(jObject);
    QString aJson = jDocument.toJson(QJsonDocument::Indented);

    return SItem(aJson.toStdString());
}
