#ifndef UIDITEM_H
#define UIDITEM_H

#include "gpgitem.h"
#include "../../Keys/uid.h"

#define ICON_UID_PATH "/Icones/uid.png"

class UidItem : public GpgItem
{
    public:
        UidItem(Uid *uid);
        ~UidItem();
        void showMenu(const QPoint &pos);
    private:
        Uid* m_uid;
};

#endif // UIDITEM_H
