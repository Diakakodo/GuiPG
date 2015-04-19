#ifndef PRIMAPUBKEYITEM_H
#define PRIMAPUBKEYITEM_H

#include "pubkeyitem.h"
#include "../../Keys/primapubkey.h"

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

    public slots:
        void sign();
        void exportPublicKey();
        void exportSecretKey();

    private:
        PrimaPubKey* m_pub;

};

#endif // PRIMAPUBKEYITEM_H
