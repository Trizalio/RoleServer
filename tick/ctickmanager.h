#ifndef CTICKMANAGER_H
#define CTICKMANAGER_H

#include "orm/corm.h"
#include "items/citemmanager.h"

class CTickManager : public QObject
{
    Q_OBJECT

signals:
    void statusChange(QByteArray sStatusChange, int nPlayerId);
    void statusUpdate(int nPlayerId);
public slots:
    void tick();

public:
    CTickManager(COrm *pOrm);


private:
    void update(std::vector<SUserStat>& aUserStats);
    void cureStun(std::vector<SUserStat>& aUserStats);
    void drainOxygen(std::vector<SUserStat>& aUserStats);

    COrm* m_pOrm;
};

#endif // CTICKMANAGER_H
