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


global.hasMain = FALSE;
global.hasRun = FALSE;

// nabyva TRUE pokud parsujeme tridu main (metoda run musi byt v ni)
bool isInMain = FALSE;

// TODO TODO TODO naplneni help structure vsude kde je potreba
// kontrola jestli neni vestavena funkce ( pole s vestavenymi funkcemi)
void pParse(){
  
  tToken * token;
  token = getToken();
  
  if(token->type != t_kw_class){
    throwException(2,0,0);
    }
 
  destroyToken(token);
  
  pClass();
  
  token = getToken();           
  
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
  
  if ((global.hasMain && global.hasRun) == FALSE) {   // program nema bud tridu main nebo metodu run - sematicka chyba
    throwException(3, NULL, NULL);
  }
  //uspesny konec
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
  
  if (strcmp(token->data, "Main") == 0){   // nasli jsme tridu main
    global.hasMain = TRUE;
    isInMain = TRUE;
  }
  // zkontrolovat jestli identifikator tridy uz neexistuje
  
  // vytvorit tridu v tabulce symbolu
  
  
  
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
  
  if (token->type == t_kw_static){       //received 'static' keyword - defining global function or variable
    destroyToken(token); //static
    
    token = getToken();
    
    // pokud je dalsi token datovy typ ( boolean jsem tam nedal, kdyztak doplnit jestli budem delat rozsireni (Kappa)) 
    if (token->type == t_kw_int || token->type == t_kw_string || token->type == t_kw_double || token->type == t_kw_void ){ 
      
      fillTemp(token->type, TRUE, NULL); // ulozime si typ tokenu
      
      detroyToken(token); // zruseni tokenu s datatype
      // static dataType - musi nasledovat identifikator
      token = getToken();
      
      if (token->type != t_simple_ident){
         throwException(2, NULL, NULL);
      }
      
      fillTemp(NULL, TRUE, token->data); // ulozime si identifikator
      
      destroyToken(token); // identifikator
      
      token = getToken(); // nacist dalsi token, bud zavorka - funkce, jinak promena
      
      if (token->type == t_bracket_l) {
        destroyToken();
        if (strcmp(temp->data,"run") == 0) { // funkce 'run'
          if (isInMain) {               // a jsme v class Main
            global.hasRun = TRUE;
          }
          else {
            // semanticka chyba, nemuze byt funkce run jinde nez v class Main
            throwException(3, NULL, NULL);
          }
          if (temp->type != t_kw_void) {
            // navratovy typ run musi byt void
            throwException(3, NULL, NULL);
          }
        }
        pFunction();
      }
      else {
        //destroyToken();
        pVar(token);
      }
      
      pCLassBody(); // pokravujeme ve zpracovani zbytku tela tridy
      
      
    } 
    else {
      // syntax error za keyword 'static' musi nasledovat datatype
      throwException(2, NULL, NULL);
    }
    
  } // end  if (token->type == t_kw_static)
  else if (token->type == t_kw_int || token->type == t_kw_string || token->type == t_kw_double) {
    // data type - promena (neni globalni)
    
    fillTemp(token->type, FALSE, NULL); // ulozime si typ tokenu
    
    destroyToken(token); //datatype
    
    token = getToken();
     
    //musi nasledovat identifikator
    if (token->type != t_simple_ident){
         throwException(2, NULL, NULL);
    }
    fillTemp(NULL, FALSE, token->data); // ulozime si identifikator
    
    destroyToken(token); // identifikator
    
    pVar(NULL); //volame funkci pro parsovani promene
    
    pCLassBody(); // pokravujeme ve zpracovani zbytku tela tridy
    
  }
  else if (token->type == t_brace_r) {
     destroyToken(token);
     isInMain = FALSE;
    // dalsi token je prava curly zavorka, konec tela  tridy vracime se do funkce pClass(); ( a z ni hned zpatku do funkce pParse();
    
  }
  else {
    // token neni ani kw 'static', ani datatype, ani zavorka na konec funkce - syntax error
    throwException(2, NULL, NULL);
  }
  
} // end function 
void pFunction(){
/**
 * <type> ID(<params>){<commands>}
 */
  
  // funkci to zavola po obdrzeni <static> <dataType> (  ---- nasleduji parametry
  // hned volame funkci na zpracovani parametru
  
  tToken * token;
  
  //kontorla jestli uz ta funkce neexistuje nebo jestli to neni vestavena fce
  // ulozit do tab. symbolu
  
  pParams();  // parse parametru
  
  pCommands(); // parse tela funkce
  
}
void pVar(tToken *token){
/**
 * variable assign
 * <type> ID = <expr>;
 * <type> ID;
 *
 */
  // v temp mame identifikator a typ promene
  // parametr je posledni nacteny token
  
  if (token == NULL) {
    token = getToken();
  }
  
  //musime vytvorit uzel
  // mozna kontrolovat jestli uz neexistuje
  
  if (token->type == t_semicolon) { // neprirazujem zadnou hodnotu, konec funkce
    return;
  }
  
  if (token->type == t_assignment) {
    // tady doplnit neco z precedencni
  }
  else {
    throwException(2, NULL, NULL);
  }
  
}

