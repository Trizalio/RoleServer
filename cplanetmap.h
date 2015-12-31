#ifndef CPLANETMAP_H
#define CPLANETMAP_H

#include <vector>
#include <math.h>
#include <stdlib.h>

/// lambda
#include <functional>
#include <iostream>
///Qt
#include <QDebug>

#include "ccell.h"

#define MAP_HEIGHT 20
#define MAP_WIDTH (MAP_HEIGHT * M_PI)

class CPlanetMap
{
public:
    CPlanetMap();

    void forEachCell(std::function<void(CCell *, double, double)> Action);

    double getHeight() const;
    double getWidth() const;

    void loadPlanetFromDB();
    void writePlanetToDB();

    CCell* getCellByCoordinates(double X, double Y) const;

private:
    double getStep(double fY) const;
    void initShifting();


    std::vector<std::vector<CCell*> > m_aaMap;
    std::vector<unsigned short > m_anAmount;
    std::vector<double > m_afWidth;
};

#endif // CPLANETMAP_H

