#include "pubkeyitem.h"


#include <QMenu>

PubKeyItem::PubKeyItem(PubKey* pub) : SubSecKeyItem(pub)
{
    m_pub = pub;

    setText(COL_CAPACITY, pub->getCapabilities());
    setText(COL_EXPIRATION, pub->getExpirationDate().toString("dd/MM/yyyy"));
    setText(COL_VALIDITY, GpgObject::validityToStr(pub->getValidity()));
    if (pub->getValidity() == VALIDITY_INVALID) {
        setTextColor(COL_VALIDITY, QColor(255,255,255));
    }
    setBackgroundColor(COL_VALIDITY, Configuration::getDefaultValidityColor(pub->getValidity()));
}

PubKeyItem::~PubKeyItem()
{

}

void PubKeyItem::showMenu(const QPoint &pos) {
    if (pos.isNull()) {
        // not used
    }
    //QMenu* menu = new QMenu(treeWidget());
    //menu->addAction("Test Clef public");
    //menu->popup(treeWidget()->viewport()->mapToGlobal(pos));
}
