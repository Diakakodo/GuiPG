#ifndef SUBPUBKEYITEM_H
#define SUBPUBKEYITEM_H

#include "gpgitem.h"
#include "../../Keys/subpubkey.h"

class SubPubKeyItem : public GpgItem
{
    public:
        SubPubKeyItem(SubPubKey* sub);
        ~SubPubKeyItem();
        void showMenu(const QPoint &pos);
    private:
        SubPubKey* m_sub;
};

#endif // SUBPUBKEYITEM_H
