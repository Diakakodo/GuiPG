#ifndef KEYEXPORT_H
#define KEYEXPORT_H

#include <QDialog>
#include "../Profile/profile.h"
#include "mainwindow.h"

namespace Ui {
class KeyExport;
}

class KeyExport : public QDialog
{
    Q_OBJECT

public:
    enum Type {
        SECRET_KEYS,
        PUBLIC_KEYS
    };

    enum ExportMode {
        EXPORT_KEYSERVER,
        EXPORT_FILE
    };

    explicit KeyExport(MainWindow* parent = 0, Type mode = PUBLIC_KEYS, QStringList keys = QStringList());
    ~KeyExport();
    int exportFunction(ExportMode mode, QString keyserver, QString path);

private slots:
    void on_cancelButton_clicked();

    void on_browseButton_clicked();

    void on_exportButton_clicked();

    void on_keyServerList_activated(const QString &arg1);

    void on_pathEdit_textChanged(const QString &arg1);


private:
    Ui::KeyExport *ui;
    Type m_mode;
    QStringList m_keys;
    Profile* m_profile;
};

#endif // KEYEXPORT_H
