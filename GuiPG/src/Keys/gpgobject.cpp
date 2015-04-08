#include "gpgobject.h"

GpgObject::GpgObject(PubkeyAlgo pubAlgo, QString keyId, QDate creationDate) :
    m_pubAlgo(pubAlgo), m_keyId(keyId), m_creationDate(creationDate)
{

}

GpgObject::~GpgObject()
{

}

