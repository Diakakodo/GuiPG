#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>

#include "mainwindow.h"
#include "gpgtreewidget.h"
#include "GpgItems/primapubkeyitem.h"

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject* parent, GpgTreeWidget *tree, MainWindowModel* model);

private:
    void run();
    GpgTreeWidget* m_tree;
    MainWindowModel* m_model;

signals:
    void deleteTopItem(int i);
    void addTopItem(PrimaPubKeyItem* newItem);

public slots:
};

#endif // MYTHREAD_H
