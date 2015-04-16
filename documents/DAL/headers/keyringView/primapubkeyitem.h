#ifndef PRIMAPUBKEYITEM_H
#define PRIMAPUBKEYITEM_H

#include "pubkeyitem.h"
#include "../../Keys/primapubkey.h"

class PrimaPubKeyItem : public PubKeyItem
{
    public:
        PrimaPubKeyItem(PrimaPubKey* pub);
        ~PrimaPubKeyItem();

        void showMenu(const QPoint &pos);

    private:
        PrimaPubKey* m_pub;

};

#endif // PRIMAPUBKEYITEM_H
