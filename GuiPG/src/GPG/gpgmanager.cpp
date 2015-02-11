#include "gpgmanager.h"
#include <QDebug>

GPGManager::GPGManager(const Profile *p) : m_profile(p) {
    connect(&m_gpg, (void (QProcess::*)(int, QProcess::ExitStatus)) &QProcess::finished,
            this, &GPGManager::terminate);
    connect(&m_gpg, &QProcess::readyReadStandardOutput, this, &GPGManager::readOutput);
}

void GPGManager::execute() {
    QStringList args;
    args << m_action.getOptions() << "--with-colons" << m_action.getCmd()
         << m_action.getArgs();
    m_gpg.start(m_profile->getGPGExecutable(), args);
}

void GPGManager::readOutput() {
    m_output += m_gpg.readAllStandardOutput();
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
