#include "gpgmanager.h"
#include <QDebug>
#include "../Launcher/launcher.h"
#include <QDialog>
#include <QLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>


GPGManager::GPGManager(Profile *p, MainWindow* window) : m_profile(p) {
    connect(&m_gpg, (void (QProcess::*)(int, QProcess::ExitStatus)) &QProcess::finished,
            this, &GPGManager::terminate);
    connect(&m_gpg, (void (QProcess::*)(QProcess::ProcessError)) &QProcess::error, this, &GPGManager::errorGPG);
    connect(&m_gpg, &QProcess::stateChanged, this, &GPGManager::stateChanged);

    QHash<Profile*, MainWindow*> hash = Launcher::m_profileMainWindowHash;
    if (hash.contains((Profile* const)p)) {
        MainWindow* window = hash.value((Profile* const) p);
        m_window = window;
        connect(this, &GPGManager::isWatchingYou, window, &MainWindow::updateBigBrother);
    } else if (window) {
        m_window = window;
        connect(this, &GPGManager::isWatchingYou, window, &MainWindow::updateBigBrother);
    }

    //m_gpg.setProcessChannelMode(QProcess::MergedChannels);
    m_gpg.setReadChannel(QProcess::StandardOutput);
}

bool GPGManager::askHiddenInteraction() {
    QStringList l = m_output.split('\n', QString::SkipEmptyParts);
    if (!l.isEmpty()) {
        QString last = l.last();
        if (last.contains("[GNUPG:] GET_HIDDEN")) {
            return true;
        }
    }
    return false;
}

bool GPGManager::askInteraction() {
    QStringList l = m_output.split('\n', QString::SkipEmptyParts);
    if (!l.isEmpty()) {
        QString last = l.last();
        if (last.contains("[GNUPG:] GET_")) {
            return true;
        }
    }
    return false;
}

GPGManager::~GPGManager() {
    if (m_gpg.state() != QProcess::NotRunning) {
        m_gpg.waitForFinished();
        if (m_gpg.state() != QProcess::NotRunning) {
            m_gpg.kill();
        }
    }
}

void GPGManager::sendInteraction() {
    if (m_gpg.state() != QProcess::Running
            || !askInteraction()) {
        throw GPGException("m_gpg.state() != QProcess::Running "
                           "|| !askInteraction(m_output)");
    }
    if (!m_action.hasInteraction()) {
        m_gpg.kill();
        throw NotEnoughInteraction("Pas assez d'interactions.");
    } else {
        QByteArray data(m_action.nextInteraction().toLatin1());
        m_output += data;
        m_gpg.write(data);
    }
}

void GPGManager::sendHiddenInteraction() {
    QDialog dialog;
    QLayout* HLayout = new QHBoxLayout(&dialog);
    QLayout* VLayout1 = new QVBoxLayout();
    QLayout* VLayout2 = new QVBoxLayout();
    HLayout->addItem(VLayout1);
    HLayout->addItem(VLayout2);
    VLayout1->addWidget(new QLabel("Passphrase :", &dialog));
    passphraseEdit = new QLineEdit(&dialog);
    passphraseEdit->setEchoMode(QLineEdit::Password);
    VLayout2->addWidget(passphraseEdit);
    VLayout1->addWidget(new QLabel("", &dialog));
    QPushButton* validButton = new QPushButton("valider", &dialog);
    VLayout2->addWidget(validButton);
    connect(validButton, &QPushButton::clicked, this, &GPGManager::onSendHiddenInteraction);
    connect(validButton, &QPushButton::clicked, &dialog, &QDialog::accept);
    connect(&dialog, &QDialog::rejected, this, &GPGManager::onSendHiddenInteractionAborted);
    dialog.setModal(true);
    dialog.exec();
}

void GPGManager::onSendHiddenInteraction() {
    QString pwd = passphraseEdit->text();
    m_gpg.write(pwd.toLatin1() + "\n");
}

void GPGManager::onSendHiddenInteractionAborted() {
    m_gpg.kill();
}

