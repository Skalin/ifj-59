/**
 * IFJ/IAL - Error handler
 * Varianta:    b/2/I
 * Soubor:       error_handler.h
 * Tým:         59
 * Autoři:      Jan Hrbotický, xhrbot01@stud.fit.vutbr.cz
 *              Dominik Skála, xskala11@stud.fit.vutbr.cz
 *              Milan Hruban, xhruba08@stud.fit.vutbr.cz
 *              Martin Hons, xhonsm00@stud.fit.vutbr.cz
 *              David Hél, xhelda00@stud.fit.vutbr.cz
 */
#ifndef ERROR_HANDLER
#define ERROR_HANDLER

/*
 * Ukonci program a jako navratovou chybu pouzije prvni parametr
 * @param errorNumber cislo chyboveho stavu
 * @param row cislo radku na kterem se chyba vyskytla
 * @param column cislo sloupce (znaku) na kterem se chyba vyskytla
 * @return
 */
void throwException(int errorNumber, int row, int column);

#endif
