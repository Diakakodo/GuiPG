#include "primapubkeyitem.h"
#include "uiditem.h"
#include "subpubkeyitem.h"
#include "../gpgtreewidget.h"
#include <QMenu>
#include <QAction>

#include "../../GPG/action.h"

PrimaPubKeyItem::PrimaPubKeyItem(PrimaPubKey *pub) : PubKeyItem(pub)
{
    m_pub = pub;

    Uid* primaryUid = pub->getPrimaryUid();
    if (primaryUid != nullptr) {
        setText(COL_NAME, primaryUid->getName());
        setText(COL_MAIL, primaryUid->getMail());
    }
    setText(COL_TRUST, PrimaPubKey::trustToStr(pub->getTrust()));
    if (pub->getTrust() == TRUST_INVALID) {
        setTextColor(COL_TRUST, QColor(255,255,255));
    }
    setBackgroundColor(COL_TRUST, Configuration::getDefaultValidityColor(pub->getTrust()));
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
    menu->addAction("Signer", this, SLOT(sign()));
    menu->popup(treeWidget()->viewport()->mapToGlobal(pos));
}
#include <QDebug>
void PrimaPubKeyItem::sign() {
    KeyManager* keyManager = ((GpgTreeWidget*) treeWidget())->getKeyManager();
    for (PrimaSecKey* sec : keyManager->getSecKeys()) {
        qDebug() << "sec : " << sec->getFpr();
        for (SubSecKey* ssb : sec->getSubSecKeyList()) {
            qDebug() << "ssb : " << ssb->getFpr();
        }
    }
    QStringList opt;
    opt << "";
    QStringList interactions;
    interactions << "";
    Action actionSign("--sign-key", QStringList(), opt, interactions);
    qDebug() << "sign";
}
