#include "cplanetthread.h"


CPlanetThread::CPlanetThread()
{
}

void CPlanetThread::run()
{
    m_PlanetMap.loadPlanetFromDB();
    while(true)
    {
        radiateSun();
        rotateSun();

        radiatePlanet();

        m_PlanetMap.writePlanetToDB();
        msleep(100);
    }

}


void CPlanetThread::radiateSun()
{

}

void CPlanetThread::rotateSun()
{

}

void CPlanetThread::radiatePlanet()
{

}
