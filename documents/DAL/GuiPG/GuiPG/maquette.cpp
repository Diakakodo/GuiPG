#include "maquette.h"
#include "ui_maquette.h"
#include <QLineEdit>

Maquette::Maquette(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Maquette)
{
    ui->setupUi(this);
    QLineEdit* q = new QLineEdit();
    q->setText("Rechercher");
    ui->toolBar->addWidget(q);
}

Maquette::~Maquette()
{
    delete ui;
}
