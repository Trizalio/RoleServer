#ifndef CCONNECTIONKEEPER_H
#define CCONNECTIONKEEPER_H

#include <QObject>
#include <QTimer>
#include "orm/corm.h"

class CConnectionKeeper : public QObject
{
    Q_OBJECT
public:
    CConnectionKeeper(COrm* pOrm);

signals:

public slots:
    void update();
private:
    COrm* m_pOrm;
};

#endif // CCONNECTIONKEEPER_H
