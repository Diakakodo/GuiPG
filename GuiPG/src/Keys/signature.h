#ifndef SIGNATURE_H
#define SIGNATURE_H

#include <QObject>
#include <QDate>

class Signature : public QObject {
    Q_OBJECT

    public:
        enum Algorithm {
            ALGO_RSA,
            ALGO_DSA,
            ALGO_DSA_SIG,
            ALGO_RSA_SIG
        };

        explicit Signature(Algorithm a,
                           const QString& id,
                           const QDate& creation,
                           const QString& owner);

        const QString& getOwner() const;
        Algorithm getAlgorithm() const;
        const QDate& getCreationDate() const;
        const QString& getId() const;

    signals:

    public slots:

    private:
        Algorithm m_algo;
        QString m_id;
        QDate m_creation;
        QString m_owner;
};

#endif // SIGNATURE_H
