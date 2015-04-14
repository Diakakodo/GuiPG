#include "gpgmanager.h"
#include <QDebug>
#include "../Launcher/launcher.h"

GPGManager::GPGManager(const Profile *p) : m_profile(p) {
    connect(&m_gpg, (void (QProcess::*)(int, QProcess::ExitStatus)) &QProcess::finished,
            this, &GPGManager::terminate);
    connect(&m_gpg, (void (QProcess::*)(QProcess::ProcessError)) &QProcess::error, this, &GPGManager::errorGPG);
    connect(&m_gpg, &QProcess::stateChanged, this, &GPGManager::stateChanged);

    QHash<Profile*, MainWindow*> hash = Launcher::m_profileMainWindowHash;
    if (hash.contains((Profile* const)p)) {
        MainWindow* window = hash.value((Profile* const) p);
        // TODO se connecter au bigbrother !
        connect(this, &GPGManager::isWatchingYou, window, &MainWindow::updateBigBrother);
    }

    //m_gpg.setProcessChannelMode(QProcess::MergedChannels);
    m_gpg.setReadChannel(QProcess::StandardOutput);
}

bool GPGManager::askInteraction() {
    QStringList l = m_output.split('\n', QString::SkipEmptyParts);
    if (!l.isEmpty()) {
        QString last = l.last();
        if (last.contains("[GNUPG:] GET_LINE") || last.contains("[GNUPG:] GET_HIDDEN")) {
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

void GPGManager::stateChanged(QProcess::ProcessState newState) {
    if (newState == QProcess::Running
            && m_action.hasInteraction()
            && askInteraction()) {
        sendInteraction();
    }
}

void GPGManager::errorGPG(QProcess::ProcessError error) {
    if (error) {
        // slot not used.
    }
}

void GPGManager::execute() {
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
    // TODO definir proprement le chemin vers getPrettyGoodPty
    if (m_action.getOptions().contains("--batch")) {
        m_gpg.start("./getPrettyGoodPty", QStringList("sh") << "-c" << QString("gpg " + args.join(" ") + "\n"));
        m_gpg.waitForStarted();
        while (m_action.hasInteraction()) {
            QString data = m_action.nextInteraction();
            m_gpg.write(data.toLatin1());
            if (data.startsWith("Passphrase:")) {
                emit newData("Passphrase: *****\n");
            } else {
                emit newData(data);
            }
        }
        m_gpg.write("%commit\n");
        emit newData("%commit\n");
        m_gpg.write("%echo done\n");
        emit newData("%echo done\n");

        connect(&m_gpg, &QProcess::readyReadStandardOutput, this, &GPGManager::readOutput);
        m_gpg.closeWriteChannel();
    } else {
        m_gpg.start("./getPrettyGoodPty", QStringList("sh") << "-c" << QString("gpg " + args.join(" ") + "\n"));
        m_gpg.waitForStarted();
        connect(&m_gpg, &QProcess::readyReadStandardOutput, this, &GPGManager::readOutput);
    }
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
            && askInteraction()) {
        sendInteraction();
    }
}

const QString& GPGManager::getOutput() const {
    return m_output;
}

void GPGManager::terminate(int s, QProcess::ExitStatus status) {
    if (status) {
        // variable not used.
    }
    disconnect(&m_gpg, &QProcess::readyReadStandardOutput, this, &GPGManager::readOutput);
    emit finished(s, m_output);
    emit isWatchingYou(m_cmd, m_output);
}

void GPGManager::setAction(const Action &a) {
    m_action = a;
}

void GPGManager::cancelProcess() {
    m_gpg.kill();
}


