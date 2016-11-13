/**
 * IFJ/IAL - Lexikální analyzátor
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
  
  } tPriority;

/* TERMINÁLY A NONTERMINÁLY  */
typedef enum {
  
  } tInputs;

int precedence();
int getRule(tStack *stack, )

#endif
