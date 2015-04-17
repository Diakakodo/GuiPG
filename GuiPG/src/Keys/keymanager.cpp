#include "keymanager.h"
#include "QDebug"
#include <QRegularExpression>

KeyManager::KeyManager(Profile *p, MainWindow *window) : m_gpg(new GPGManager(p, window)) {
    m_hashprimaPubKeys = new QHash<QString, PrimaPubKey*>();
    m_hashprimaSecKeys = new QHash<QString, PrimaSecKey*>();
}

KeyManager::~KeyManager() {
    delete m_hashprimaPubKeys;
    delete m_hashprimaSecKeys;
    delete m_gpg;
}


void KeyManager::load() {
    QStringList optionsPubKeys;
    optionsPubKeys << "--fixed-list-mode"
                   << "--with-colons"
                   << "--with-fingerprint"
                   << "--with-fingerprint"
                   << "--with-key-data";
    Action actionPubKeys("--list-sigs", QStringList(), optionsPubKeys);

    m_gpg->setAction(actionPubKeys);
    connect(m_gpg, &GPGManager::finished, this, &KeyManager::gpgFinishedPublicKeys);
    m_gpg->execute();


}

void KeyManager::loadSecretKeys() {
    QStringList optionsSecKeys;
    optionsSecKeys << "--fixed-list-mode"
                   << "--with-colons"
                   << "--with-fingerprint"
                   << "--with-fingerprint"
                   << "--with-key-data";
    Action actionSeckeys("--list-secret-keys", QStringList(), optionsSecKeys);

    m_gpg->setAction(actionSeckeys);
    connect(m_gpg, &GPGManager::finished, this, &KeyManager::gpgFinishedSecretKeys);
    m_gpg->execute();
}

QString extractNameOfUidStr(QString uidStr) {
    if (!uidStr.contains("<")) {
        return uidStr;
    }
    QString name = uidStr.split("<").first();
    name.truncate(name.lastIndexOf(' '));
    return name;
}

QString extractMailOfUidStr(QString uidStr) {
    if (!uidStr.contains("<")) {
        return "";
    }
    QString mail = uidStr.split("<").last();
    mail.truncate(mail.lastIndexOf('>'));
    return mail;
}

void KeyManager::gpgFinishedSecretKeys(int s, const QString &output) {
    disconnect(m_gpg, &GPGManager::finished, this, &KeyManager::gpgFinishedSecretKeys);
    if (s) {
        // not used.
    }
    PrimaSecKey* lastPrimaSecKey = nullptr;
    GpgObject*   last            = nullptr;
    SubSecKey*   lastssb         = nullptr;
    Uid*         lastUid         = nullptr;
    QStringList l = output.split("\n", QString::SkipEmptyParts);
    for (QString line : l) {
        QStringList split = line.split(":");
        if (line.startsWith("sec")) {
            PrimaSecKey* sec = new PrimaSecKey(
                        GPG_SECRETE_KEY,       // keyscope
                        split.at(2).toLong(),  // length
                        split.at(3),           // algo
                        split.at(4),           // keyId
                        QDateTime::fromMSecsSinceEpoch(split.at(5).toULong() * 1000).date(),     // Date de création
                        split.at(6).isEmpty() ?                                                  //
                            QDate()                                                              // Date d'expiration.
                          : QDateTime::fromMSecsSinceEpoch(split.at(6).toULong() * 1000).date(), //
                        ""                     // fingerprint
                        );
            lastPrimaSecKey = sec;
            last = sec;
            m_hashprimaSecKeys->insert(sec->getKeyId(), sec);
        } else if (line.startsWith("ssb")) {

        } else if (line.startsWith("fpr")) {

        } else if (line.startsWith("uid")) {

        }
    }
    emit SecKeysLoaded();
    emit KeysLoaded();
}

