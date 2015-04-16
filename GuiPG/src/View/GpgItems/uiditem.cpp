#include "uiditem.h"
#include "signatureitem.h"
#include <QMenu>

UidItem::UidItem(Uid* uid) : GpgItem (uid)
{
    m_uid = uid;
    setText(COL_CREATION, uid->getCreationDate().toString("dd/MM/yyyy"));
    setText(COL_NAME, uid->getName());
    setText(COL_MAIL, uid->getMail());
    setText(COL_VALIDITY, uid->getValidity());
    setText(COL_ID, uid->getFpr());
    for (Signature* sig : uid->getSigList()) {
        addChild(new SignatureItem(sig));
    }
}

UidItem::~UidItem()
{

}

void UidItem::showMenu(const QPoint &pos) {
    QMenu* menu = new QMenu(treeWidget());
    menu->addAction("Test uid");
    menu->popup(treeWidget()->viewport()->mapToGlobal(pos));
}