void pParams(){ 
/**
 * <type> ID
 */
  
  tToken * token;
  token = getToken();
  
  // leva zavorka uz nactena v pClass
  
  // 
  if (token->type == t_kw_int || token->type == t_kw_string || token->type == t_kw_double) {
    fillTemp(token->type, FALSE, NULL);
    destroyToken(token);
    
    //nacist identifikator
    token = getToken();
    if (token->type != t_simple_ident) {
      throwException(2, NULL, NULL);
    }
    fillTemp(NULL, FALSE, token->data);
    destroyToken(token);
    
    // zpracovat parametr TODO
    
    pParamsNext(); // zpracovani dalsi parametru
    
  }
  else if (token->type == t_bracket_r) {
    //prava zavorka , funkce nema parametry
    destroyToken(token);
  }
  else {
    throwException(2, NULL, NULL);
  }
  
}   

void pParamsNext(){
  /*
  *  , <dataType> <identifikator>
  */
  tToken * token;
  
  token = getToken();
  
  if (token->type == t_bracket_r) {
    // uzaviraci zavorka, zadny dalsi parametr
    destroyToken(token);
  }
  else if (token->type == t_comma) {
    // carka, nasleduje dalsi parametr
    destroyToken(token);
    token = getToken();
    
    if (token->type == t_kw_int || token->type == t_kw_string || token->type == t_kw_double) {
      fillTemp(token->type, FALSE, NULL);
      destroyToken(token);
      
      //nacist identifikator
      token = getToken();
      if (token->type != t_simple_ident) {
         throwException(2, NULL, NULL);
       }
       fillTemp(NULL, FALSE, token->data);
       destroyToken(token);
      
      // zpracovat parametr TODO
      
      pParamsNext(); // zpracovani dalsi parametru
    }
    else {
    // carka a pak neco jineho nez datatype
      throwException(2, NULL, NULL);
    }
  }
  else {
   // ani carka ani zavorka
    throwException(2, NULL, NULL);
  }

}
      
void pCommands(){
/**
 * <L curly brace> <commands> <R curly brace>
 */
    tToken * token;
    token = getToken();
  
    if (token->type != t_brace_l){   // left curly brace, start of block
        throwException(2, NULL, NULL);
    }
    destroyToken(token);
  
    token = getToken();
    
    switch(token->type){
        
      case t_brace_r: 
        // prava curly zavorka, konec bloku prikazu
        return;
        break;
       
      default:
        // neocekavany vstup
        throwException(2, NULL, NULL);
    
    } //end switch 

void pSingleCommand(){
  // TODO tato funkce je asi docela nakokos lepsi udelat vse v pCommands();

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
  // vlozi informace do pomocneho tokenu
 void fillTemp(tokenType type, bool isStatic, char data){
   if (type != NULL)
     temp->type = type;
   
   /*if (isStatic != NULL)
     temp->isStatic = isStatic;*/
   
   if (data != NULL)
     temp->data = data;
 
 }
