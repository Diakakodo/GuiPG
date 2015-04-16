#include "signatureitem.h"

#include <QMenu>

SignatureItem::SignatureItem(Signature* sig) : GpgItem(sig)
{
    m_sig = sig;
    m_uidName = sig->getUidName();
    m_uidMail = sig->getUidMail();

    setText(COL_NAME, m_uidName);
    setText(COL_MAIL, m_uidMail);
    setText(COL_ALGO, GpgObject::algoToStr(sig->getAlgo()));
}

SignatureItem::~SignatureItem()
{

}


void SignatureItem::showMenu(const QPoint &pos) {
    QMenu* menu = new QMenu(treeWidget());
    menu->addAction("Test Signature");
    menu->popup(treeWidget()->viewport()->mapToGlobal(pos));
}

