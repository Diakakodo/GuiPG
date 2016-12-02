#ifndef SECRETKEYWIDGET_H
#define SECRETKEYWIDGET_H

#include <QWidget>
#include "../Keys/primaseckey.h"

namespace Ui {
class SecretKeyWidget;
}

class SecretKeyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SecretKeyWidget(QList<PrimaSecKey *> keys,QWidget *parent = 0);
    ~SecretKeyWidget();

signals:
    void selectedSecretKey(QString SecretKeyFpr);

private slots:
    void on_selectButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::SecretKeyWidget *ui;
};

#endif // SECRETKEYWIDGET_H
