#ifndef GPGITEM_H
#define GPGITEM_H

#include <QTreeWidgetItem>
#include "../../Keys/gpgobject.h"
#include <QPoint>

class GpgItem : public QTreeWidgetItem {

    public:

        GpgItem(QTreeWidget * parent, GpgObject* gpgObject);
        GpgItem(GpgObject* gpgObject);
        virtual ~GpgItem() = 0;

        virtual void showMenu(const QPoint &pos) = 0;

    protected:
        GpgObject* m_gpgObject;
};

#endif // GPGITEM_H
