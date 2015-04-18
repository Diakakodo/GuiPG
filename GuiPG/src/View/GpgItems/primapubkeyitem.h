#ifndef PRIMAPUBKEYITEM_H
#define PRIMAPUBKEYITEM_H

#include "pubkeyitem.h"
#include "../../Keys/primapubkey.h"

class PrimaPubKeyItem : public PubKeyItem
{
        Q_OBJECT
    public:
        PrimaPubKeyItem(PrimaPubKey* pub);
        ~PrimaPubKeyItem();

        void showMenu(const QPoint &pos);

    public slots:
        void sign();


    private:
        PrimaPubKey* m_pub;

};

#endif // PRIMAPUBKEYITEM_H