void KeyManager::gpgFinishedPublicKeys(int s, const QString &output) {
    disconnect(m_gpg, &GPGManager::finished, this, &KeyManager::gpgFinishedPublicKeys);
    if (s) {
        // not used.
    }
    PrimaPubKey* lastPrimaPubKey = nullptr;
    GpgObject*   last            = nullptr;
    SubPubKey*   lastsub         = nullptr;
    Uid*         lastuid         = nullptr;
    QStringList l = output.split("\n", QString::SkipEmptyParts);
    for (QString line : l) {
        QStringList split = line.split(":");
        if (line.startsWith("pub:")) {
            PrimaPubKey* pub = new PrimaPubKey(
                        GPG_PUB_KEY,                            // keyscope
                        split.at(1),                            // validity
                        split.at(2).toLong(),                   // length
                        (QString) split.at(3),                  // algo
                        split.at(4),                            // keyId
                        QDateTime::fromMSecsSinceEpoch(split.at(5).toULong() * 1000).date(),     // Date de création
                        split.at(6).isEmpty() ?                                                  //
                            QDate()                                                              // Date d'expiration.
                          : QDateTime::fromMSecsSinceEpoch(split.at(6).toULong() * 1000).date(), //
                        split.at(8),            //Trust
                        split.at(11),           // capabilities
                        ""                      // fingerprint come later in lines
                        );
            lastPrimaPubKey = pub;
            last = pub;
            m_hashprimaPubKeys->insert(pub->getKeyId(), pub);
        } else if (line.startsWith("sub:")) {
            lastuid = nullptr;
            SubPubKey* sub = new SubPubKey(
                    GPG_SUB_KEY,                            // keyscope
                    split.at(1),                            // validity
                    split.at(2).toLong(),                   // length
                    (QString) split.at(3),          // algo
                    split.at(4),                            // keyId
                    QDateTime::fromMSecsSinceEpoch(split.at(5).toULong() * 1000).date(),     // Date de création
                    split.at(6).isEmpty() ?                                                  //
                        QDate()                                                              // Date d'expiration.
                      : QDateTime::fromMSecsSinceEpoch(split.at(6).toULong() * 1000).date(), //
                    split.at(11),           // capabilities
                    ""                      // fingerprint come later in lines
                    );
            last = sub;
            lastsub = sub;
            lastPrimaPubKey->addSubPubKey(sub);
        } else if (line.startsWith("fpr:")) {
            last->setFpr(split.at(10));
        } else if (line.startsWith("sig:")
                   || line.startsWith("rev:")) {
            QString name = extractNameOfUidStr(split.at(9));
            QString mail = extractMailOfUidStr(split.at(9));
            Signature* sig = new Signature(
                        split.at(3), // algo
                        split.at(4), // keyid
                        QDateTime::fromMSecsSinceEpoch(split.at(5).toULong() * 1000).date(), // create
                        name, // uid name
                        mail, // uid mail
                        split.at(10), // sigClass
                        (QString) split.at(10).at(2), // sigscope
                        split.at(15), // hashAlgo
                        split.at(12) // fingerprint
                        );
            if (lastsub == nullptr) {
                lastuid->addSignature(sig);
            } else {
                lastsub->addSignature(sig);
            }
        } else if (line.startsWith("uid")) {
            lastsub = nullptr;
            QString name = extractNameOfUidStr(split.at(9));
            QString mail = extractMailOfUidStr(split.at(9));
            Uid* uid = new Uid(split.at(1),
                               QDateTime::fromMSecsSinceEpoch(split.at(5).toULong() * 1000).date(), // create
                               split.at(7),
                               name, // name + comment
                               mail  // mail
                               );
            lastuid = uid;
            last = uid;
            lastPrimaPubKey->addUid(uid);
        }
    }
    emit PubKeysLoaded();
    loadSecretKeys();
}

QList<PrimaPubKey *> KeyManager::getPubKeys() const {
    return m_hashprimaPubKeys->values();
}

QList<PrimaSecKey *> KeyManager::getSecKeys() const {
    return m_hashprimaSecKeys->values();
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
