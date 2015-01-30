#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QObject>
#include <QDomDocument>
#include <QHash>
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

        ~Configuration();

        /**
         * @brief loadProfiles Charge les profils disponibles.
         * @return Vrai si tout s'est bien passé.
         */
        bool load();

        Profile* getProfileById(unsigned id) const;

        /**
         * @brief getProfiles Retourne la liste des profils.
         * @return La liste des profils.
         */
        const QList<Profile*>& getProfiles() const;

        /**
         * @brief save Sauvegarde la configuration pour le dernier profil
         * chargé.
         * @return Vrai si tout s'est bien passé, faux sinon.
         */
        bool save();


    private:

        QString m_filePath;
        QList<Profile*> m_profiles;
};

#endif // CONFIGURATION_H
