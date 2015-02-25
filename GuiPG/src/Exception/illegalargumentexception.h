#ifndef ILLEGALARGUMENTEXCEPTION
#define ILLEGALARGUMENTEXCEPTION

#include <QException>
#include <QString>

/**
 * @brief La classe IllegalArgumentException
 *
 * Exception levée quand les préconditions concernant
 * un parametre d'une méthode ne sont pas respécté.
 *
 */
class IllegalArgumentException : public QException {
    public:
        explicit IllegalArgumentException(QString msg);
        const char* what() const throw();
    void raise() const;
    IllegalArgumentException *clone() const;
    private:
        QString m_msg;
};


#endif // ILLEGALARGUMENTEXCEPTION

