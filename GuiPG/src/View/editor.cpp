#include "editor.h"
#include "ui_editor.h"
#include "mainwindow.h"
#include <QFileDialog>
#include "../Keys/uid.h"
#include "../Keys/primapubkey.h"
#include <fstream>
#include "sys/types.h"
#include "sys/stat.h"
#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

Editor::Editor(MainWindow *parent, KeyManager* keyManager) :
    QDialog(parent),
    ui(new Ui::Editor)
{
    ui->setupUi(this);
    m_profile = parent->getProfil();
    m_manager = new GPGManager(m_profile);
    m_parent = parent;
    m_keyManager = keyManager;
}

Editor::~Editor()
{
    delete ui;
}

void Editor::on_encryptButton_clicked()
{
    QStringList opt;
    opt << "--command-fd=0"
        << "--status-fd=1"
        << "-a"
        << "-r bobbb"
        << "--output /tmp/outputFile";
    QString cmd = "-e";
    QStringList arg;
    arg << "/tmp/tmpFile";
    QStringList interactions;
    interactions << "toto";

    ofstream fichier("/tmp/tmpFile", ios::out | ios::trunc);

    if (fichier) {
        fichier << ui->textEdit->toPlainText().toStdString();
        fichier.close();
    }

    Action action(cmd, arg, opt, interactions);
    m_manager->setAction(action);
    connect(m_manager, &GPGManager::finished, this, &Editor::onEncryptionCompleted);
    m_manager->execute();
}

void Editor::onEncryptionCompleted()
{
    remove("/tmp/tmpFile");
}

void Editor::on_exitButton_clicked()
{
    close();
}
