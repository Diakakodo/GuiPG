#ifndef GUIPGAPP_H
#define GUIPGAPP_H

#include <QApplication>
#include "../Profile/profile.h"

class GuiPGApp : public QApplication
{
    public:
        explicit GuiPGApp(int& argc, char** argv);

        ~GuiPGApp();

        void launchApp(Profile* p);
};

#endif // GUIPGAPP_H
