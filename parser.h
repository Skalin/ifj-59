/**
 * IFJ/IAL - Syntaktická analýza
 * Varianta:    b/2/I
 * Soubor:      parser.h
 * Tým:         59
 * Autoři:      Jan Hrbotický, xhrbot01@stud.fit.vutbr.cz
 *              Dominik Skála, xskala11@stud.fit.vutbr.cz
 *              Milan Hruban, xhruba08@stud.fit.vutbr.cz
 *              Martin Hons, xhonsm00@stud.fit.vutbr.cz
 *              David Hél, xhelda00@stud.fit.vutbr.cz
 */

#ifndef IFJ_59_PARSER_H
#define IFJ_59_PARSER_H


/**
HLAVIČKY FUNKCÍ
*/
/**
* Funkce zacne parsovani souboru
*/
void pParse();

/**
* Funkce pro parsovani trid v souboru
*/
void pClass();

/**
* Funkce pro parsovani tela tridy
*/
void pClassBody();

/**
* Funkce pro parsovani deklarace promene, nebo prirazeni hodnoty promene
*/
void pVar(tToken *token);

/**
* Funkce pro parsovani tela funkce
*/
void pFunction();

/**
* Funkce pro parsovani prvniho argumentu pri deklaraci funkce
*/
void pParams();

/**
* Funkce pro parsovani dalsich argumentu pri deklaraci funkce
*/
void pParamsNext();

/**
*Funkce pro parsovani bloku prikazu
*/
void pCommands();

/**
* Funkce pro parsovani jednoho prikazu
*/
void pSingleCommand();

/**
* Funkce pro parsovani prvniho argumentu pri volani funkce
*/
void pExprParams();

/**
* Funkce pro parsovani dalsich argumentu pri volani funkce
*/
void pExprParamsNext();

/**
* Funkce pro parsovani ridici struktury if
*/
void pIf();

/**
* Funkce pro parsovani cyklu while
*/
void pWhile();



#endif //IFJ_59_PARSER_H


