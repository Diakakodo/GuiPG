#include "gpgitem.h"
#include "../gpgtreewidget.h"


// Initialisation de la hash map (nomde la colone -> numéro de la colone)
// Les noms sont défini dans la X_Maccro X_COLUMNS et le numéro est donné par
// l'ordre de définition des collones dans la X_MACRO.
QHash<int, QString> GpgItem::columns = []() -> QHash<int, QString> {
    // Ce tableau permet de récupérer le nom de la colone a partir de son numéro d'enum.
    #define X(id, str) str,
    QString columnsName[NB_COLUMNS + 1] = {
        X_COLUMNS
        NULL
    };
    #undef X
    QHash<int, QString> hash;
    for (int i = 0; i < GpgItem::NB_COLUMNS; ++i) {
        hash.insert(i, columnsName[i]);
    }
    return hash;
}();

GpgItem::GpgItem(QTreeWidget * parent,
                 GpgObject* gpgObject) : QTreeWidgetItem (parent),
                                        m_gpgObject(gpgObject)
{
    setText(COL_CREATION, gpgObject->getCreationDate().toString("dd/MM/yyyy"));
    setText(COL_ID, gpgObject->getFpr().right(16));
    m_fpr = gpgObject->getFpr();
}

GpgItem::GpgItem(GpgObject* gpgObject) : QTreeWidgetItem (),
                                        m_gpgObject(gpgObject)
{
    setText(COL_CREATION, gpgObject->getCreationDate().toString("dd/MM/yyyy"));
    setText(COL_ID, gpgObject->getFpr().right(16));
    m_fpr = gpgObject->getFpr();
}

QString GpgItem::getFpr() {
    return m_fpr;
}

GpgItem::~GpgItem()
{

}

void GpgItem::changed(int s, QString output) {
    if (s || output == "") {
        // not used.
    }
    disconnect(m_gpg, &GPGManager::finished, this, &GpgItem::changed);
    delete m_gpg;
    Action updateAction("--check-trustdb");
    m_gpg = new GPGManager(((GpgTreeWidget*) treeWidget())->getProfile());
    m_gpg->setAction(updateAction);
    connect(m_gpg, &GPGManager::finished, this, &GpgItem::onGpgUpdate);
    m_gpg->execute();
}


void GpgItem::onGpgUpdate(int s, QString output) {
    if (s || output == "") {
        // not used
    }
    disconnect(m_gpg, &GPGManager::finished, this, &GpgItem::onGpgUpdate);
    delete m_gpg;
    ((GpgTreeWidget*) treeWidget())->getKeyManager()->load();
}
