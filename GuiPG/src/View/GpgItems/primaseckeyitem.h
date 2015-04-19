#ifndef PRIMASECKEYITEM_H
#define PRIMASECKEYITEM_H

#include "subseckeyitem.h"
#include "../../Keys/primaseckey.h"

class PrimaSecKeyItem : public SubSecKeyItem
{
    public:
        PrimaSecKeyItem(PrimaSecKey* sec);
        ~PrimaSecKeyItem();

        void showMenu(const QPoint &pos);

    private:
        PrimaSecKey* m_sec;

    public slots:
        void exportKey();
};

#endif // PRIMASECKEYITEM_H
