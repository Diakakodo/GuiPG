#ifndef GPGMANAGER_H
#define GPGMANAGER_H

#include <QObject>
#include <QProcess>
#include "../Profile/profile.h"
#include "action.h"

class GPGManager : public QObject {
        Q_OBJECT

    public:
        explicit GPGManager(const Profile* p);

        void execute();
        const QString& getOutput() const;
        void setAction(const Action& a);

    signals:
        void finished(int s, const QString& output);

    private slots:
        void readOutput();
        void terminate(int s, QProcess::ExitStatus status);

    private:
        QProcess m_gpg;
        const Profile* m_profile;
        QString m_output;
        Action m_action;
};

#endif // GPGMANAGER_H
