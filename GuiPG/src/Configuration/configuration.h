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
         * @brief load Charge la configuration pour le profil donné. Dans le
         * cas où celui-ci n'existe pas, les valeurs par défaut sont attribuées.
         * @param p Le profil.
         * @return Vrai si tout s'est bien passé, faux sinon.
         */
        bool load(const Profile* p);
        /**
         * @brief getGPGExecutable Retourne le chemin vers l'exécutable de GPG.
         * @return Le chemin vers l'exécutable de GPG.
         */
        QString getGPGExecutable() const;
        /**
         * @brief getProfile Retourne le profil associé à la configuration
         * chargée.
         * @return Le profil associé à la configuration chargée ou nullptr si
         * !isLoaded().
         */
        const Profile* getProfile() const;
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
        /**
         * @brief setGPGExecutable Change le chemin vers l'exécutable de GPG pour le profil courant.
         * @param path Le nouveau chemin vers l'exécutable de GPG.
         */
        void setGPGExecutable(const QString& path);

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

        QDomDocument m_doc;
        QString m_filePath;
        const Profile* m_profile;
        QDomElement m_profileElement;
        QHash<QString, QDomElement> m_vars;
};

#endif // CONFIGURATION_H
