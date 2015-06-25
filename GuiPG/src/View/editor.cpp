#include "editor.h"
#include "ui_editor.h"
#include "mainwindow.h"
#include <QFileDialog>
#include "../Keys/uid.h"
#include "../Keys/primapubkey.h"
#include "filesigneditor.h"
#include "fileencryptioneditor.h"
#include "filedecryptionandverifyeditor.h"
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

void Editor::on_exitButton_clicked()
{
    remove("/tmp/tmpFile");
    close();
}

void Editor::on_encryptButton_clicked()
{


    ofstream fichier("/tmp/tmpFile", ios::out | ios::trunc);

    if (fichier) {
        fichier << ui->textEdit->toPlainText().toStdString();
        fichier.close();
    }

    FileEncryptionEditor fileencryptioneditor(m_parent, m_keyManager);
    fileencryptioneditor.exec();

}

void Editor::onEncryptionCompleted()
{
    remove("/tmp/tmpFile");
}


void Editor::on_signButton_clicked()
{
    ofstream fichier("/tmp/tmpFile", ios::out | ios::trunc);

    if (fichier) {
        fichier << ui->textEdit->toPlainText().toStdString();
        fichier.close();
    }

    FileSignEditor filesigneditor(m_parent, m_keyManager);
    filesigneditor.exec();
}

void Editor::on_decryptButton_clicked() {
    ofstream fichier("/tmp/tmpFile", ios::out | ios::trunc);

    if (fichier) {
        fichier << ui->textEdit->toPlainText().toStdString();
        fichier.close();
    }

    FileDecryptionAndVerifyEditor filedecryptionandverifyeditor(m_profile, m_parent);
    filedecryptionandverifyeditor.exec();
}
