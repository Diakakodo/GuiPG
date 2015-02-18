#include "keymanager.h"

KeyManager::KeyManager(const Profile *p) : m_gpg(new GPGManager(p)) {
    connect(m_gpg, &GPGManager::finished, this, &KeyManager::gpgFinished);
}

KeyManager::~KeyManager() {
    qDeleteAll(m_keys);
    delete m_gpg;
}

void KeyManager::load() {
    QStringList opt;
    opt << "--fixed-list-mode";
    Action a("--list-keys", QStringList(), opt);
    m_gpg->setAction(a);
    m_gpg->execute();
}
#include <QDebug>
void KeyManager::gpgFinished(int s, const QString &output) {
    QStringList lines = output.split("\n");
    QString lastOwner;
    for (int i = 1; i < lines.size(); ++i) {
        QStringList split = lines.at(i).split(":");
        if (split.first() == "pub") {
            ++i;
            QString owner = lines.at(i).split(":").at(9);

            Key* k = new Key(
                    Key::SCOPE_PUBLIC,
                    (Key::Algorithm) split.at(3).toInt(),
                    split.at(2).toUInt(),
                    (Key::Validity) split.at(1).at(0).toLatin1(),
                    split.at(4),
                    QDateTime::fromMSecsSinceEpoch(split.at(5).toULong() * 1000).date(),
                    QDateTime::fromMSecsSinceEpoch(split.at(6).toULong() * 1000).date(),
                    owner
            );
            m_keys.append(k);
            lastOwner = owner;
        } else if (split.first() == "sub") {
            Key* k = new Key(
                    Key::SCOPE_PUBLIC,
                    (Key::Algorithm) split.at(3).toInt(),
                    split.at(2).toUInt(),
                    (Key::Validity) split.at(1).at(0).toLatin1(),
                    split.at(4),
                    QDateTime::fromMSecsSinceEpoch(split.at(5).toULong() * 1000).date(),
                    QDateTime::fromMSecsSinceEpoch(split.at(6).toULong() * 1000).date(),
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
