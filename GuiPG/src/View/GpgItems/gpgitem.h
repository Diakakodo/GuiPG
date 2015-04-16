#ifndef GPGITEM_H
#define GPGITEM_H

#include <QTreeWidgetItem>
#include "../../Keys/gpgobject.h"
#include <QPoint>

// X(nom de l'enum, nom de la colone)
#define X_COLUMNS               \
X(NAME_COL,       "Nom")        \
X(MAIL_COL,       "Email")      \
X(VALIDITY_COL,   "Validité")   \
X(TRUST_COL,      "Confiance")  \
X(CREATION_COL,   "Création")   \
X(EXPIRATION_COL, "Expiration") \
X(LENGTH_COL,     "Taille")     \
X(ALGO_COL,       "Algo")       \
X(CAPACITY_COL,   "Capacité")   \
X(ID_COL,         "ID")


class GpgItem : public QTreeWidgetItem {

    public:

        GpgItem(QTreeWidget * parent, GpgObject* gpgObject);
        GpgItem(GpgObject* gpgObject);
        virtual ~GpgItem() = 0;

        virtual void showMenu(const QPoint &pos) = 0;

        // Cette enum permet de conter le nombre de colones
        // définie et de leur attribuer un numéro selon leur ordre de définition.
        #define X(id, str) id,
        enum columnsNumber {
            X_COLUMNS
            NB_COLUMNS
        };
        #undef X


        static QHash<int, QString> columns;

    protected:
        GpgObject* m_gpgObject;
};

#endif // GPGITEM_H
