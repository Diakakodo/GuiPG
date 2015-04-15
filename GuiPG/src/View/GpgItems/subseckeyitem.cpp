#include "subseckeyitem.h"
#include <QMenu>

SubSecKeyItem::SubSecKeyItem(SubSecKey* subSecKey) : GpgItem (subSecKey)
{
    setText(4, subSecKey->getCreationDate().toString("dd/MM/yyyy"));
    setText(6, QString::number(subSecKey->getLength()));
    setText(7, GpgObject::algoToStr(subSecKey->getAlgo()));
    setText(9, subSecKey->getKeyId());
}

SubSecKeyItem::~SubSecKeyItem()
{

}

void SubSecKeyItem::showMenu(const QPoint &pos) {
    QMenu* menu = new QMenu(treeWidget());
    menu->addAction("Test");
    menu->popup(treeWidget()->viewport()->mapToGlobal(pos));
}


