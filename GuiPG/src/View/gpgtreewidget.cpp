#include "gpgtreewidget.h"

GpgTreeWidget::GpgTreeWidget(QWidget * parent) : QTreeWidget(parent)
{

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
