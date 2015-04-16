#ifndef UIDITEM_H
#define UIDITEM_H

#include "gpgitem.h"
#include "../../Keys/uid.h"

class UidItem : public GpgItem
{
    public:
        UidItem(Uid *uid);
        ~UidItem();
    private:
        Uid* m_uid;
};

#endif // UIDITEM_H
