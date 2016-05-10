#include "common.h"

QString stringListToString(QStringList StringList)
{
    QString Result;
    Result.append("[");
    bool bFirst = true;

    for(QStringList::iterator it = StringList.begin(); it != StringList.end(); ++it)
    {
        if(bFirst == false)
        {
            Result.append(", ");
        }
        Result.append("\"");
        Result.append(*it);
        Result.append("\"");
        bFirst = false;
    }
    Result.append("]");
    return Result;
}