bool GPGManager::isRunning() {
    return m_gpg.state() == QProcess::Running;
}

void GPGManager::stateChanged(QProcess::ProcessState newState) {
    if (newState == QProcess::Running
            && m_action.hasInteraction()
            && askInteraction()) {
        sendInteraction();
    }
}

Profile *GPGManager::getProfile() {
    return m_profile;
}

void GPGManager::errorGPG(QProcess::ProcessError error) {
    if (error) {
        // slot not used.
    }
}

const QString &GPGManager::getCmd() const {
    return m_cmd;
}

int GPGManager::getId() {
    return m_id;
}

void GPGManager::execute() {
    m_output = "";
    QStringList args;
    if (m_profile->getConfigurationPath() != "") {
        args.append("--homedir");
        args.append(m_profile->getConfigurationPath());
    }
    for (QString option : m_action.getOptions()) {
        args.append(option);
    }
    args.append(m_action.getCmd());
    for (QString argument : m_action.getArgs()) {
        args.append(argument);
    }
    QStringList cmd(m_profile->getGPGExecutable());
    cmd.append(args);
    m_cmd = cmd.join(" ");
    //qDebug() << cmd;
    m_startTime = QTime::currentTime();
    if (m_action.getOptions().contains("--batch")) {
        m_gpg.start(QCoreApplication::applicationDirPath() + "/getPrettyGoodPty", QStringList("sh") << "-c" << QString(m_cmd + "\n"));
        m_gpg.waitForStarted();
        while (m_action.hasInteraction()) {
            QString data = m_action.nextInteraction();
            m_gpg.write(data.toLatin1());
            QString dataAvailable;
            if (data.startsWith("Passphrase:")) {
                dataAvailable = "Passphrase: *****\n";
            } else {
                dataAvailable = data;
            }
            m_output += dataAvailable;
            emit newData(dataAvailable);
        }
        m_gpg.write("%commit\n");
        m_output += "%commit\n";
        emit newData("%commit\n");
        m_gpg.write("%echo done\n");
        m_output += "%echo done\n";
        emit newData("%echo done\n");

        connect(&m_gpg, &QProcess::readyReadStandardOutput, this, &GPGManager::readOutput);
        m_gpg.closeWriteChannel();
    } else {
        m_gpg.start(QCoreApplication::applicationDirPath() + "/getPrettyGoodPty", QStringList("sh") << "-c" << QString(m_cmd + "\n"));
        m_gpg.waitForStarted();
        connect(&m_gpg, &QProcess::readyReadStandardOutput, this, &GPGManager::readOutput);
    }
    m_id = 0;
    if (m_window) {
        m_id = m_window->getNbCmd();
        m_window->setNbCmd(m_id + 1);
    }
    emit isWatchingYou(this, true, m_id);
}
void GPGManager::readOutput() {
    QString data = m_gpg.readAllStandardOutput();
    //qDebug() << data;
    m_output += data;
    if (m_action.getOptions().contains("--batch") && m_output.endsWith(": done\n")) {
        m_gpg.kill();
    }
    emit newData(data);
    if (m_gpg.state() == QProcess::Running
            && askHiddenInteraction()) {
        sendHiddenInteraction();
    } else {
        if (m_gpg.state() == QProcess::Running
                && askInteraction()) {
            sendInteraction();
        }
    }
}

const QString& GPGManager::getOutput() const {
    return m_output;
}

void GPGManager::terminate(int s, QProcess::ExitStatus status) {
    if (status) {
        // variable not used.
    }
    m_endTime = QTime::currentTime();
    disconnect(&m_gpg, &QProcess::readyReadStandardOutput, this, &GPGManager::readOutput);
    emit isWatchingYou(this, false, m_id);
    emit finished(s, m_output);
}

void GPGManager::setAction(const Action &a) {
    m_action = a;
}

void GPGManager::cancelProcess() {
    m_gpg.kill();
}


const QTime& GPGManager::getStartTime() const {
    return m_startTime;
}

const QTime& GPGManager::getEndTime() const {
    return m_endTime;
}
