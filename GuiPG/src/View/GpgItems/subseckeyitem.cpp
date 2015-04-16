#include "subseckeyitem.h"
#include <QMenu>

SubSecKeyItem::SubSecKeyItem(SubSecKey* subSecKey) : GpgItem (subSecKey)
{
    m_sec = subSecKey;

    setText(COL_LENGTH, QString::number(subSecKey->getLength()));
    setText(COL_ALGO, GpgObject::algoToStr(subSecKey->getAlgo()));
    setText(COL_ID, subSecKey->getKeyId());
}

SubSecKeyItem::~SubSecKeyItem()
{

}

void SubSecKeyItem::showMenu(const QPoint &pos) {
    QMenu* menu = new QMenu(treeWidget());
    menu->addAction("Test SubSecKey");
    menu->popup(treeWidget()->viewport()->mapToGlobal(pos));
}


