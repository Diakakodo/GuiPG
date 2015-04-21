#ifndef SUBPUBKEYITEM_H
#define SUBPUBKEYITEM_H

#include "pubkeyitem.h"
#include "../../Keys/subpubkey.h"

#define ICON_SINGLE_SUBKEY_PATH "/Icones/single_subkey.png"
#define ICON_DOUBLE_SUBKEY_PATH "/Icones/double_subkeys.png"

class SubPubKeyItem : public PubKeyItem
{
    public:
        SubPubKeyItem(SubPubKey* sub);
        ~SubPubKeyItem();
        void showMenu(const QPoint &pos);
    private:
        SubPubKey* m_sub;
};

#endif // SUBPUBKEYITEM_H
