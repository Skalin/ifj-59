/**
 * IFJ/IAL - Lexikální analyzátor
 * Varianta:    b/2/I
 * Soubor:      parser.c
 * Tým:         59
 * Autoři:      Jan Hrbotický, xhrbot01@stud.fit.vutbr.cz
 *              Dominik Skála, xskala11@stud.fit.vutbr.cz
 *              Milan Hruban, xhruba08@stud.fit.vutbr.cz
 *              Martin Hons, xhonsm00@stud.fit.vutbr.cz
 *              David Hél, xhelda00@stud.fit.vutbr.cz
 */

#include <stdio.h>

#include "parser.h"
#include "garbage_collector.h"
#include "error_handler.h"
#include "lexical_analyzer.h"

void pParse(){
  tToken * token;
  
  if ((token = malloc(sizeof(tToken))) == NULL) //
    {
    throwException(10,0,0);
    return NULL;
    }
  
  
  token = token_get();
  if(token->type != t_eof)
    {
    throwException(12,0,0);
    } 
  
}  

void pClass(){
/**
 * class Main {
 * <type> Function {
 * }
 *
 */
}
void pFunction(){
/**
 * <type> ID(<params>){<commands>}
 */
}
void pVar(){
/**
 * <type> ID = <expr>;
 * <type> ID;
 *
 */
}

void pParams(){
/**
 * <type> ID
 */
}
void pCommands(){
/**
 *
 */
}
void pSingleCommand(){
/**
 *
 */
}
void pIf(){
/***
 * if ( <expr> ) <commands> else <commands>
 */
}
void pWhile(){
/**
 * while ( <expr> ) { <commands> }
 */
}

int isVar(int type){}
