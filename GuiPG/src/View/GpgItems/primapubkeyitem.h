#ifndef PRIMAPUBKEYITEM_H
#define PRIMAPUBKEYITEM_H

#include "pubkeyitem.h"
#include "../../Keys/primapubkey.h"

#define ICON_SINGLE_KEY_PATH "/Icones/single_key.png"
#define ICON_DOUBLE_KEY_PATH "/Icones/double_keys.png"

// X(nom de l'enum, confiance)
#define X_TRUSTS                        \
X(EDIT_TRUST_UNDEFINED,     "Sans avis")\
X(EDIT_TRUST_INVALID,       "Aucune")   \
X(EDIT_TRUST_MARGINAL,      "Légère")   \
X(EDIT_TRUST_FULLY,         "Complète") \
X(EDIT_TRUST_ULTIMATELY,    "Ultime")

class PrimaPubKeyItem : public PubKeyItem
{
        Q_OBJECT
    public:
        PrimaPubKeyItem(PrimaPubKey* pub);
        ~PrimaPubKeyItem();

        void showMenu(const QPoint &pos);

        // Cette enum permet de conter le nombre de confiance
        // définie et de leur attribuer un numéro selon leur ordre de définition.
        #define X(id, str) id,
        enum trustNumber {
            X_TRUSTS
            NB_TRUST
        };
        #undef X

        static QHash<int, QAction*> trustActions;
        PrimaPubKey* getPrimaPubKey() const;

    public slots:
        void sign();
        void setPossibleTrustValue(int s, QString output);
        void trust(int value);
        void exportPublicKey();
        void exportSecretKey();
        void deleteKey();

    private:
        PrimaPubKey* m_pub;
        QList<int> m_possibleTrustValue;

        void getPossibleTrustValue();


};

#endif // PRIMAPUBKEYITEM_H
