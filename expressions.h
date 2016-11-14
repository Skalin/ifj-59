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
    P_DOLLAR,         //
    P_COMMA,          // ,
    P_BRACKET_L,      // (
    P_BRACKER_R,      // )
  
  //DOPLNIT
  } tInputs,

int precedAnalysis();
int getRule(tStack *stack, )

#endif
