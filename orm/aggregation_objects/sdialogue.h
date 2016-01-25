#ifndef SDIALOGUE
#define SDIALOGUE

#include <vector>

#include "orm/sql_objects/smessage.h"

struct SDialogue
{
public:
    SDialogue(){}
//    SDialogue(int nId,
//            std::string sLogin,
//            std::string sPasswordHash):
//        m_nId(nId),
//        m_sLogin(sLogin),
//        m_sPasswordHash(sPasswordHash)
//    {}

    std::vector<SMessage> m_aMessages;
};

#endif // SDIALOGUE

