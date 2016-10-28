/*
 * IFJ/IAL - Error handler
 * Varianta:    b/2/I
 * Subor:       error_handler.h
 * Tým:         59
 * Autoři:      Jan Hrbotický, xhrbot01@stud.fit.vutbr.cz
 *              Dominik Skála, xskala11@stud.fit.vutbr.cz
 *              Milan Hruban, xhruba08@stud.fit.vutbr.cz
 *              Martin Hons, xhonsm00@stud.fit.vutbr.cz
 *              David Hél, xhelda00@stud.fit.vutbr.cz
 */

#include "error_handler.c"

/*
 * Ukonci program a jako navratovou chybu pouzije prvni parametr
 * @param errorNumber hodnota erroru
 * @return
 */
void throwException( int errorNumber, int row);