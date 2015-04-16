#include "subpubkeyitem.h"

#include <QMenu>

#include "../../Keys/signature.h"
#include "signatureitem.h"

SubPubKeyItem::SubPubKeyItem(SubPubKey* sub) : PubKeyItem(sub)
{
    m_sub = sub;

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
