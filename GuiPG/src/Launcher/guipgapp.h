#ifndef GUIPGAPP_H
#define GUIPGAPP_H

#include <QObject>
#include <QApplication>
#include "../Profile/profile.h"

class GuiPGApp : public QApplication
{
        Q_OBJECT
    public:
        explicit GuiPGApp(int& argc, char** argv);

        ~GuiPGApp();

    public slots:
        void launchApp(Profile* p);
};

#endif // GUIPGAPP_H
