#ifndef GPGTREEWIDGET_H
#define GPGTREEWIDGET_H

#include <QTreeWidget>
#include "../Keys/keymanager.h"
#include "../Profile/profile.h"

class myItemDelegate;

class GpgTreeWidget : public QTreeWidget {
        Q_OBJECT
    public:
        GpgTreeWidget(QWidget * parent = 0, KeyManager* keyManager = 0);
        ~GpgTreeWidget();
        void setProfile(Profile* profile);
        Profile* getProfile();
        KeyManager* getKeyManager() const;
        void setKeyManager(KeyManager* keyManager);

    private:
        Profile* m_profile = nullptr;
        KeyManager* m_keyManager;
        myItemDelegate* m_itemdelegate;
};

#endif // GPGTREEWIDGET_H
