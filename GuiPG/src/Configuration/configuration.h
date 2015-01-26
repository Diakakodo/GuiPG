#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QObject>
#include "../Profile/profile.h"

/**
 * Configuration du logiciel.
 */
class Configuration : public QObject {
    Q_OBJECT

    public:
        /**
         * @brief Configuration Initialise une configuration.
         * @param filePath Le chemin vers le fichier de configuration.
         */
        explicit Configuration(const QString& filePath);

        /**
         * @brief isLoaded Retourne si la configuration d'un profil a été
         * chargé.
         * @return Vrai si la configuration d'un profil a été chargé.
         */
        bool isLoaded();
        /**
         * @brief load Charge la configuration pour le profil donné. Dans le
         * cas où celui-ci n'existe pas, les valeurs par défaut sont attribuées.
         * @param p Le profil.
         * @return Vrai si tout s'est bien passé, faux sinon.
         */
        bool load(const Profile* p);
        /**
         * @brief getProfile Retourne le profil associé à la configuration
         * chargée.
         * @return Le profil associé à la configuration chargée ou nullptr si
         * !isLoaded().
         */
        const Profile* getProfile() const;
        /**
         * @brief save Sauvegarde la configuration pour le dernier profil
         * chargé.
         * @return Vrai si tout s'est bien passé, faux sinon.
         */
        bool save() const;

    private:
        QString m_filePath;
        const Profile* m_profile;
};

#endif // CONFIGURATION_H
