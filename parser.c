/**
 * IFJ/IAL - Syntaktická analýza
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
  token = getToken();
  
  if(token->type != t_kw_class){
    throwException(2,0,0);
    }
  destroyToken(token);
  
  pClass();
  
  token = getToken();            //if it works it ain't stupid hehe xd
  
  while (token->type == t_kw_class){
    destroyToken(token);
    pClass();
    token = getToken();
  }
 
 if(token->type != t_eof)
    {
    throwException(2,0,0);    // TODO TODO TODO syntax error right?
    } 
  destroyToken(token);
  
}  

void pClass(){
/**
 * class Main {
 * <type> Function {
 * }
 *
 */
  tToken * token;
  token = getToken();
  
  if (token->type != t_simple_ident){
    throwException(2,0,0)
  }
  // zkontrolovat jestli identifikator tridy uz neexistuje
  
  // vytvorit tridu v tabulce symbolu
  
  // nejak se asi bude specialne resit trida main neco jako if (strcmp(token->data, "Main")
  
  destroyToken(token);  //kill token with identifier
  
  token = getToken();    // and get a new one, should be left curly brace
  
  if(token->type != t_brace_l){
     throwException(2,0,0);
  }
  destroyToken(token);  // kill curly brace token and start parsing body of class;
  
  pClassBody();
  
  
}

void pClassBody(){
/**
** body of class. definice statickych promenych, funkci
**/
  
  tToken * token;
  token = getToken();
  
  if (token->type == t_kw_static){ received 'static' keyword - defining global function or variable
  
  }
  
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
    if (token->type != t_brace_l){   // left curly brace, start of block
        throwException(2, NULL, NULL);
    }
    destroyToken(token);

    //commands TODO TODO TODO 
    // tady asi bude velky switch a rekurzivni volani 

    token = getToken();
    if (token->type != t_brace_r){   // right curly brace, end of block
        throwException(2, NULL, NULL);
    }
    destroyToken(token);

void pSingleCommand(){

   tToken * token = getToken();
   /*tToken */
  
  switch (token->type)
    {
        
      case t_kw_while {
         destroyToken(token);
         pWhile();
         break;
        }

      case t_kw_if {
         destroyToken(token);
         pIf();
         break;
        }
        
      case t_find {
         precedAnalysis();   //TODO
         break;
        }  
        
      case t_sort {
         precedAnalysis();   //TODO
         break;
        }  
        
      case t_length {
         precedAnalysis();   //TODO
         break;
        }  
        
      case t_substring {
         precedAnalysis();   //TODO
         break;
        }  
        
      case t_compare {
         precedAnalysis();   //TODO
         break;
        }  
        
      case t_read_int {
         precedAnalysis();   //TODO
         break;
        }  
        
      case t_read_double {
         precedAnalysis();   //TODO
         break;
        }  
        
      case t_read_substring {
         precedAnalysis();   //TODO
         break;
        } 
        
      case t_print {
         precedAnalysis();   //TODO
         break;
        }  
        
      case t_semicolon {
         throwException(2,0,0);
         break;
        }
    
      case t_simple_ident {
        
        
        }
    }
  
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
    if (token->type != t_kw_else){   // else
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
  
  if (token->type == t_int) {
    return TRUE;    
  }
  if (token->type == t_double) {
    return TRUE;    
  } 
  if (token->type == t_double_e) {
    return TRUE;    
  } 
  if (token->type == t_string) {
    return TRUE;    
  } 
  if (token->type == t_simple_ident) {
    return TRUE;    
  } 
   if (token->type == t_complete_ident) {
    return TRUE;    
  } 
    
   return FALSE;

}
