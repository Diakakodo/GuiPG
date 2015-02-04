#ifndef GPGMANAGER_H
#define GPGMANAGER_H

#include <QObject>

class GPGManager : public QObject
{
        Q_OBJECT
    public:
        explicit GPGManager(QObject *parent = 0);

    signals:

    public slots:

};

#endif // GPGMANAGER_H
