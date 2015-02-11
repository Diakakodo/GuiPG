#include "action.h"

// Constructeurs

Action::Action(QString cmd, const QStringList &args, const QStringList &options, const QStringList &interactions)
    : m_cmd(cmd), m_args(args), m_options(options), m_interactions(interactions) {
    // On place l'index des interaction a 0.
    m_index = 0;
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
