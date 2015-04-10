#include "gpgmanager.h"
#include "QDebug"

GPGManager::GPGManager(const Profile *p) : m_profile(p) {
    connect(&m_gpg, (void (QProcess::*)(int, QProcess::ExitStatus)) &QProcess::finished,
            this, &GPGManager::terminate);
    connect(&m_gpg, (void (QProcess::*)(QProcess::ProcessError)) &QProcess::error, this, &GPGManager::errorGPG);
    connect(&m_gpg, &QProcess::stateChanged, this, &GPGManager::stateChanged);

    m_gpg.setProcessChannelMode(QProcess::MergedChannels);
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
}

void GPGManager::execute() {
    QByteArray args = " ";
    if (m_profile->getConfigurationPath() != "") {
        args.append("--homedir " + m_profile->getConfigurationPath() + " ");
    }
    for (QString option : m_action.getOptions()) {
        args.append(option + " ");
    }
    args.append(m_action.getCmd() + " ");
    for (QString argument : m_action.getArgs()) {
        args.append(argument + " ");
    }
    //qDebug() << m_profile->getGPGExecutable() << args;
    // TODO definir proprement le chemin vers getPrettyGoodPty
    // Ainsi que le nom du shell a lancer (éventuellement la variable d'env SHELL).
    m_gpg.start("./getPrettyGoodPty", QStringList("sh"));
    m_gpg.waitForReadyRead();
    m_prompt = m_gpg.readAllStandardOutput();
    QByteArray cmd(m_profile->getGPGExecutable().toLatin1());
    cmd.append(args);
    if (!cmd.endsWith("\n")) {
        cmd.append("\n");
    }
    m_gpg.write(cmd);

    m_gpg.waitForReadyRead();
    QString data;
    data = m_gpg.readAllStandardOutput();
    emit newData(data);
    m_output = data;
    connect(&m_gpg, &QProcess::readyReadStandardOutput, this, &GPGManager::readOutput);
    if (m_output.endsWith(m_prompt)) {
        m_output = m_output.split(m_prompt).at(0);
        m_gpg.kill();
    }
}

void GPGManager::readOutput() {
    QString data = m_gpg.readAllStandardOutput();
    m_output += data;
    if (data.endsWith(m_prompt)) {
        m_output = m_output.split(m_prompt).at(0);
        m_gpg.kill();
        QString tmp = data.split(m_prompt).at(0);
        if (tmp != "") {
            emit newData(tmp);
        }
    } else {
        emit newData(data);
    }
    if (m_gpg.state() == QProcess::Running
            && askInteraction()) {
        sendInteraction();
    }
}

const QString& GPGManager::getOutput() const {
    return m_output;
}

void GPGManager::terminate(int s, QProcess::ExitStatus status) {
    disconnect(&m_gpg, &QProcess::readyReadStandardOutput, this, &GPGManager::readOutput);
    emit finished(s, m_output);
    //emit finishedNoParam();

}

void GPGManager::setAction(const Action &a) {
    m_action = a;
}

void GPGManager::cancelProcess() {
    m_gpg.kill();
}


