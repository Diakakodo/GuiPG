#include "primapubkeyitem.h"
#include "uiditem.h"
#include "subpubkeyitem.h"
#include "../gpgtreewidget.h"
#include "../keyexport.h"
#include "../../Keys/keydeletion.h"
#include "../subkeycreation.h"
#include <QMenu>
#include <QAction>
#include <QSignalMapper>
#include "../../GPG/action.h"
#include <QMessageBox>

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
    for (int col = 0; col < NB_COLUMNS; ++col) {
        QFont f = font(col);
        if (pub->hasPrimaSecKey()) {
            f.setBold(true);
        }
        if (pub->getValidity() == VALIDITY_EXPIRED) {
            f.setStrikeOut(true);
        }
        setFont(col, f);
    }

    if (pub->hasPrimaSecKey()) {
        setIcon(COL_NAME, QIcon(":/icones/res/" ICON_DOUBLE_KEY_PATH));
    } else {
        setIcon(COL_NAME, QIcon(":/icones/res/" ICON_SINGLE_KEY_PATH));
    }
}

PrimaPubKeyItem::~PrimaPubKeyItem()
{
    //delete this->m_secretKeyWidget;
}

void PrimaPubKeyItem::showMenu(const QPoint &pos) {
    m_pos = pos;
    m_menu = new QMenu(treeWidget());
    if (m_pub->hasPrimaSecKey()) {
        m_menu->addAction("Ajouter un identifiant utilisateur", this, SLOT(addUid()));
        m_menu->addAction("Supprimer/Révoquer un identifiant utilisateur", this, SLOT(delOrRevUid()));
    }
    m_menu->addAction("Exporter la clé publique", this, SLOT(exportPublicKey()));
    if (m_pub->hasPrimaSecKey()) {
        m_menu->addAction("Exporter la clé secrète", this, SLOT(exportSecretKey()));
        m_menu->addAction("Ajouter une sous-clé", this, SLOT(addSubKey()));
        m_menu->addAction("Supprimer/Révoquer une sous-clé", this, SLOT(delOrRevSubKey()));
    }
    //m_menu->addAction("Signer", this, SLOT(sign()));
    m_menu->addAction("Signer", this, SLOT(selectSecretKey()));
    m_menu->addAction("Supprimer", this, SLOT(deleteKey()));
    getPossibleTrustValue();
}


void PrimaPubKeyItem::addSubKey() {
    GpgTreeWidget* tree = (GpgTreeWidget*) treeWidget();
    m_createSubPubKeyView = new SubKeyCreation(tree->getProfile(), m_pub, tree);
    connect(m_createSubPubKeyView, &QDialog::finished, this, &PrimaPubKeyItem::onAddSubKeyFinished);
    m_createSubPubKeyView->show();

}

void PrimaPubKeyItem::onAddSubKeyFinished(int result) {
    if (result) {
        ((GpgTreeWidget*) treeWidget())->getKeyManager()->load();
        delete m_createSubPubKeyView;
    }
}

void PrimaPubKeyItem::onAddUidFinished() {
    ((GpgTreeWidget*) treeWidget())->getKeyManager()->load();
    delete m_addUidView;
}

void PrimaPubKeyItem::selectSecretKey() {
    GpgTreeWidget* tree = (GpgTreeWidget*) treeWidget();
    this->m_secretKeyWidget = new SecretKeyWidget(tree->getKeyManager()->getSecKeys());
    connect(this->m_secretKeyWidget, &SecretKeyWidget::selectedSecretKey, this, &PrimaPubKeyItem::sign);
    this->m_secretKeyWidget->show();
}

