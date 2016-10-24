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
#define NUMBER_OF_RESERVED_WORDS

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

/* Globální token */
extern tToken token;

/*
 * Získá token z analyzátoru a vrátí jej
 * @param token
 * @return jeden načtený token z analyzátoru
 */
tToken * getToken( tToken * token );

/*
 * Inicializuje token a vrací pointer na token
 * @param token
 * @return ukazatel na inicializovaný token
 */
tToken * initToken( tToken * token );

/*
 * Ruší již předem vytvořený token
 * @param token
 */
void destroyToken( tToken * token );

/*
 * Funkce aktualizuje hodnotu tokenu na hodnotu z parametru string
 * @param token
 * @param string
 */
tToken * updateToken( tToken * token, char *string );

/*
 * Projde pole keyword a přiřadí korektně k tokenu "id" z pole keyword
 * @param token
 */
void keywordCheckToken( tToken * token );



