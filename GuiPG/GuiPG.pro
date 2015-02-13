QT += core widgets xml
QMAKE_CXXFLAGS += -std=c++11 -pedantic -Wall

HEADERS += \
    src/Configuration/configuration.h \
    src/Profile/profile.h \
    src/View/mainwindow.h \
    src/Profile/profilemanager.h \
    src/Launcher/guipgapp.h \
    src/Launcher/launcher.h \
    src/GPG/gpgmanager.h \
    src/GPG/action.h \
    src/Keys/key.h \
    src/Keys/keymanager.h \
    src/View/keycreation.h \
    src/Model/mainwindowmodel.h \
    src/View/Profil/profilecreation.h \
    src/View/config.h \
    src/View/Profil/dialogprofile.h

SOURCES += \
    src/Configuration/configuration.cpp \
    src/Profile/profile.cpp \
    src/main.cpp \
    src/View/mainwindow.cpp \
    src/Profile/profilemanager.cpp \
    src/Launcher/guipgapp.cpp \
    src/Launcher/launcher.cpp \
    src/GPG/gpgmanager.cpp \
    src/GPG/action.cpp \
    src/Keys/key.cpp \
    src/Keys/keymanager.cpp \
    src/View/keycreation.cpp \
    src/Model/mainwindowmodel.cpp \
    src/View/Profil/profilecreation.cpp \
    src/View/config.cpp \
    src/View/Profil/dialogprofile.cpp

FORMS += \
    src/View/mainwindow.ui \
    src/View/keycreation.ui \
    src/View/Profil/profilecreation.ui \
    src/View/config.ui \
    src/View/Profil/dialogprofile.ui

test {

    QT += testlib
    TARGET = Guipg-test
    SOURCES -= src/main.cpp

    SOURCES += src/Tests/tst_maintest.cpp
}
