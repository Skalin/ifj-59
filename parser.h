/**
 * IFJ/IAL - Lexikální analyzátor
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
void pParse();  
void pClass();
void pVars();
void pVar();
void pFunction();
void pArgs();
void pCommands();
void pIf();
void pWhile();

int isVar(int type);
  
#endif //IFJ_59_PARSER_H

// struktura pro ukladani doceasnych informaci o tokenu
typedef struct {
	tokenType type;   // typ tokenu
	char data[];      // data tokenu
} tTemp;

struct tTemp temp;
