#include "subpubkeyitem.h"

#include <QMenu>

#include "../../Keys/signature.h"
#include "signatureitem.h"

SubPubKeyItem::SubPubKeyItem(SubPubKey* sub) : PubKeyItem(sub)
{
    m_sub = sub;
    setText(COL_NAME, "Sous clef " + GpgObject::algoToStr(sub->getAlgo()));

    for (Signature* sig : sub->getSignatures()) {
        addChild(new SignatureItem(sig));
    }

    if (sub->hasSubSecKey()) {
        setIcon(COL_NAME, QIcon(":/icones/res/" ICON_DOUBLE_SUBKEY_PATH));
    } else {
        setIcon(COL_NAME, QIcon(":/icones/res/" ICON_SINGLE_SUBKEY_PATH));
    }
}

SubPubKeyItem::~SubPubKeyItem()
{

}


void SubPubKeyItem::showMenu(const QPoint &pos) {
    if (pos.isNull()) {
        // not used
    }
    //QMenu* menu = new QMenu(treeWidget());
    //menu->addAction("Test Sous clef public");
    //menu->popup(treeWidget()->viewport()->mapToGlobal(pos));
}
