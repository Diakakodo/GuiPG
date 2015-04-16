#include "primapubkeyitem.h"
#include "uiditem.h"
#include "subpubkeyitem.h"
#include <QMenu>

PrimaPubKeyItem::PrimaPubKeyItem(PrimaPubKey *pub) : PubKeyItem(pub)
{
    m_pub = pub;

    setText(COL_TRUST, pub->getTrust());
    for (Uid* uid : pub->getUidList()) {
        addChild(new UidItem(uid));
    }

    for (SubPubKey* sub : pub->getSubPubKeyList()) {
        addChild(new SubPubKeyItem(sub));
    }
}

PrimaPubKeyItem::~PrimaPubKeyItem()
{

}

void PrimaPubKeyItem::showMenu(const QPoint &pos) {
    QMenu* menu = new QMenu(treeWidget());
    menu->addAction("Test Clef Publique primaire");
    menu->popup(treeWidget()->viewport()->mapToGlobal(pos));
}
