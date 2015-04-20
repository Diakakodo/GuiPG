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
    setText(COL_ID, gpgObject->getFpr());

}

GpgItem::GpgItem(GpgObject* gpgObject) : QTreeWidgetItem (),
                                        m_gpgObject(gpgObject)
{
    setText(COL_CREATION, gpgObject->getCreationDate().toString("dd/MM/yyyy"));
    setText(COL_ID, gpgObject->getFpr());
}

GpgItem::~GpgItem()
{

}

void GpgItem::changed(int s, QString output) {
    if (s || output == "") {
        // not used.
    }
    Action updateAction("--check-trustdb");
    GPGManager* gpg = new GPGManager(((GpgTreeWidget*) treeWidget())->getProfile());
    gpg->setAction(updateAction);
    connect(gpg, &GPGManager::finished, this, &GpgItem::onGpgUpdate);
    gpg->execute();
}


void GpgItem::onGpgUpdate(int s, QString output) {
    ((GpgTreeWidget*) treeWidget())->getKeyManager()->load();
}
