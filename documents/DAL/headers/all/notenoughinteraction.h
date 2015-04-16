#ifndef NOTENOUGHINTERACTION_H
#define NOTENOUGHINTERACTION_H

#include "gpgexception.h"

class NotEnoughInteraction : public GPGException
{
    public:
        NotEnoughInteraction(QString msg = "");
        ~NotEnoughInteraction();
};

#endif // NOTENOUGHINTERACTION_H
