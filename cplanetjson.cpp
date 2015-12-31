#include "cplanetjson.h"

CPlanetJson::CPlanetJson(const CPlanetMap& pMap)
{
    QJsonArray jMapArray;
    for(size_t X = 0; X < pMap.getWidth(); ++X)
    {
        QJsonArray jRowArray;
        for(size_t Y = 0; Y < pMap.getHeight(); ++Y)
        {
            CCell* pCell = pMap.getCellByCoordinates(X, Y);

            QJsonObject jCellObject;
            jCellObject.insert("Temperature", QJsonValue(pCell->nTemperature));
            jCellObject.insert("Height", QJsonValue(pCell->nHeight));

            QJsonValue jCellValue(jCellObject);
            jRowArray.append(jCellValue);

        }
        QJsonValue jRowValue(jRowArray);
        jMapArray.append(jRowValue);
    }
    QJsonValue jMapValue(jMapArray);
    QJsonValue jWidthValue(pMap.getWidth());
    QJsonValue jHeightValue(pMap.getHeight());

    QJsonObject jMainObject;
    jMainObject.insert("Map", jMapValue);
    jMainObject.insert("Width", jWidthValue);
    jMainObject.insert("Height", jHeightValue);

    QJsonDocument jDocument;
    jDocument.setObject(jMainObject);
    m_aJson = jDocument.toJson(QJsonDocument::Indented);
}


QByteArray CPlanetJson::getJson()
{
    return m_aJson;
}
