#ifndef ACTION_H
#define ACTION_H

#include <QObject>
#include <QStringList>
#include <QException>

/** TODO : question est ce qu'on garde un system d'exceptions ou bien !?
 * @brief The IllegalStateException class
 *
 * Exception levée quand les préconditions d'une
 * méthode ne sont pas respécté.
 *
 */
class IllegalStateException : public QException
{
    public:
        explicit IllegalStateException(QString msg = "")
            : m_msg(msg) {}
        const char* what() const throw() {
          return m_msg.toLatin1();
        }
    void raise() const { throw *this; }
    IllegalStateException *clone() const { return new IllegalStateException(*this); }
    private:
        QString m_msg;
};

/**
 * @brief The Action class
 * Classe permettant de définir une action a éxécuter.
 *
 * Sachant qu'un action est composée obligatoirement d'une commande.
 *
 * Une action peut également contenir :
 *   - une liste d'options
 *   - une liste d'arguments
 *   - une liste d'interactions
 *
 */
class Action : public QObject {
    Q_OBJECT

    public:
        /**
         * @brief Action Construit une action correspondant
         * a la commande cmd, avec les arguments args, les options options
         * et les interactions interactions.
         *
         * Ainsi l'action représenté est l'éxecution de la ligne de commande :
         * PATH_EXECUTABLE options cmd args
         *
         * puis un envoie sur l'entrée standard de la liste des interactions.
         *
         * @param cmd Le nom de la commande
         * @param args La liste des arguments.
         * @param options La liste des options.
         * @param interactions La liste des interactions.
         */
        explicit Action(QString cmd,
                        const QStringList& args = QStringList(),
                        const QStringList& options = QStringList(),
                        const QStringList& interactions = QStringList());
        Action();

        ~Action();

        /**
         * @brief getCmd Retourne le nom de la commande de l'action.
         * @return Le nom de la commande de l'action.
         */
        const QString& getCmd() const;

        /**
         * @brief getArgs Retourne la liste des arguments de l'action.
         * @return La liste des arguments de l'action.
         */
        const QStringList& getArgs() const;

        /**
         * @brief getOptions Retourne la liste des options de l'action
         * @return Liste des options de l'action.
         */
        const QStringList& getOptions() const;

        /**
         * @brief getInteractions Retourne la liste des interactions de l'action.
         * @return La liste des interactions de l'action.
         */
        const QStringList& getInteractions() const;

        /**
         * @brief hasInteraction Indique si l'action a une interaction disponnible.
         * @return true si une interaction est disponnible false sinon.
         */
        bool hasInteraction() const;

        /**
         * @brief nextInteraction Retourne la prochaine interaction disponnible.
         * @pre hasInteraction()
         * @post l'interaction retournée n'est plus disponnible.
         * @return L'interaction suivante.
         */
        const QString& nextInteraction();

        Action& operator=(const Action& a);

    private:
        /**
         * @brief m_cmd Le nom de la commande de l'action.
         */
        QString m_cmd;
        /**
         * @brief m_args La liste des arguments de l'action.
         */
        QStringList m_args;
        /**
         * @brief m_options La liste des options de l'action.
         */
        QStringList m_options;
        /**
         * @brief m_interactions La liste des interactions de l'action.
         */
        QStringList m_interactions;
        /**
         * @brief m_index Index de la prochaine interaction.
         */
        unsigned m_index;


    signals:

    public slots:
};

#endif // ACTION_H
