#include "gpgitem.h"

GpgItem::GpgItem(QTreeWidget * parent,
                 GpgObject* gpgObject) : QTreeWidgetItem (parent),
                                        m_gpgObject(gpgObject)
{

}

GpgItem::GpgItem(GpgObject* gpgObject) : QTreeWidgetItem (),
                                        m_gpgObject(gpgObject)
{

}

GpgItem::~GpgItem()
{

}

