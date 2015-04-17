#ifndef SIGNATUREITEM_H
#define SIGNATUREITEM_H

#include "gpgitem.h"
#include "../../Keys/signature.h"

#define ICON_SIGNATURE_PATH "/../src/Icones/signature.png"

class SignatureItem : public GpgItem
{
    public:
        SignatureItem(Signature* sig);
        ~SignatureItem();
        void showMenu(const QPoint &pos);

    private:
        Signature* m_sig;
        QString m_uidName;
        QString m_uidMail;
};

#endif // SIGNATUREITEM_H
