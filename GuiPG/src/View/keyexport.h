#ifndef KEYEXPORT_H
#define KEYEXPORT_H

#include <QDialog>

namespace Ui {
class KeyExport;
}

class KeyExport : public QDialog
{
    Q_OBJECT

public:
    explicit KeyExport(QWidget *parent = 0);
    ~KeyExport();

private slots:
    void on_cancelButton_clicked();

    void on_browseButton_clicked();

    void on_exportButton_clicked();

    void on_keyServerList_activated(const QString &arg1);

    void on_pathEdit_textChanged(const QString &arg1);

private:
    Ui::KeyExport *ui;
};

#endif // KEYEXPORT_H
