#include "gpgtreewidget.h"
#include "GpgItems/gpgitem.h"
#include <QItemDelegate>

class myItemDelegate : public QItemDelegate
{
public:
        myItemDelegate ()
        {
        }

        QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const
        {
               return QSize(100,24);
        }
};

GpgTreeWidget::GpgTreeWidget(QWidget * parent) : QTreeWidget(parent)
{
    setItemDelegate(new myItemDelegate());
    setIconSize(QSize(24,24));
    setAlternatingRowColors(true);
}

GpgTreeWidget::~GpgTreeWidget()
{

}

void GpgTreeWidget::setProfile(Profile* profile) {
    m_profile = profile;
}

Profile* GpgTreeWidget::getProfile() {
    return m_profile;
}
