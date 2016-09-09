#ifndef SMESSAGE
#define SMESSAGE

#include <string>

#define MESSAGE_DROP_SCRIPT "DROP TABLE IF EXISTS `Messages`;"
#define MESSAGE_CREATE_SCRIPT "CREATE TABLE `Messages` ( \
`id` INTEGER NOT NULL AUTO_INCREMENT, \
`fk_Users_id_from` INTEGER NOT NULL, \
`fk_Users_id_to` INTEGER NOT NULL, \
`time` DATETIME NOT NULL, \
`subject` VARCHAR(50) NOT NULL, \
`text` MEDIUMTEXT NOT NULL, \
`anonymously` bit NOT NULL DEFAULT False, \
PRIMARY KEY (`id`), \
KEY (`fk_Users_id_from`), \
KEY (`fk_Users_id_to`) \
);"

#define MESSAGE_CONNECT_SCRIPT_1 "ALTER TABLE `Messages` ADD FOREIGN KEY (fk_Users_id_from) REFERENCES `Users` (`id`);"
#define MESSAGE_CONNECT_SCRIPT_2 "ALTER TABLE `Messages` ADD FOREIGN KEY (fk_Users_id_to) REFERENCES `Users` (`id`);"
#define MESSAGE_UTF8_SCRIPT "ALTER TABLE `Messages` ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;"

struct SMessage
{
public:
    SMessage(){}
    SMessage(int nId,
            int nSenderId,
            int nRecieverId,
            QString sTime,
            QString sSubject,
            QString sText,
            bool bAnonymously):
        m_nId(nId),
        m_nSenderId(nSenderId),
        m_nRecieverId(nRecieverId),
        m_sTime(sTime),
        m_sSubject(sSubject),
        m_sText(sText),
        m_bAnonymously(bAnonymously)
    {}
    SMessage(int nSenderId,
            int nRecieverId,
            QString sTime,
            QString sSubject,
            QString sText,
            bool bAnonymously):
        m_nSenderId(nSenderId),
        m_nRecieverId(nRecieverId),
        m_sTime(sTime),
        m_sSubject(sSubject),
        m_sText(sText),
        m_bAnonymously(bAnonymously)
    {}
    int m_nId = 0;
    int m_nSenderId;
    int m_nRecieverId;
    QString m_sTime;
    QString m_sSubject;
    QString m_sText;
    bool m_bAnonymously;

};

#endif // SMESSAGE

