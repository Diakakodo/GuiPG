#include "pubkeyitem.h"


#include <QMenu>

PubKeyItem::PubKeyItem(PubKey* pub) : GpgItem(pub)
{
    m_pub = pub;

    setText(COL_ALGO, pub->getAlgo());
    setText(COL_CAPACITY, pub->getCapabilities());
    setText(COL_CREATION, pub->getCreationDate().toString("dd/MM/yyyy"));
    setText(COL_EXPIRATION, pub->getExpirationDate().toString("dd/MM/yyyy"));
    setText(COL_ID, pub->getKeyId());
    setText(COL_LENGTH, QString::number(pub->getLength()));
    setText(COL_VALIDITY, pub->getValidity());
}

PubKeyItem::~PubKeyItem()
{

}

void PubKeyItem::showMenu(const QPoint &pos) {
    QMenu* menu = new QMenu(treeWidget());
    menu->addAction("Test Clef public");
    menu->popup(treeWidget()->viewport()->mapToGlobal(pos));
}
