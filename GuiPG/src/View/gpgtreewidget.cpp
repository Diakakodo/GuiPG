#include "gpgtreewidget.h"
#include "GpgItems/gpgitem.h"
#include <QItemDelegate>
#include <QDebug>
class myItemDelegate : public QItemDelegate
{
public:
        myItemDelegate ()
        {
        }

        ~myItemDelegate ()
        {
        }

        QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const
        {
               QItemDelegate::sizeHint(option, index);
               return QSize(100,24);
        }
};

GpgTreeWidget::GpgTreeWidget(QWidget * parent, KeyManager *keyManager) : QTreeWidget(parent)
{
    m_itemdelegate = new myItemDelegate();
    m_keyManager = keyManager;
    setItemDelegate(m_itemdelegate);
    setIconSize(QSize(24,24));
    setAlternatingRowColors(true);
}

GpgTreeWidget::~GpgTreeWidget()
{
    delete m_itemdelegate;
}

void GpgTreeWidget::setKeyManager(KeyManager* keyManager) {
    m_keyManager = keyManager;
}

KeyManager* GpgTreeWidget::getKeyManager() const {
    return m_keyManager;
}

void GpgTreeWidget::setProfile(Profile* profile) {
    m_profile = profile;
}

Profile* GpgTreeWidget::getProfile() {
    return m_profile;
}
