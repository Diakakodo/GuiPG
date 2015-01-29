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

        /**
         * @brief isLoaded Retourne si la configuration d'un profil a été
         * chargé.
         * @return Vrai si la configuration d'un profil a été chargé.
         */
        bool isLoaded() const;
        /**
         * @brief loadProfiles Charge les profils disponibles.
         * @return Vrai si tout s'est bien passé.
         */
        bool loadProfiles();
        /**
         * @brief load Charge la configuration pour le profil donné. Dans le
         * cas où celui-ci n'existe pas, les valeurs par défaut sont attribuées.
         * @param p Le profil.
         * @return Vrai si tout s'est bien passé, faux sinon.
         */
        bool loadVars(const Profile* p);
        /**
         * @brief getProfile Retourne le profil associé à la configuration
         * chargée.
         * @return Le profil associé à la configuration chargée ou nullptr si
         * !isLoaded().
         */
        const Profile* getCurrentProfile() const;

        /**
         * @brief getProfiles Retourne la liste des profils.
         * @return La liste des profils.
         */
        const QList<Profile*>& getProfiles() const;
        /**
         * @brief getVars Retourne la table d'association clé => valeur chargée.
         * @return La table d'association clé => valeur chargée.
         */
        const QHash<QString, QDomElement>& getVars() const;
        /**
         * @brief save Sauvegarde la configuration pour le dernier profil
         * chargé.
         * @return Vrai si tout s'est bien passé, faux sinon.
         */
        bool save();


    private:
        /**
         * @brief attrIsProfileId Retourne vrai si attr vaut id.
         * @param attr L'attribut dont on veut vérifier la valeur.
         * @param id La valuer que l'on veut avoir.
         * @return Vrai si attr vaut id.
         */
        bool attrIsProfileId(const QString& attr, unsigned id) const;
        /**
         * @brief initConfig Initialise la configuration.
         */
        void initConfig();
        /**
         * @brief loadConfig Charge la configuration contenue dans un élément
         * donné.
         * @param root L'élément racine de la configuration.
         * @param parent Le nom de l'élément parent.
         */
        void loadConfig(QDomNode root, const QString& parent = QString());

        const Profile* m_currentProfile;
        QDomDocument m_doc;
        QString m_filePath;
        QList<Profile*> m_profiles;
        QDomElement m_profileElement;
        QHash<QString, QDomElement> m_vars;
};

#endif // CONFIGURATION_H
