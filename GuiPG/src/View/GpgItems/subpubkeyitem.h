#ifndef SUBPUBKEYITEM_H
#define SUBPUBKEYITEM_H

#include "subseckeyitem.h"
#include "../../Keys/subpubkey.h"

class SubPubKeyItem : public SubSecKeyItem
{
    public:
        SubPubKeyItem(SubPubKey* sub);
        ~SubPubKeyItem();
        void showMenu(const QPoint &pos);
    private:
        SubPubKey* m_sub;
};

#endif // SUBPUBKEYITEM_H
