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
    src/View/keycreation.h

SOURCES += \
    src/Configuration/configuration.cpp \
    src/Profile/profile.cpp \
    src/main.cpp \
    src/action.cpp \
    src/View/mainwindow.cpp \
    src/View/Profil/dialogprofil.cpp \
    src/Profile/profilemanager.cpp \
    src/Launcher/guipgapp.cpp \
    src/Launcher/launcher.cpp \
    src/View/keycreation.cpp \

FORMS += \
    src/View/mainwindow.ui \
    src/View/Profil/dialogprofil.ui \
    src/View/keycreation.ui

test {

    QT += testlib
    TARGET = Guipg-test
    SOURCES -= src/main.cpp

    SOURCES += src/Tests/tst_maintest.cpp\
}
