#ifndef PROFILE_H
#define PROFILE_H

#include <QObject>

class Profile : public QObject {
    Q_OBJECT

    public:
        explicit Profile();

        unsigned getId();

    signals:

    public slots:

};

#endif // PROFILE_H
