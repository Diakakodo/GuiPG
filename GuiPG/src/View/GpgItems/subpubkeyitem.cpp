#include "subpubkeyitem.h"

#include <QMenu>

#include "../../Keys/signature.h"
#include "signatureitem.h"

SubPubKeyItem::SubPubKeyItem(SubPubKey* sub) : SubSecKeyItem(sub)
{
    m_sub = sub;

    setText(COL_EXPIRATION, sub->getExpirationDate().toString("dd/MM/yyyy"));
    setText(COL_CAPACITY, sub->getCapabilities());
    for (Signature* sig : sub->getSignatures()) {
        addChild(new SignatureItem(sig));
    }
}

SubPubKeyItem::~SubPubKeyItem()
{

}


void SubPubKeyItem::showMenu(const QPoint &pos) {
    QMenu* menu = new QMenu(treeWidget());
    menu->addAction("Test Sous clef public");
    menu->popup(treeWidget()->viewport()->mapToGlobal(pos));
}