void PrimaPubKeyItem::sign(QString fpr) {
    QString infos = "Voulez vous vraiment signer cette clef ?\n\n";
    infos += "Empreinte : " + m_pub->getFpr() + "\n";
    infos += "Date de création : " + m_pub->getCreationDate().toString() + "\n";
    infos += "Date d'expiration : " + m_pub->getExpirationDate().toString() + "\n";
    infos += "Capacité : " + m_pub->getCapabilities() + "\n";
    infos += "Validité : " + GpgObject::validityToStr(m_pub->getValidity()) + "\n";
    infos += "Confiance : " + PrimaPubKey::trustToStr(m_pub->getTrust()) + "\n\n";
    infos += "Identifiants utilisateurs qui seront signés :\n";
    for (Uid* u : m_pub->getUidList()) {
        infos += "    " + u->getName() + " " + u->getMail() + "\n";
    }
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(0, "Confirmation de signature", infos, QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        //KeyManager* keyManager = ((GpgTreeWidget*) treeWidget())->getKeyManager();

        QStringList opt;
        opt << "--status-fd=1"
            << "--command-fd=0"
            << "--default-key"
            << fpr;
        QStringList interactions;
        interactions << "y";
        interactions << "y";
        Action actionSign("--sign-key", QStringList(m_pub->getKeyId()), opt, interactions);
        m_gpg = new GPGManager(((GpgTreeWidget*) treeWidget())->getProfile());
        connect(m_gpg, &GPGManager::finished, this, &GpgItem::changed);
        m_gpg->setAction(actionSign);
        m_gpg->execute();
    }
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

void PrimaPubKeyItem::addUid() {
    GpgTreeWidget* tree = (GpgTreeWidget*) treeWidget();
    m_addUidView = new AddUidDialog(tree->getProfile(), m_pub, tree);
    connect(m_addUidView, &AddUidDialog::finished, this, &PrimaPubKeyItem::onAddUidFinished);
    m_addUidView->exec();
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

void PrimaPubKeyItem::deleteKey() {
    QString infos = "Voulez vous vraiment supprimer cette clef ?\n\n";
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(0, "Confirmation de suppression", infos, QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        KeyManager* keyManager = ((GpgTreeWidget*) treeWidget())->getKeyManager();
        KeyDeletion* deleteManager = new KeyDeletion(keyManager, ((GpgTreeWidget*) treeWidget())->getProfile(), m_pub->getKeyId());
        if (m_pub->hasPrimaSecKey()) {
            deleteManager->deleteKeys(); // On supprime les deux clés (privé/secrete).
        } else {
            deleteManager->deletePublicKey(); // On ne supprime que la clé publique.
        }
     }
}

void PrimaPubKeyItem::setPossibleTrustValue(int s, QString output) {
    m_possibleTrustValue.clear();
    disconnect(m_gpg, &GPGManager::finished, this, &PrimaPubKeyItem::getPossibleTrustValue);
    delete m_gpg;
    if (s == EXIT_SUCCESS) {
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

PrimaPubKey* PrimaPubKeyItem::getPrimaPubKey() const {
    return m_pub;
}

void PrimaPubKeyItem::delOrRevUid() {
    GpgTreeWidget* tree = (GpgTreeWidget*) treeWidget();
    m_delUidView = new DeleteUidDialog(tree->getProfile(), m_pub, tree);
    connect(m_delUidView, &DeleteUidDialog::finished, this, &PrimaPubKeyItem::onDeleteUidFinished);
    m_delUidView->exec();

}

void PrimaPubKeyItem::onDeleteUidFinished() {
    ((GpgTreeWidget*) treeWidget())->getKeyManager()->load();
    delete m_delUidView;
}

void PrimaPubKeyItem::delOrRevSubKey() {
    GpgTreeWidget* tree = (GpgTreeWidget*) treeWidget();
    m_delSubKeyView = new DeleteSubKeyDialog(tree->getProfile(), m_pub, tree);
    connect(m_delSubKeyView, &DeleteSubKeyDialog::finished, this, &PrimaPubKeyItem::onDeleteSubKeyFinished);
    m_delSubKeyView->exec();

}

void PrimaPubKeyItem::onDeleteSubKeyFinished() {
    ((GpgTreeWidget*) treeWidget())->getKeyManager()->load();
    delete m_delSubKeyView;
}

