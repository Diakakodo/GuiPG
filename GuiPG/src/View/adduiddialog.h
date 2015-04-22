#ifndef ADDUIDDIALOG_H
#define ADDUIDDIALOG_H

#include <QDialog>

namespace Ui {
class AddUidDialog;
}

class AddUidDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddUidDialog(QWidget *parent = 0);
    ~AddUidDialog();

private:
    Ui::AddUidDialog *ui;
};

#endif // ADDUIDDIALOG_H
