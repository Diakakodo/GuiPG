#include "signatureitem.h"

#include <QMenu>
#include <QCoreApplication>

SignatureItem::SignatureItem(Signature* sig) : GpgItem(sig)
{
    m_sig = sig;
    m_uidName = sig->getUidName();
    m_uidMail = sig->getUidMail();

    setText(COL_NAME, m_uidName);
    setText(COL_MAIL, m_uidMail);
    setText(COL_ALGO, GpgObject::algoToStr(sig->getAlgo()));
    setIcon(COL_NAME, QIcon(":/icones/res/" ICON_SIGNATURE_PATH));

    setTextAlignment(COL_NAME, Qt::AlignVCenter | Qt::AlignLeft);
}

SignatureItem::~SignatureItem()
{

}


void SignatureItem::showMenu(const QPoint &pos) {
    QMenu* menu = new QMenu(treeWidget());
    menu->addAction("Test Signature");
    menu->popup(treeWidget()->viewport()->mapToGlobal(pos));
}

