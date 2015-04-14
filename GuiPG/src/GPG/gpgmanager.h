#ifndef GPGMANAGER_H
#define GPGMANAGER_H

#include <QObject>
#include <QProcess>
#include "../Profile/profile.h"
#include "action.h"
#include <QSemaphore>

class GPGManager : public QObject {
        Q_OBJECT

    public:
        explicit GPGManager(const Profile* p);
        ~GPGManager();
        void execute();
        const QString& getOutput() const;
        void setAction(const Action& a);
        void cancelProcess();

    signals:
        void finished(int s, const QString& output);
        void newData(const QString& data);
        void finishedNoParam();
        void isWatchingYou(QString cmd, QString output);

    private slots:
        void readOutput();
        void terminate(int s, QProcess::ExitStatus status);
        void errorGPG(QProcess::ProcessError error);
        void stateChanged(QProcess::ProcessState newState);

    private:
        QProcess m_gpg;
        const Profile* m_profile;
        QString m_output;
        QString m_cmd;
        Action m_action;

        /**
         * @brief sendInteraction
         * @pre
         *      m_gpg.state() == QProcess::Running
         *   && askInteraction()
         */
        void sendInteraction();
        /**
         * @brief askInteraction Permet de savoir si le retour de GPG necessite
         * une interaction ou non.
         * @return un booléen indiquant si gpg attend des données.
         */
        bool askInteraction();
};

#endif // GPGMANAGER_H
