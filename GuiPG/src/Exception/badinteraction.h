#ifndef BADINTERACTION_H
#define BADINTERACTION_H

#include "gpgexception.h"

class BadInteraction : public GPGException
{
    public:
        BadInteraction(QString msg = "");
        ~BadInteraction();
};

#endif // BADINTERACTION_H
