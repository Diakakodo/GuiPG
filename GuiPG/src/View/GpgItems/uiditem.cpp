#include "uiditem.h"
#include "signatureitem.h"
#include <QMenu>
#include "../gpgtreewidget.h"
#include <QDebug>
UidItem::UidItem(Uid* uid) : GpgItem (uid)
{
    m_uid = uid;
    setText(COL_NAME, uid->getName());
    setText(COL_MAIL, uid->getMail());
    setText(COL_VALIDITY, GpgObject::validityToStr(uid->getValidity()));
    if (uid->getValidity() == VALIDITY_INVALID) {
        setTextColor(COL_VALIDITY, QColor(255,255,255));
    }
    setBackground(COL_VALIDITY, Configuration::getDefaultValidityColor(uid->getValidity()));
    for (Signature* sig : uid->getSigList()) {
        addChild(new SignatureItem(sig));
    }

    setIcon(COL_NAME, QIcon(":/icones/res/" ICON_UID_PATH));
}

UidItem::~UidItem()
{

}

void UidItem::showMenu(const QPoint &pos) {
    if (pos.isNull()) {
        // not used
    }
    //QMenu* menu = new QMenu(treeWidget());
    //menu->addAction("Test uid");
    //menu->popup(treeWidget()->viewport()->mapToGlobal(pos));
}
