#include "action.h"

// Constructeurs
#include <QDebug>

/**
 * @brief setEOL Permet d'ajouter les '\n' manquant a la fin de chaques QString de la liste *l.
 * @param l pointeur sur la QStringList a modifier.
 * @post
 * pour toutes chaines s de l :
 *   si ((old s)[(old s).length - 1] == '\n')
 *   alors
 *     s == (old s)
 *   sinon
 *     s == (old s) + "\n"
 */
void setEOL(QStringList* l) {
    for (int i = 0; i < l->length(); ++i) {
        if ( (*l)[i][(*l)[i].length() - 1] != '\n' ) {
            l->replace(i, (*l)[i] + "\n");
        }
    }
}
Action::Action(QString cmd, const QStringList &args, const QStringList &options, const QStringList &interactions)
    : m_cmd(cmd), m_args(args), m_options(options), m_interactions(interactions) {
    // On place l'index des interaction a 0.
    m_index = 0;
    for (QString s : m_interactions) {
        if (s.isEmpty()) {
            throw IllegalArgumentException("Une interaction est vide");
        }
    }
    setEOL(&m_interactions);
    for (QString s : m_interactions) {
        if (s.contains('\n')) {

        }
    }
}


Action::Action() {

}

// Destructeur

Action::~Action()
{

}

// Requetes

const QString& Action::getCmd() const {
    return m_cmd;
}

const QStringList& Action::getArgs() const {
    return m_args;
}

const QStringList& Action::getOptions() const {
    return m_options;
}

const QStringList& Action::getInteractions() const {
    return m_interactions;
}

bool Action::hasInteraction() const {
    return m_index < (unsigned) m_interactions.length();
}

// Commandes

const QString& Action::nextInteraction() {
    if (!this->hasInteraction()) {
        throw IllegalStateException("!this->hasInteraction()");
    }
    ++m_index;
    return m_interactions.at(m_index - 1);
}

Action& Action::operator =(const Action& a) {
    m_options = a.getOptions();
    m_args = a.getArgs();
    m_cmd = a.getCmd();
    m_index = 0;
    m_interactions = a.getInteractions();
    return *this;
}
