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

        /**
         * @brief save Sauvegarde la configuration pour le dernier profil
         * chargé.
         * @return Vrai si tout s'est bien passé, faux sinon.
         */
        bool save();

        /**
         * @brief getDefaultProfile Retourne le profil défaut.
         * @return Le profil dont l'id correspond à l'id par défaut enregistré
         * par la configuration ou nullptr si aucun ne correspond.
         */
        Profile* getDefaultProfile() const;

        /**
         * @brief getDefaultProfileId Retourne l'id du profil par défaut.
         * @return L'id par défaut enregistré par la configuration qui
         * correspond à l'id de l'un des profils de la liste m_profiles
         * ou 0 sinon.
         */
        unsigned getDefaultProfileId() const;

        /**
         * @brief getProfileById Retourne un profil enregistré dans la
         * configutation.
         * @param id
         * @return Un profil enregistré dans la configutation ou nullptr si
         * aucun id ne correspond.
         */
        Profile* getProfileById(unsigned id) const;

        /**
         * @brief getProfiles Retourne la liste des profils.
         * @return La liste des profils.
         */
        const QList<Profile*>& getProfiles() const;

        /**
          * @brief addProfile Ajoute un profil à la liste des profils.
          * @param p le profil à ajouter
          */
        void addProfile(Profile* p);

        void deleteProfile(unsigned profileId);

        void setDefaultProfileId(unsigned profileId);


    private:
        /**
         * @brief addNode Ajoute un élément fils avec un noeud de texte.
         * @param name Nom de la balise.
         * @param value Valeur du noeud de texte.
         * @param doc Le document parent.
         * @param parent La balise parente.
         */
        void addNode(const QString& name, const QString& value,
                     QDomDocument& doc, QDomElement& parent);

        QString m_filePath;
        QList<Profile*> m_profiles;
        unsigned m_defaultProfileId;
};

#endif // CONFIGURATION_H
