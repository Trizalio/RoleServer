#include "cconnectionkeeper.h"

CConnectionKeeper::CConnectionKeeper(COrm* pOrm):
    m_pOrm(pOrm)
{

    QTimer* pTimer = new QTimer();
    connect(pTimer, SIGNAL(timeout()), this, SLOT(update()));
    pTimer->start(60 * 60 * 1000);
}

void CConnectionKeeper::update()
{
    m_pOrm->findUserById(0);
}

