#include "primaseckeyitem.h"
#include "uiditem.h"
#include <QMenu>

PrimaSecKeyItem::PrimaSecKeyItem(PrimaSecKey *sec) : SubSecKeyItem(sec)
{
    m_sec = sec;

    setText(COL_EXPIRATION, sec->getExpirationDate().toString("dd/MM/yyyy"));
    Uid* uid = sec->getUid();
    if (uid != nullptr) {
        addChild(new UidItem(uid));
    }
    for (SubSecKey* ssc : sec->getSubSecKeyList()) {
        addChild(new SubSecKeyItem(ssc));
    }
}

PrimaSecKeyItem::~PrimaSecKeyItem()
{

}

void PrimaSecKeyItem::showMenu(const QPoint &pos) {
    QMenu* menu = new QMenu(treeWidget());
    menu->addAction("Test Clef Privée primaire");
    menu->popup(treeWidget()->viewport()->mapToGlobal(pos));
}
