#include "primapubkeyitem.h"
#include "uiditem.h"
#include "subpubkeyitem.h"
#include "../gpgtreewidget.h"
#include "../keyexport.h"
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
    m_pos = pos;
    m_menu = new QMenu(treeWidget());
    m_menu->addAction("Signer", this, SLOT(sign()));
    m_menu->addAction("Exporter la clé publique", this, SLOT(exportPublicKey()));
    if (m_pub->hasPrimaSecKey()) {
        m_menu->addAction("Exporter la clé secrète", this, SLOT(exportSecretKey()));
    }
    getPossibleTrustValue();
}

void PrimaPubKeyItem::sign() {
    //KeyManager* keyManager = ((GpgTreeWidget*) treeWidget())->getKeyManager();

    QStringList opt;
    opt << "--status-fd=1"
        << "--command-fd=0";
        //<< "--default-key"
        //<< "" // TODO récupérer le keyId de la clé privée avec laquelle on veut signer.
    QStringList interactions;
    interactions << "y";
    Action actionSign("--sign-key", QStringList(m_pub->getKeyId()), opt, interactions);
    m_gpg = new GPGManager(((GpgTreeWidget*) treeWidget())->getProfile());
    connect(m_gpg, &GPGManager::finished, this, &GpgItem::changed);
    m_gpg->setAction(actionSign);
    m_gpg->execute();
}

void PrimaPubKeyItem::trust(int value) {
    QStringList opt;
    opt << "--status-fd=1"
        << "--command-fd=0";
    QStringList interactions;
    if (value != EDIT_TRUST_ULTIMATELY + 1) {
        interactions << "trust"
                     << QString::number(value)
                     << "save";
    } else {
        interactions << "trust"
                     << QString::number(value)
                     << "y"
                     << "save";
    }
    Action actionSign("--edit-key", QStringList(m_pub->getKeyId()), opt, interactions);
    m_gpg = new GPGManager(((GpgTreeWidget*) treeWidget())->getProfile());
    m_gpg->setAction(actionSign);

    connect(m_gpg, &GPGManager::finished, this, &GpgItem::changed);
    m_gpg->execute();
}

void PrimaPubKeyItem::exportPublicKey() {
    KeyManager* keyManager = ((GpgTreeWidget*) treeWidget())->getKeyManager();
    KeyExport keyExport(keyManager->getMainWindow(), KeyExport::PUBLIC_KEYS, QStringList(m_pub->getKeyId()));
    keyExport.show();
    keyExport.exec();
}

void PrimaPubKeyItem::exportSecretKey() {
    KeyManager* keyManager = ((GpgTreeWidget*) treeWidget())->getKeyManager();
    KeyExport keyExport(keyManager->getMainWindow(), KeyExport::SECRET_KEYS, QStringList(m_pub->getKeyId()));
    keyExport.show();
    keyExport.exec();
}

void PrimaPubKeyItem::setPossibleTrustValue(int s, QString output) {
    m_possibleTrustValue.clear();
    disconnect(m_gpg, &GPGManager::finished, this, &PrimaPubKeyItem::getPossibleTrustValue);
    delete m_gpg;
    if (s) {
        QStringList l = output.split("\n", QString::SkipEmptyParts);
        for (QString line : l) {
            if (line.length() > 5 && line.at(4) == '=') {
                if (line.at(2).digitValue() > 0 && line.at(2).digitValue() < 6)
                    m_possibleTrustValue.append(line.at(2).digitValue());
            }
        }
    }
    QMenu* changeTrustMenu = new QMenu("Modifier la confiance", m_menu);
    for (int i = 0; i < NB_TRUST; i++) {
        if (m_possibleTrustValue.contains(i+1)) {
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
    }

    m_menu->addMenu(changeTrustMenu);

    m_menu->popup(treeWidget()->viewport()->mapToGlobal(m_pos));
}

void PrimaPubKeyItem::getPossibleTrustValue() {
    QStringList opt;
    opt << "--status-fd=1"
        << "--command-fd=0";
    QStringList interactions;
    interactions << "trust"
                 << "m"
                 << "save";
    Action actionSign("--edit-key", QStringList(m_pub->getKeyId()), opt, interactions);
    m_gpg = new GPGManager(((GpgTreeWidget*) treeWidget())->getProfile());
    m_gpg->setAction(actionSign);
    connect(m_gpg, &GPGManager::finished, this, &PrimaPubKeyItem::setPossibleTrustValue);
    m_gpg->execute();
}
