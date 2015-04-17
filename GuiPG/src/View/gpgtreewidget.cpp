#include "gpgtreewidget.h"
#include "GpgItems/gpgitem.h"

GpgTreeWidget::GpgTreeWidget(QWidget * parent) : QTreeWidget(parent)
{
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
