#ifndef CPLANETTHREAD_H
#define CPLANETTHREAD_H


#include <QThread>
#include <QDebug>

#include "cplanetmap.h"

class CPlanetThread : public QThread
{
public:
    CPlanetThread();

protected:
    void run();

private:

    void radiateSun();
    void rotateSun();

    void radiatePlanet();

    CPlanetMap m_PlanetMap;
};

#endif // CPLANETTHREAD_H
