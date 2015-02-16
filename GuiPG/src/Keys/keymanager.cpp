#include "keymanager.h"

KeyManager::KeyManager(const Profile *p) : m_gpg(new GPGManager(p)) {
    connect(m_gpg, &GPGManager::finished, this, &KeyManager::gpgFinished);
}

KeyManager::~KeyManager() {
    qDeleteAll(m_keys);
    delete m_gpg;
}

void KeyManager::load() {
    Action a("--list-keys");
    m_gpg->setAction(a);
    m_gpg->execute();
}
#include <QDebug>
void KeyManager::gpgFinished(int s, const QString &output) {
    QStringList lines = output.split("\n");
    for (int i = 1; i < lines.size(); ++i) {
        QStringList split = lines.at(i).split(":");
        if (split.first() == "pub") {
            Key* k = new Key(
                    Key::SCOPE_PUBLIC,
                    (Key::Algorithm) split.at(3).toInt(),
                    split.at(2).toUInt(),
                    (Key::Validity) split.at(1).at(0).toLatin1(),
                    split.at(4),
                    QDate::fromString(split.at(5), "yyyy-MM-dd"),
                    QDate::fromString(split.at(6), "yyyy-MM-dd"),
                    split.at(9)
            );
            qDebug() << split;
            m_keys.append(k);
        } else if (split.first() == "sub") {
            Key* k = new Key(
                    Key::SCOPE_PUBLIC,
                    (Key::Algorithm) split.at(3).toInt(),
                    split.at(2).toUInt(),
                    (Key::Validity) split.at(1).at(0).toLatin1(),
                    split.at(4),
                    QDate::fromString(split.at(5), "yyyy-MM-dd"),
                    QDate::fromString(split.at(6), "yyyy-MM-dd"),
                    split.at(9)
            );
            m_keys.last()->addSubKey(k);
        }
    }
    emit keysLoaded();
}

const QList<Key*>& KeyManager::getKeys() const {
    return m_keys;
}
