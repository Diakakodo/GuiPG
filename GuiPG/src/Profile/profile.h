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
        explicit Profile(unsigned id, const QString& name, const QString& exec);

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
        /**
         * @brief getGPGExecutable Retourne le chemin vers l'exécutable de GPG.
         * @return Le chemin vers l'exécutable de GPG.
         */
        QString getGPGExecutable() const;
        /**
         * @brief setGPGExecutable Change le chemin vers l'exécutable de GPG pour le profil courant.
         * @param path Le nouveau chemin vers l'exécutable de GPG.
         */
        void setGPGExecutable(const QString& path);

    private:
        unsigned m_id;
        QString m_name;
        QString m_exec;
};

#endif // PROFILE_H
