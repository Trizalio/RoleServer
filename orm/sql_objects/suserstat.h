#ifndef SUSERSTAT_H
#define SUSERSTAT_H

#include <QDebug>

#include "cjsonserializable.h"


#define USER_STAT_DROP_SCRIPT "DROP TABLE IF EXISTS `UserStats`;"

#define USER_STAT_CREATE_SCRIPT "CREATE TABLE `UserStats` ( \
`id` INTEGER NOT NULL, \
`hp_max` INTEGER NOT NULL, \
`hp` INTEGER NOT NULL, \
`pp` INTEGER NOT NULL, \
`air` INTEGER NOT NULL, \
`fk_Items_id_air` INTEGER NULL DEFAULT NULL, \
`stun` INTEGER NOT NULL DEFAULT 0, \
PRIMARY KEY (`id`) \
);"

#define USER_STAT_CONNECT_SCRIPT_1 "ALTER TABLE `UserStats` ADD FOREIGN KEY (id) REFERENCES `Users` (`id`);"
#define USER_STAT_CONNECT_SCRIPT_2 "ALTER TABLE `UserStats` ADD FOREIGN KEY (fk_Items_id_air) REFERENCES `Items` (`id`);"

#define USER_STAT_UTF8_SCRIPT "ALTER TABLE `UserStats` ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;"

#define DEFAULT_AIR_SEC 7 * 60
#define DEFAULT_STUN_SEC 3 * 60

enum EUserStates
{
    AlreadyDead,
    Died,
    Damaged,
    Ok,
    Healed,
    HealedToCap,
    AlreadyFull
};

class SUserStat : public CJsonSerializable
{
public:
    SUserStat();
    SUserStat(int nHpMax,
            int nHp,
            int nPp,
            int nAir,
            int nAirId);
    SUserStat(int nId,
            int nHpMax,
            int nHp,
            int nPp,
            int nAir,
            int nAirId,
            int nStun);

    QJsonObject getJsonObject() override;

    int m_nId = 0;

    int m_nHpMax = 0;
    int m_nHp = 0;

    int m_nPp = 0;

    int m_nAir = 0;
    int m_nAirId = 0;

    int m_nStun = 0;

    bool m_bChanged = false;
};

#endif // SUSERSTAT_H
