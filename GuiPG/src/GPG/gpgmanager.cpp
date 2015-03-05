#include "gpgmanager.h"
#include <QDebug>

GPGManager::GPGManager(const Profile *p) : m_profile(p) {
    connect(&m_gpg, (void (QProcess::*)(int, QProcess::ExitStatus)) &QProcess::finished,
            this, &GPGManager::terminate);
    connect(&m_gpg, &QProcess::readyReadStandardOutput, this, &GPGManager::readOutput);
    connect(&m_gpg, (void (QProcess::*)(QProcess::ProcessError)) &QProcess::error, this, &GPGManager::errorGPG);
    connect(&m_gpg, &QProcess::stateChanged, this, &GPGManager::stateChanged);

    m_gpg.setProcessChannelMode(QProcess::MergedChannels);
    m_gpg.setReadChannel(QProcess::StandardOutput);
}

bool GPGManager::askInteraction() {
    QStringList l = m_output.split('\n', QString::SkipEmptyParts);
    if (!l.isEmpty()) {
        QString last = l.last();
        if (last.contains("[GNUPG:] GET_LINE")) {
            return true;
        }
    }
    return false;
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
}

void GPGManager::execute() {
    QStringList args;
    if (m_profile->getConfigurationPath() != "") {
        args << "--homedir" << m_profile->getConfigurationPath();
    }
    args << m_action.getOptions() << m_action.getCmd()
         << m_action.getArgs();
    qDebug() << m_profile->getGPGExecutable();
    qDebug() << args;

    m_gpg.start(m_profile->getGPGExecutable(), args);
}

void GPGManager::readOutput() {
    QString tmp = m_gpg.readAllStandardOutput();
    //qDebug() << tmp;
    m_output += tmp;
    if (m_gpg.state() == QProcess::Running
            && askInteraction()) {
        sendInteraction();
    }
}

const QString& GPGManager::getOutput() const {
    return m_output;
}

void GPGManager::terminate(int s, QProcess::ExitStatus status) {
    emit finished(s, m_output);
}

void GPGManager::setAction(const Action &a) {
    m_action = a;
}

