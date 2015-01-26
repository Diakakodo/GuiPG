#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QObject>

class Configuration : public QObject
{
        Q_OBJECT
    public:
        explicit Configuration(QObject *parent = 0);

    signals:

    public slots:

};

#endif // CONFIGURATION_H
