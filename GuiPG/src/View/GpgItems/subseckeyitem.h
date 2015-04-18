#ifndef SUBSECKEYITEM_H
#define SUBSECKEYITEM_H

#include "gpgitem.h"
#include "../../Keys/subseckey.h"

class SubSecKeyItem : public GpgItem {
    public:
        SubSecKeyItem(SubSecKey* subSecKey);
        ~SubSecKeyItem();

        void showMenu(const QPoint &pos);

    private:
        SubSecKey* m_sec;
};

#endif // SUBSECKEYITEM_H
