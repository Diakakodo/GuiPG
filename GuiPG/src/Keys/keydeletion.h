#ifndef KEYDELETION_H
#define KEYDELETION_H

#include <QDialog>
#include "../Profile/profile.h"
#include "../View/mainwindow.h"

class KeyDeletion : public QDialog
{
    Q_OBJECT

public:

    explicit KeyDeletion(MainWindow* parent = 0);
    ~KeyDeletion();
    void deletePublicKey(QString keyId);
    void deleteSecretKey(QString keyId);


private:
    void onDeletionCompleted();
    GPGManager* m_manager;
    MainWindow* m_window;
    Profile* m_profile;
};


#endif // KEYDELETION_H
