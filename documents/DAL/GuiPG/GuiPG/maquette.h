#ifndef MAQUETTE_H
#define MAQUETTE_H

#include <QMainWindow>

namespace Ui {
class Maquette;
}

class Maquette : public QMainWindow
{
        Q_OBJECT

    public:
        explicit Maquette(QWidget *parent = 0);
        ~Maquette();

    private:
        Ui::Maquette *ui;
};

#endif // MAQUETTE_H
