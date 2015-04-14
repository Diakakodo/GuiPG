#ifndef PROFILE_H
#define PROFILE_H

#include <QObject>
#include <QHash>
#include "../Keys/subseckey.h"
#include <QColor>

class Profile : public QObject {
    Q_OBJECT

    public:
        /**
         * @brief Profile Initialise un profil.
         * @param id L'id du profil.
         * @param name Le nom du profil.
         */
        explicit Profile(unsigned id = 1, const QString& name = "default");

        /**
         * @brief getConfigurationPath Retourne le chemin vers le dossier de config
         * @return le chemin vers le dossier de config
         */
        const QString& getConfigurationPath() const;

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
        const QString& getGPGExecutable() const;

        /**
         * @brief setGPGExecutable Change le chemin vers l'exécutable de GPG pour le profil courant.
         * @param path Le nouveau chemin vers l'exécutable de GPG.
         */
        void setGPGExecutable(const QString& exec);

        /**
         * @brief setConfigurationPath Modifie le chemin de config
         * @param path le chemin de config
         */
        void setConfigurationPath(const QString& path);

        QColor getValidityColor(GpgObject::Validity v) const;

        void setValidityColor(GpgObject::Validity v, const QColor& c);

        const QHash<GpgObject::Validity, QColor>& getValidityColors() const;

        const QColor& getSignatureColor() const;
        void setSignatureColor(const QColor& c);


    private:
        unsigned m_id;
        QString m_name;
        QString m_exec;
        QString m_path;
        QHash<GpgObject::Validity, QColor> m_validityColors;
        QColor m_signColor;
};

#endif // PROFILE_H
