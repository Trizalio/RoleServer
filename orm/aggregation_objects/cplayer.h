#ifndef CPLAYER_H
#define CPLAYER_H

#include "orm/sql_objects/splayer.h"
#include "orm/sql_objects/scredential.h"

class CPlayer : public CJsonSerializable
{
public:
    CPlayer(SPlayer Player, SCredential Credential);

    QJsonObject getJsonObject() override;
private:

    SPlayer m_Player;
    SCredential m_Credential;
};

#endif // CPLAYER_H
