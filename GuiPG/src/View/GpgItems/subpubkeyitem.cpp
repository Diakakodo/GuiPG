#include "subpubkeyitem.h"

#include <QMenu>

#include "../../Keys/signature.h"
#include "signatureitem.h"

SubPubKeyItem::SubPubKeyItem(SubPubKey* sub) : GpgItem(sub)
{
    m_sub = sub;
    setText(COL_ALGO, sub->getAlgo());
    setText(COL_CREATION, sub->getCreationDate().toString("dd/MM/yyyy"));
    setText(COL_ID, sub->getKeyId());
    setText(COL_LENGTH, QString::number(sub->getLength()));
    setText(COL_VALIDITY, sub->getValidity());
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
