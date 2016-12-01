#include "mythread.h"
#include "GpgItems/primapubkeyitem.h"
#include <QDebug>
MyThread::MyThread(QObject *parent, GpgTreeWidget *tree, MainWindowModel* model) : QThread(parent)
{
    m_tree = tree;
    m_model= model;
}

void MyThread::run() {
    const QList<PrimaPubKey*> pubKeys = m_model->getKeyManager()->getPubKeys();
    QList<QString> hash;
    for (PrimaPubKey* pub : pubKeys) {
        hash.append(pub->getFpr());
    }
    QHash<QString, QTreeWidgetItem*> hashItem;
    QTreeWidget tmpTree;
    int count = m_tree->topLevelItemCount();
    for (int i = 0; i < count; i++) {
        if (hash.contains(((PrimaPubKeyItem*) m_tree->topLevelItem(i))->getFpr())) {
            QTreeWidgetItem* item = new QTreeWidgetItem(&tmpTree);
            for (int j = 0; j < m_tree->topLevelItem(i)->childCount(); ++j) {
                QTreeWidgetItem* child = m_tree->topLevelItem(i)->child(j)->clone();
                item->addChild(child);
                child->setExpanded(m_tree->topLevelItem(i)->child(j)->isExpanded());
                child->setSelected(m_tree->topLevelItem(i)->child(j)->isSelected());
                for (int k = 0; k < m_tree->topLevelItem(i)->child(j)->childCount(); ++k) {
                    QTreeWidgetItem* subChild = m_tree->topLevelItem(i)->child(j)->child(k)->clone();
                    child->addChild(subChild);
                    item->child(j)->child(k)->setSelected(m_tree->topLevelItem(i)->child(j)->child(k)->isSelected());
                }
            }
            tmpTree.addTopLevelItem(item);
            if (m_tree->topLevelItem(i)->isSelected() && tmpTree.selectedItems().count() < 1) {
                item->setSelected(true);
            }
            item->setExpanded(m_tree->topLevelItem(i)->isExpanded());
            item->setHidden(m_tree->topLevelItem(i)->isHidden());
            hashItem.insert(((PrimaPubKeyItem*) m_tree->topLevelItem(i))->getFpr(), item);
        }
    }
    for (int i = 0; i < count; ++i) emit deleteTopItem(0);
    for (PrimaPubKey* pub : pubKeys) {
        QTreeWidget* tmp = new QTreeWidget();
        PrimaPubKeyItem* newItem = new PrimaPubKeyItem(pub);
        tmp->addTopLevelItem(newItem);
        if (hashItem.contains(pub->getFpr())) {
            QTreeWidgetItem* item = hashItem.value(pub->getFpr());
            newItem->setHidden(item->isHidden());
            newItem->setExpanded(item->isExpanded());
            newItem->setSelected(item->isSelected());
            for (int i = 0; i < item->childCount() && i < newItem->childCount(); ++i) {
                newItem->child(i)->setExpanded(item->child(i)->isExpanded());
                newItem->child(i)->setSelected(item->child(i)->isSelected());
                for (int j = 0; j < newItem->child(i)->childCount() && j < item->child(i)->childCount(); ++j) {
                    newItem->child(i)->child(j)->setSelected(item->child(i)->child(j)->isSelected());
                }
            }
        }
        emit addTopItem(tmp, newItem);
    }
    tmpTree.clear();
}
