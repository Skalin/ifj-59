/**
 * IFJ/IAL - Lexikální analyzátor
 * Varianta:    b/2/I
 * Subor:       lexical_analyzer.h
 * Tým:         59
 * Autoři:      Jan Hrbotický, xhrbot01@stud.fit.vutbr.cz
 *              Dominik Skála, xskala11@stud.fit.vutbr.cz
 *              Milan Hruban, xhruba08@stud.fit.vutbr.cz
 *              Martin Hons, xhonsm00@stud.fit.vutbr.cz
 *              David Hél, xhelda00@stud.fit.vutbr.cz
 */

/**
  *Include všech souborů
  */

#include "lexical_analyzer.c"

/**
 * Definice
 */
#define NUMBER_OF_KEY_WORDS 17

/**
 * Prototyp funkce
 */
void printKeyWordTable(); // Vytiskne obsah tabulky klíčových slov


/**
 * Jednotlivé stavy automatu
 */
typedef enum {


};


/**
 * Struktura tokenu
 */
typedef struct
{

} tToken;

// Globální token
extern tToken token;

