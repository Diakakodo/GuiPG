#include "keymanager.h"
#include "QDebug"
#include <QRegularExpression>

KeyManager::KeyManager(const Profile *p) : m_gpg(new GPGManager(p)) {

}

KeyManager::~KeyManager() {
    qDeleteAll(m_keys);
    delete m_gpg;
}

void KeyManager::load() {
    QStringList opt;
    /*
    opt << "--fixed-list-mode" << "--with-colons";
    Action a("--list-sigs", QStringList(), opt);
    /*/
    opt << "--fixed-list-mode" << "--with-colons" << "--with-fingerprint" << "--with-fingerprint" << "--with-key-data";
    Action a("--list-public-keys", QStringList(), opt);
    //*/
    m_gpg->setAction(a);
    connect(m_gpg, &GPGManager::finished, this, &KeyManager::gpgFinished);
    m_gpg->execute();
}

void KeyManager::gpgFinished(int s, const QString &output) {
    /*
    QStringList lines = output.split("\n");
    Key* last = nullptr;
    Key* lastKey = nullptr;
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
                    owner,
                    (Key::Validity) split.at(8).at(0).toLatin1()
            );
            m_keys.append(k);
            last = k;
            lastKey = k;
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
                    last->getOwner()
            );
            lastKey->addSubKey(k);
            last = k;
        } else if (split.first() == "sig") {
            Signature* s = new Signature(
                    (Key::Algorithm) split.at(3).toInt(),
                    split.at(4),
                    QDateTime::fromMSecsSinceEpoch(split.at(5).toULong() * 1000).date(),
                    split.at(9)
            );
            last->addSignature(s);
        }
    }
    emit keysLoaded();
    */
    QStringList l = output.split("\n", QString::SkipEmptyParts);
    for (QString line : l) {
        QStringList split = line.split(":");
        if (line.startsWith("pub:")) {
            PrimaPubKey* pub = new PrimaPubKey(
                        PrimaPubKey::KEYSCOPE_PUBLIC,
                        (GpgObject::Validity) split.at(1).at(0).toLatin1(),
                        split.at(2).toLong(),
                        (GpgObject::Algorithm) split.at(3).toInt(),
                        split.at(4),
                        QDate(),// TODO
                        QDate(),// TODO
                        PrimaPubKey::TRUST_UNKNOWN,//TODO
                        "");
        } else if (line.startsWith("")) {

        }
    }
}

const QList<GpgObject *> &KeyManager::getKeys() const {
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
