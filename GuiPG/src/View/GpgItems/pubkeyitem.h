#ifndef PUBKEYITEM_H
#define PUBKEYITEM_H

#include "../../Keys/pubkey.h"
#include "gpgitem.h"

class PubKeyItem : public GpgItem
{
    public:
        PubKeyItem(PubKey* pud);
        ~PubKeyItem();
        void showMenu(const QPoint &pos);

    private:
        PubKey* m_pub;

};

#endif // PUBKEYITEM_H
