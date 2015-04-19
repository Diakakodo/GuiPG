#include "primapubkeyitem.h"
#include "uiditem.h"
#include "subpubkeyitem.h"
#include "../gpgtreewidget.h"
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <QSignalMapper>

// Initialisation de la hash map (action -> numéro de la confiance)
// Les noms sont défini dans la X_Maccro X_COLUMNS et le numéro est donné par
// l'ordre de définition des collones dans la X_MACRO.
QHash<int, QAction*> PrimaPubKeyItem::trustActions = []() -> QHash<int, QAction*> {
    // Ce tableau permet de récupérer le nom de l'action a partir de son numéro d'enum.
    #define X(id, str) str,
    QString actionName[NB_TRUST + 1] = {
        X_TRUSTS
        NULL
    };
    #undef X
    QHash<int, QAction*> hash;
    for (int i = 0; i < PrimaPubKeyItem::NB_TRUST; ++i) {
        hash.insert(i, new QAction(actionName[i], nullptr));
    }
    return hash;
}();


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

    QMenu* changeTrustMenu = new QMenu("Modifier la confiance", menu);
    for (int i = 0; i < NB_TRUST; i++) {
        QAction* a = new QAction(trustActions.value(i)->text(), this);
        if (PrimaPubKey::trustToStr(m_pub->getTrust()) == a->text()) {
            a->setCheckable(true);
            a->setChecked(true);
        }
        changeTrustMenu->addAction(a);
        QSignalMapper *pSignalMapper = new QSignalMapper(this);
        connect(pSignalMapper, SIGNAL(mapped(int)), SLOT(trust(int)));
        connect(a,  SIGNAL(triggered()), pSignalMapper, SLOT(map()));
        pSignalMapper->setMapping(a,i+1);
    }

    menu->addMenu(changeTrustMenu);

    menu->popup(treeWidget()->viewport()->mapToGlobal(pos));
}

void PrimaPubKeyItem::sign() {
    KeyManager* keyManager = ((GpgTreeWidget*) treeWidget())->getKeyManager();

    QStringList opt;
    opt << "--status-fd=1"
        << "--command-fd=0";
        //<< "--default-key"
        //<< "" // TODO récupérer le keyId de la clé privée avec laquelle on veut signer.
    QStringList interactions;
    interactions << "o";
    Action actionSign("--sign-key", QStringList(m_pub->getKeyId()), opt, interactions);
    GPGManager* gpg = new GPGManager(((GpgTreeWidget*) treeWidget())->getProfile());
    gpg->setAction(actionSign);
    gpg->execute();
}

void PrimaPubKeyItem::trust(int value) {
    QStringList opt;
    opt << "--status-fd=1"
        << "--command-fd=0";
    QStringList interactions;
    interactions << "trust"
                 << QString::number(value)
                 << "save";
    Action actionSign("--edit-key", QStringList(m_pub->getKeyId()), opt, interactions);
    GPGManager* gpg = new GPGManager(((GpgTreeWidget*) treeWidget())->getProfile());
    gpg->setAction(actionSign);
    gpg->execute();
}
