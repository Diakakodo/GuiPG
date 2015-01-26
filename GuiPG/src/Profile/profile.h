#ifndef PROFILE_H
#define PROFILE_H

#include <QObject>

class Profile : public QObject {
    Q_OBJECT

    public:
        /**
         * @brief Profile Initialise un profil.
         * @param id L'id du profil.
         * @param name Le nom du profil.
         */
        explicit Profile(unsigned id, const QString& name);

        /**
         * @brief getId Retourne l'id de ce profil.
         * @return L'id de ce profil.
         */
        unsigned getId() const;
        /**
         * @brief getName Retourne le nom de ce profil.
         * @return Le nom de ce profil.
         */
        const QString& getName() const;

    private:
        unsigned m_id;
        QString m_name;
};

#endif // PROFILE_H
