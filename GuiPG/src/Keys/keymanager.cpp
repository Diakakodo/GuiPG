#include "keymanager.h"
#include "QDebug"
#include <QRegularExpression>

KeyManager::KeyManager(const Profile *p) : m_gpg(new GPGManager(p)) {

}

KeyManager::~KeyManager() {
    qDeleteAll(m_primaPubKeys);
    delete m_gpg;
}

void KeyManager::load() {
    QStringList opt;
    /*
    opt << "--fixed-list-mode" << "--with-colons";
    Action a("--list-sigs", QStringList(), opt);
    /*/
    opt << "--fixed-list-mode" << "--with-colons" << "--with-fingerprint" << "--with-fingerprint" << "--with-key-data";
    Action a("--list-sigs", QStringList(), opt);
    //*/
    m_gpg->setAction(a);
    connect(m_gpg, &GPGManager::finished, this, &KeyManager::gpgFinishedPublicKeys);
    m_gpg->execute();
}

QString extractNameOfUidStr(QString uidStr) {
    QString name = uidStr.split("<").first();
    name.truncate(name.lastIndexOf(' '));
    return name;
}
QString extractMailOfUidStr(QString uidStr) {
    QString mail = uidStr.split("<").last();
    mail.truncate(mail.lastIndexOf('>'));
    return mail;
}

void KeyManager::gpgFinishedPublicKeys(int s, const QString &output) {
    if (s) {
        // not used.
    }
    QStringList l = output.split("\n", QString::SkipEmptyParts);
    PrimaPubKey* lastPrimaPubKey = nullptr;
    GpgObject* last = nullptr;
    SubPubKey* lastsub = nullptr;
    Uid* lastuid = nullptr;
    for (QString line : l) {
        QStringList split = line.split(":");
        if (line.startsWith("pub:")) {
            PrimaPubKey* pub = new PrimaPubKey(
                        GPG_PUB_KEY,                            // keyscope
                        split.at(1),                            // validity
                        split.at(2).toLong(),                   // length
                        (QString) split.at(3).toInt(),          // algo
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
            m_primaPubKeys.append(pub);
        } else if (line.startsWith("sub:")) {
            lastuid = nullptr;
            SubPubKey* sub = new SubPubKey(
                    GPG_SUB_KEY,                            // keyscope
                    split.at(1),                            // validity
                    split.at(2).toLong(),                   // length
                    (QString) split.at(3).toInt(),          // algo
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
}

const QList<PrimaPubKey *> &KeyManager::getPubKeys() const {
    return m_primaPubKeys;
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
