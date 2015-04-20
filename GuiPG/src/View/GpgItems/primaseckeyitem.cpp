#include "primaseckeyitem.h"
#include "uiditem.h"
#include "../gpgtreewidget.h"
#include "../keyexport.h"
#include <QMenu>

PrimaSecKeyItem::PrimaSecKeyItem(PrimaSecKey *sec) : SubSecKeyItem(sec)
{
    m_sec = sec;

    setText(COL_EXPIRATION, sec->getExpirationDate().toString("dd/MM/yyyy"));
    for (Uid* uid : sec->getUidList()) {
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
    menu->addAction("Exporter", this, SLOT(exportKey()));
    menu->popup(treeWidget()->viewport()->mapToGlobal(pos));
}

void PrimaSecKeyItem::exportKey() {
    KeyManager* keyManager = ((GpgTreeWidget*) treeWidget())->getKeyManager();
    KeyExport keyExport(keyManager->getMainWindow(), KeyExport::SECRET_KEYS, QStringList(m_sec->getKeyId()));
    keyExport.show();
    keyExport.exec();
}
