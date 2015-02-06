QT += core widgets xml
QMAKE_CXXFLAGS += -std=c++11 -pedantic -Wall

HEADERS += \
    src/Configuration/configuration.h \
    src/Profile/profile.h \
    src/action.h \
    src/View/mainwindow.h \
    src/View/Profil/dialogprofil.h \
    src/Profile/profilemanager.h \
    src/Launcher/guipgapp.h \
    src/Launcher/launcher.h \
    src/GPG/gpgmanager.h \
    src/GPG/action.h \
    src/Keys/key.h \
    src/Keys/keymanager.h \
    src/View/keycreation.h \
    src/View/keycreation.h \
    src/View/keysuppression.h

SOURCES += \
    src/Configuration/configuration.cpp \
    src/Profile/profile.cpp \
    src/main.cpp \
    src/View/mainwindow.cpp \
    src/View/Profil/dialogprofil.cpp \
    src/Profile/profilemanager.cpp \
    src/Launcher/guipgapp.cpp \
    src/Launcher/launcher.cpp \
    src/GPG/gpgmanager.cpp \
    src/GPG/action.cpp \
    src/Keys/key.cpp \
    src/Keys/keymanager.cpp \
    src/View/keycreation.cpp \
    src/View/keysuppression.cpp

FORMS += \
    src/View/mainwindow.ui \
    src/View/Profil/dialogprofil.ui \
    src/View/keycreation.ui \
    src/View/keysuppression.ui

test {

    QT += testlib
    TARGET = Guipg-test
    SOURCES -= src/main.cpp

    SOURCES += src/Tests/tst_maintest.cpp\
}
