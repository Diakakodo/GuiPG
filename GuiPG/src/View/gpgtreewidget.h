#ifndef GPGTREEWIDGET_H
#define GPGTREEWIDGET_H

#include <QTreeWidget>

#include "../Profile/profile.h"

class GpgTreeWidget : public QTreeWidget
{
    public:
        GpgTreeWidget(QWidget * parent = 0);
        ~GpgTreeWidget();
        void setProfile(Profile* profile);
        Profile* getProfile();

    private:
        Profile* m_profile = nullptr;
};

#endif // GPGTREEWIDGET_H
