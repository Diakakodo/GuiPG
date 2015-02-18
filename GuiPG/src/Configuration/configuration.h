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

        Profile* getDefaultProfile() const;

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


        /**
         * @brief save Sauvegarde la configuration pour le dernier profil
         * chargé.
         * @return Vrai si tout s'est bien passé, faux sinon.
         */
        bool save();


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
};

#endif // CONFIGURATION_H
