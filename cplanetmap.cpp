#include "cplanetmap.h"


CPlanetMap::CPlanetMap()
{
    for(int i = 0; i < MAP_WIDTH; ++i)
    {
        m_aaMap.push_back(std::vector<CCell*>());
        for(int j = 0; j < MAP_HEIGHT; ++j)
        {
            m_aaMap.at(i).push_back(new CCell());
        }
    }
    initShifting();
//    qDebug() << "lanbda start";
    forEachCell([](CCell* pCell, double fX, double fY){
        pCell->nTemperature = fX+fY;
    });
    forEachCell([](CCell* pCell, double fX, double fY){
        pCell->nHeight = int(fX+fY) % int((MAP_WIDTH + MAP_HEIGHT) / 10);
    });
//    forEachCell([](CCell* pCell, double fX, double fY){
//        qDebug() << pCell->nTemperature;
//    });
//    qDebug() << "lanbda end";

}

double CPlanetMap::getStep(double fY) const
{
    double fRelativeHeight = abs(((fY + 0.5) / MAP_HEIGHT) - 0.5) * 2;
    double Step = 1/(1.0 - fRelativeHeight);
    return Step;
}

void CPlanetMap::initShifting()
{
    for (int Y = 0; Y < MAP_HEIGHT; ++Y) {
        double fWidth = getStep(Y);
        double fNextCellX = 0;
        for (int X = 0; X < MAP_WIDTH; ++X) {
            CCell* pCurCell = m_aaMap[X][Y];
            if(X >= fNextCellX){
                pCurCell->bReal = true;
                fNextCellX += fWidth;
            } else {
                pCurCell->bReal = false;
            }
        }
    }
    for (int Y = 0; Y < MAP_HEIGHT; ++Y) {
        m_anAmount.push_back(0);
        for (int X = 0; X < MAP_WIDTH; ++X) {
            CCell* pCurCell = m_aaMap[X][Y];
            if(pCurCell->bReal){
                m_anAmount[Y] += 1;
            }
        }
        m_afWidth.push_back(MAP_WIDTH / m_anAmount[Y]);
    }
}



CCell* CPlanetMap::getCellByCoordinates(double X, double Y) const
{
    double Step = getStep(Y);
    double RealX = floor(floor(X / Step) * Step);
    return m_aaMap[RealX][Y];
}

void CPlanetMap::forEachCell(std::function<void(CCell*, double, double)> Action)
{
    for (int Y = 0; Y < MAP_HEIGHT; Y++) {
        double RealX = 0;
        double Width = m_afWidth[Y];
        for (int X = 0; X < MAP_WIDTH; X++) {
            CCell* CurCell = m_aaMap[X][Y];
            if(CurCell->bReal){
                Action(CurCell, RealX, Y);
                //action.call(this, CurCell, RealX, Y);
                RealX += Width;
            }
        }
    }
}

double CPlanetMap::getHeight() const
{
    return MAP_HEIGHT;
}

double CPlanetMap::getWidth() const
{
    return MAP_WIDTH;
}

void CPlanetMap::loadPlanetFromDB()
{

}

void CPlanetMap::writePlanetToDB()
{

}

/*

*/
