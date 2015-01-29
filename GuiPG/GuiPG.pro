QT += core widgets xml
QMAKE_CXXFLAGS += -std=c++11 -pedantic -Wall

HEADERS += \
    src/Configuration/configuration.h \
    src/Profile/profile.h \
    src/Tests/testmanager.h \
    src/action.h \
    src/View/mainwindow.h \
    src/Profile/profilemanager.h

SOURCES += \
    src/Configuration/configuration.cpp \
    src/Profile/profile.cpp \
    src/Tests/testmanager.cpp \
    src/main.cpp \
    src/action.cpp \
    src/View/mainwindow.cpp \
    src/Profile/profilemanager.cpp

FORMS += \
    src/View/mainwindow.ui
