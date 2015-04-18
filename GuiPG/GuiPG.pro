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
    src/Keys/keymanager.h \
    src/View/keycreation.h \
    src/Model/mainwindowmodel.h \
    src/View/Profil/profilecreation.h \
    src/View/config.h \
    src/View/Profil/dialogprofile.h \
    src/Exception/illegalargumentexception.h \
    src/Exception/illegalstateexception.h \
    src/Exception/exceptions.h \
    src/Exception/gpgexception.h \
    src/View/keyexport.h \
    src/View/keyimport.h \
    src/Exception/badinteraction.h \
    src/Exception/notenoughinteraction.h \
    src/View/keyedition.h \
    src/Keys/signature.h \
    src/Keys/gpgobject.h \
    src/Keys/uid.h \
    src/Keys/primapubkey.h \
    src/Keys/pubkey.h \
    src/Keys/subpubkey.h \
    src/Keys/subseckey.h \
    src/Keys/primaseckey.h \
    src/View/GpgItems/gpgitem.h \
    src/View/GpgItems/primapubkeyitem.h \
    src/View/GpgItems/primaseckeyitem.h \
    src/View/GpgItems/pubkeyitem.h \
    src/View/GpgItems/signatureitem.h \
    src/View/GpgItems/subpubkeyitem.h \
    src/View/GpgItems/subseckeyitem.h \
    src/View/GpgItems/uiditem.h \
    src/View/gpgtreewidget.h

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
    src/Keys/keymanager.cpp \
    src/View/keycreation.cpp \
    src/Model/mainwindowmodel.cpp \
    src/View/Profil/profilecreation.cpp \
    src/View/config.cpp \
    src/View/Profil/dialogprofile.cpp \
    src/Exception/illegalargumentexception.cpp \
    src/Exception/illegalstateexception.cpp \
    src/View/keyexport.cpp \
    src/View/keyimport.cpp \
    src/Exception/badinteraction.cpp \
    src/Exception/gpgexception.cpp \
    src/Exception/notenoughinteraction.cpp \
    src/View/keyedition.cpp \
    src/Keys/signature.cpp \
    src/Keys/gpgobject.cpp \
    src/Keys/uid.cpp \
    src/Keys/primapubkey.cpp \
    src/Keys/pubkey.cpp \
    src/Keys/subpubkey.cpp \
    src/Keys/subseckey.cpp \
    src/Keys/primaseckey.cpp \
    src/View/GpgItems/gpgitem.cpp \
    src/View/GpgItems/primapubkeyitem.cpp \
    src/View/GpgItems/primaseckeyitem.cpp \
    src/View/GpgItems/pubkeyitem.cpp \
    src/View/GpgItems/signatureitem.cpp \
    src/View/GpgItems/subpubkeyitem.cpp \
    src/View/GpgItems/subseckeyitem.cpp \
    src/View/GpgItems/uiditem.cpp \
    src/View/gpgtreewidget.cpp

FORMS += \
    src/View/mainwindow.ui \
    src/View/keycreation.ui \
    src/View/Profil/profilecreation.ui \
    src/View/config.ui \
    src/View/Profil/dialogprofile.ui \
    src/View/keyexport.ui \
    src/View/keyimport.ui \
    src/View/keyedition.ui

test {

    QT += testlib
    TARGET = Guipg-test
    SOURCES -= src/main.cpp

    SOURCES += src/Tests/tst_maintest.cpp
}

RESOURCES += \
    icones.qrc
