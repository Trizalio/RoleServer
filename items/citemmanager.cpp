#include "citemmanager.h"

CItemManager::CItemManager()
{

}

IItem* CItemManager::parseItem(SItem Item)
{
    qDebug() << __FUNCTION__;

    QJsonParseError jError;
    QJsonDocument jDocument = QJsonDocument::fromJson(Item.m_sJsonData.toLatin1(), &jError);
    if(jError.error != QJsonParseError::NoError
            || !jDocument.isObject())
    {
        qDebug() << "parse error";
        return 0;
    }
    QJsonObject jItem = jDocument.object();
    if(!jItem.contains("type"))
    {
        qDebug() << "type not specified";
        return 0;
    }
    QJsonValue jType = jItem.take("type");
    if(!jType.isString())
    {
        qDebug() << "wrong type";
        return 0;
    }
    QString sType = jType.toString();

    if(sType == TYPE_HEALSHOT)
    {
        qDebug() << "recognised healshot";
        return new SHealShot();
    }
    if(sType == TYPE_AIRLOCK)
    {
        qDebug() << "recognised airlock";
        return new SAirlock();
    }
    if(sType == TYPE_AIRCELL)
    {
        qDebug() << "recognised aircell";
        if(!jItem.contains("size"))
        {
            qDebug() << "size not specified";
            return new SAirCell();
        }

        QJsonValue jSize = jItem.take("size");
        if(!jSize.isDouble())
        {
            qDebug() << "wrong type";
            return new SAirCell();
        }
        int nSize = jType.toInt();
        return new SAirCell(nSize);
    }
    qDebug() << "unrecognised type";
    return 0;
}

