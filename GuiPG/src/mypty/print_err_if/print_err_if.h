/* _________________________________________________________________________
  /                                                                         \ 
 | ------------------------------------------------------------------------- |
 |  Auteurs : * Pierre-Luc BLOT                                              |
 |            * Matthieu   FIN                                               |
 |  Date    : 06/05/2014                                                     |
 |  Fichier : print_err_if.h                                                 |
 |                                                                           |
 | ------------------------------------------------------------------------- |
 |  Licence 3ème année - Université de Rouen - 2013 ~ 2014                   |
  \_________________________________________________________________________/
*/

#ifndef PRINT_ERR_IF_H
#define PRINT_ERR_IF_H

#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE
#endif
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
//----

#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>


#ifdef EXPANDED_PRINT_ERR_IF
#define STRING(expr) #expr
#define PRINT_ERR_IF(expr, cause) print_err_if( \
    __FILE__, __LINE__, __func__, \
    expr, STRING(expr), cause)
#define PRINT_ERRNO_IF(expr, callSys) print_errno_if( \
    __FILE__, __LINE__, __func__, \
    expr, STRING(expr), callFunc)
#else
#define PRINT_ERR_IF(expr, cause) print_err_if( \
    __FILE__, __LINE__, __func__, \
    expr, #expr, cause)
#define PRINT_ERRNO_IF(expr, callSys) print_errno_if( \
    __FILE__, __LINE__, __func__, \
    expr, #expr, callSys)
#endif // (EXPANDED_)PRINT_ERR_IF

/*
 * Si expr est vérifié
 *    Affiche un message d'erreur.
 *    Ce message est plus verbeux si compiler avec la macro DEBUG de définie.
 *    Retourne true.
 * Sinon
 *    Retourne false.
 */
extern bool print_err_if(const char *file, int line, const char *func,
                         int expr, const char *code, const char *cause);

extern bool print_errno_if(const char *file, int line, const char *func,
                           int expr, const char *code, const char *callSys);

extern bool print_errgai_if(const char *file, int line, const char *func,
                            int expr, const char *code, const char *callFunc, int errnum);

#endif // PRINT_ERR_IF_H
