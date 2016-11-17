/**
 * IFJ/IAL - Precedenční analýza
 * Varianta:    b/2/I
 * Soubor:      expressions.h
 * Tým:         59
 * Autoři:      Jan Hrbotický, xhrbot01@stud.fit.vutbr.cz
 *              Dominik Skála, xskala11@stud.fit.vutbr.cz
 *              Milan Hruban, xhruba08@stud.fit.vutbr.cz
 *              Martin Hons, xhonsm00@stud.fit.vutbr.cz
 *              David Hél, xhelda00@stud.fit.vutbr.cz
 */


#ifndef EXPRESSIONS
#define EXPRESSIONS

#include "stack.h"
#include "table.h"
#include "lexical_analyzer.h"
#include "typedef.h"
#include "ial.h"
#include "garbage_collector.h"

// definice struktury stringu
typedef struct SStr{
	char *data;
	int length;		        // délka řetězce
	int allocatedSize;	  // alokovaná paměť
} SString;


/* PRIORITY PRO PRECEDENCE TABLE  */
typedef enum {
    P_GREATER = G, // >
    P_LESSER = L, // <
    P_EQUAL = E, // =
    P_FAIL = F, //0
  } tPriority;

/* TERMINÁLY A NONTERMINÁLY  */
typedef enum {
    P_MUL,            // *
    P_DIV,            // /
    P_ADD,            // +
    P_SUB,            // -
    P_LESS,           // <
    P_LESS_EQUAL,     // <=  
    P_GREAT,          // >  
    P_GREAT_EQUAL,    // >=  
    P_EQUAL,          // ==
    P_NOT_EQUAL,      // !=
    P_ID,             // ID
    P_DOLLAR,         // $
    P_COMMA,          // ,
    P_BRACKET_L,      // (
    P_BRACKET_R,      // )
  
  // DOPLNIT
  } tInputs;


/*
 *
 */
int precedAnalysis();

/*
 *
 */
int getRule(tStack *stack, int something); // tady jste meli volno a asi cekate dalsi parametr, doplnil jsem "int something", je třeba refactor a překontrola jestli to je dobře

/*
 *
 */
int readInt();

/*
 *
 */
double readDouble;

/*
 *
 */
void print();

/*
 *
 */
SStr substr(SStr *str, int i, int n);

/*
 *
 */
int initString(SStr *str);

/*
 *
 */
int addCharacter(SStr *str, char c);

/*
 *
 */
int compareString(SStr *str1, SStr *str2);

/*
 *
 */

int strLength(SStr *str);

/*
 *
 */
void strClear(SStr *str);

/*
 *
 */
void destroyString(SString *str);

#endif
