/* _________________________________________________________________________
  /                                                                         \ 
 | ------------------------------------------------------------------------- |
 |  Auteurs : * Pierre-Luc BLOT                                              |
 |            * Matthieu   FIN                                               |
 |  Date    : 06/05/2014                                                     |
 |  Fichier : print_err_if.c                                                 |
 |                                                                           |
 | ------------------------------------------------------------------------- |
 |  Licence 3ème année - Université de Rouen - 2013 ~ 2014                   |
  \_________________________________________________________________________/
*/

#include "print_err_if.h"


bool print_err_if(const char *file, int line, const char *func,
                  int expr, const char *code, const char *cause) {
  if (! expr) {
    return false;
  }
  #ifdef DEBUG
    fprintf(stderr,
        "*** Error cause: %s\n"
        "*** file: %s, line: %d, function: %s()\n"
        "*** code: %s\n\n", 
        cause, file, line, func, code);
  #else
    // On affiche un message moins verbeux.
    fprintf(stderr, "*** Error cause: %s\n\n", cause);
  #endif // DEBUG
  return true;
}

bool print_errno_if(const char *file, int line, const char *func,
                    int expr, const char *code, const char *callSys) {
  if (! expr) {
    return false;
  }
  #ifdef DEBUG
    fprintf(stderr,
        "*** Error cause: %s : %s (code : %d)\n"
        "*** file: %s, line: %d, function: %s()\n"
        "*** code: %s\n\n", 
        callSys, strerror(errno), errno, file, line, func, code);
  #else
    // On affiche un message moins verbeux.
    fprintf(stderr, "*** Error cause: %s : %s\n\n", callSys, strerror(errno));
  #endif // DEBUG
  return true;
}

