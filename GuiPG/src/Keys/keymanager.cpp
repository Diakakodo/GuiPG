#include "keymanager.h"

KeyManager::KeyManager(const Profile *p) : m_gpg(new GPGManager(p)) {
    connect(m_gpg, &GPGManager::finished, this, &KeyManager::gpgFinished);
}

KeyManager::~KeyManager() {
    qDeleteAll(m_keys);
    delete m_gpg;
}
#include <QDebug>
void KeyManager::load() {
    QStringList opt;
    //*
    opt << "--fixed-list-mode" << "--with-colons";
    Action a("--list-keys", QStringList(), opt);
    /*/
    //opt << "--status-fd=1" << "--command-fd=0" << "--no-tty";
    //Action a("--full-gen-key", QStringList(), opt);
    opt << "--status-fd=1" << "--command-fd=0" << "--no-tty";
    QStringList interact;
    interact << "1" << "2048\n" << "1" << "bidon" << "bidon@albert.cul" << "" << "O";
    Action a("--full-gen-key", QStringList(), opt, interact);
    //*/
    m_gpg->setAction(a);
    m_gpg->execute();
}
#include <QDebug>
void KeyManager::gpgFinished(int s, const QString &output) {
    //qDebug() << output;
    QStringList lines = output.split("\n");
    QString lastOwner;
    for (int i = 1; i < lines.size(); ++i) {
        QStringList split = lines.at(i).split(":");
        if (split.first() == "pub") {
            ++i;
            QString owner = lines.at(i).split(":").at(9);
            bool ok = false;
            unsigned long e = split.at(6).toULong(&ok);
            QDate expiration;
            if (ok) {
                expiration = QDateTime::fromMSecsSinceEpoch(e * 1000).date();
            }
            Key* k = new Key(
                    Key::SCOPE_PUBLIC,
                    (Key::Algorithm) split.at(3).toInt(),
                    split.at(2).toUInt(),
                    (Key::Validity) split.at(1).at(0).toLatin1(),
                    split.at(4),
                    QDateTime::fromMSecsSinceEpoch(split.at(5).toULong() * 1000).date(),
                    expiration,
                    owner
            );
            m_keys.append(k);
            lastOwner = owner;
        } else if (split.first() == "sub") {
            bool ok = false;
            unsigned long e = split.at(6).toULong(&ok);
            QDate expiration;
            if (ok) {
                expiration = QDateTime::fromMSecsSinceEpoch(e * 1000).date();
            }
            Key* k = new Key(
                    Key::SCOPE_PUBLIC,
                    (Key::Algorithm) split.at(3).toInt(),
                    split.at(2).toUInt(),
                    (Key::Validity) split.at(1).at(0).toLatin1(),
                    split.at(4),
                    QDateTime::fromMSecsSinceEpoch(split.at(5).toULong() * 1000).date(),
                    expiration,
                    lastOwner
            );
            m_keys.last()->addSubKey(k);
        }
    }
    emit keysLoaded();
}

const QList<Key*>& KeyManager::getKeys() const {
    return m_keys;
}

QDate KeyManager::strToDate(const QString& d) const {
    bool nb = false;
    unsigned long timestamp = d.toULong(&nb);
    if (nb) {
        return QDateTime::fromMSecsSinceEpoch(timestamp).date();
    } else {
        return QDate::fromString(d, "yyyy-MM-dd");
    }
}
