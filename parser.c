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
#include <stdlib.h>

#include "parser.h"
#include "garbage_collector.h"
#include "error_handler.h"
#include "lexical_analyzer.h"
#include "table.h"
#include "generator.h"
#include "stack.h"

void pParse(){
  tToken * token;
  
  if ((token = plusMalloc() == NULL) //
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
 * <L curly brace> <commands> <R curly brace>
 */
    tToken * token = getToken();
    if (token->type != LA_BRACE_L){   // left curly brace, start of block
        throwException(2, NULL, NULL);
    }
    destroyToken(token);

    //commands TODO TODO TODO 
    // tady asi bude velky switch a rekurzivni volani 

    token = getToken();
    if (token->type != LA_BRACE_R){   // right curly brace, end of block
        throwException(2, NULL, NULL);
    }
    destroyToken(token);

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

    // tato funkce je volana kdyz parser obdrzi token 'if'
    // uvolneni tokenu by se melo provest uz v hlavni funkci parseru

   

   /* if (token->type != LA_BRACKET_L){   // left brace
        throwException(2, NULL, NULL);
    }
    destroyToken(token);*/

    // here should be expression         // pokud budem mit gramatiku tak ze expression muze byt i v zavorkach je tahle cast zbytecna

   /* token = getToken();
    if (token->type != LA_BRACKET_R){   // right brace
        throwException(2, NULL, NULL);
    }
    destroyToken(token); */

    // block of code
    pCommands();

    tToken * token = getToken();
    if (token->type != LA_KW_ELSE){   // else
        throwException(2, NULL, NULL);
    }
    destroyToken(token);

    // block of code for else
    pCommands();

}
void pWhile(){
/**
 * while ( <expr> ) { <commands> }
 */
  
   /* tToken * token;
    *token = getToken();
  
    if (token->type != LA_BRACKET_L) {   //pokud neexistuje levá závorka, jde o syntaktickou chybu
       throwException(2, NULL, NULL);
      }
    destroyToken(token);
  
    token = getToken();
    if (token->type != LA_BRACKET_R) {   //pokud neexistuje pravá závorka, jde o syntaktickou chybu
       throwException(2, NULL, NULL);
      }
    destroyToken(token);*/
    
    //expression
  
    pCommands();
}

int isVar(tToken token){
 
  tToken * token = token;
  
  if (token->type == LA_INT) {
    return TRUE;    
  }
  if (token->type == LA_DOUBLE) {
  return TRUE;    
  } 
  if (token->type == LA_DOUBLE_pE) {
  return TRUE;    
  } 
  if (token->type == LA_DOUBLE_E_SIGN) {
  return TRUE;    
  } 
  if (token->type == LA_DOUBLE_E) {
  return TRUE;    
  } 
   if (token->type == LA_STRING) {
  return TRUE;    
  } 
    
   return FALSE;

}
