#ifndef FileDecryptionAndVerifyEditor_H
#define FileDecryptionAndVerifyEditor_H

#include <QDialog>
#include "../Profile/profile.h"
#include "../GPG/gpgmanager.h"

namespace Ui {
class FileDecryptionAndVerifyEditor;
}

class FileDecryptionAndVerifyEditor : public QDialog
{
    Q_OBJECT

public:
    explicit FileDecryptionAndVerifyEditor(Profile* profile, QWidget *parent = 0);
    ~FileDecryptionAndVerifyEditor();

private slots:
    void on_browseDestinationFileButton2_clicked();

    void onGpgFinished(int s, QString output);

    void on_acceptButton2_clicked();

    void on_cancelButton2_clicked();

private:
    Ui::FileDecryptionAndVerifyEditor *ui;
    Profile* m_profile = nullptr;
    GPGManager* m_gpg = nullptr;
};

#endif // FileDecryptionAndVerifyEditorEDITOR_H
