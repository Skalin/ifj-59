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

#include <string.h>
#include "typedef.h"
#include "parser.h"
#include "garbage_collector.h"
#include "error_handler.h"
#include "lexical_analyzer.h"

//pomocne info o tokenu
tokenType tempType;
int tempStatic;
char *tempData;



// nabyva TRUE pokud parsujeme tridu main (metoda run musi byt v ni)
int isInMain = FALSE;

// TODO TODO TODO naplneni help structure vsude kde je potreba
// kontrola jestli neni vestavena funkce ( pole s vestavenymi funkcemi)
// kontrola semanticke chyby 8, natavit na 1 pri inicializaci rpomene

void pParse(){
	global.hasMain = FALSE;
	global.hasRun = FALSE;

	tToken * token;
	token = getToken();

	if(token->type != t_kw_class){
		throwException(2,0,0);
	}

	

	pClass();

	token = getToken();

	while (token->type == t_kw_class){
		
		pClass();
		token = getToken();
	}

	if(token->type != t_eof) {
		throwException(2,0,0);    // TODO TODO TODO syntax error right?
	}
	

	if ((global.hasMain && global.hasRun) == FALSE) {   // program nema bud tridu main nebo metodu run - sematicka chyba
		throwException(3,0,0);
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
		throwException(2,0,0);
	}

	if (strcmp(token->data, "Main") == 0){   // nasli jsme tridu main
		global.hasMain = TRUE;
		isInMain = TRUE;
	}
	// zkontrolovat jestli identifikator tridy uz neexistuje

	// vytvorit tridu v tabulce symbolu



	  //kill token with identifier

	token = getToken();    // and get a new one, should be left curly brace

	if(token->type != t_brace_l){
		throwException(2,0,0);
	}
	  // kill curly brace token and start parsing body of class;

	pClassBody();


}

void pClassBody(){
/**
** body of class. definice statickych promenych, funkci
**/

	tToken * token;
	token = getToken();

	if (token->type == t_kw_static){       //received 'static' keyword - defining global function or variable
		 //static

		token = getToken();

		// pokud je dalsi token datovy typ ( boolean jsem tam nedal, kdyztak doplnit jestli budem delat rozsireni (Kappa))
		if (token->type == t_kw_int || token->type == t_kw_string || token->type == t_kw_double || token->type == t_kw_void ){

			// ulozime si typ tokenu
			tempType = token->type;
			tempStatic = 1;

			 // zruseni tokenu s datatype
			// static dataType - musi nasledovat identifikator
			token = getToken();

			if (token->type != t_simple_ident){
				throwException(2,0,0);
			}

			 // ulozime si identifikator
			 tempData = token->data;
			 // identifikator

			token = getToken(); // nacist dalsi token, bud zavorka - funkce, jinak promena

			if (token->type == t_bracket_l) {
				
				if (strcmp(tempData,"run") == 0) { // funkce 'run'
					if (isInMain) {               // a jsme v class Main
						global.hasRun = TRUE;
					} else {
						// semanticka chyba, nemuze byt funkce run jinde nez v class Main
						throwException(3,0,0);
					}
					if (tempType != t_kw_void) {
					// navratovy typ run musi byt void
						throwException(3,0,0);
					}
				}
				pFunction();
			} else {
				
				pVar(token);
			}

				pClassBody(); // pokravujeme ve zpracovani zbytku tela tridy

		} else {
			// syntax error za keyword 'static' musi nasledovat datatype
			throwException(2,0,0);
		}
			// end  if (token->type == t_kw_static)
	} else if (token->type == t_kw_int || token->type == t_kw_string || token->type == t_kw_double) {
		// data type - promena (neni globalni)

		// ulozime si typ tokenu
		tempType = token->type;
		tempStatic = 0;
		 //datatype

		token = getToken();

		//musi nasledovat identifikator
		if (token->type != t_simple_ident){
			throwException(2,0,0);
		}
		// ulozime si identifikator
		tempData = token->data;
		

		pVar(NULL); //volame funkci pro parsovani promene

		pClassBody(); // pokravujeme ve zpracovani zbytku tela tridy

	} else if (token->type == t_brace_r) {
		
		isInMain = FALSE;
		// dalsi token je prava curly zavorka, konec tela  tridy vracime se do funkce pClass(); ( a z ni hned zpatku do funkce pParse();

	} else {
	// token neni ani kw 'static', ani datatype, ani zavorka na konec funkce - syntax error
		throwException(2,0,0);
	}

} // end function
void pFunction(){
/**
 * <type> ID(<params>){<commands>}
 */

	// funkci to zavola po obdrzeni <static> <dataType> (  ---- nasleduji parametry
	// hned volame funkci na zpracovani parametru

	

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
    //DELETE THIS
          token = getToken();
          while (token->type != t_semicolon) {
            
            token = getToken();
          }
          // END OF DELETE BLOCK
  }
  else {
    throwException(2,0,0);
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
    
    tempType = token->type;
    tempStatic = 0;

    //nacist identifikator
    token = getToken();
    if (token->type != t_simple_ident) {
      throwException(2,0,0);
    }
    tempData = token->data;
    

    // zpracovat parametr TODO

    pParamsNext(); // zpracovani dalsi parametru

  }
  else if (token->type == t_bracket_r) {
    //prava zavorka , funkce nema parametry
    
  }
  else {
    throwException(2,0,0);
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
		
	} else if (token->type == t_comma) {
		// carka, nasleduje dalsi parametr
		
		token = getToken();

		if (token->type == t_kw_int || token->type == t_kw_string || token->type == t_kw_double) {
			tempType = token->type;

			

			//nacist identifikator
			token = getToken();
			if (token->type != t_simple_ident) {
				throwException(2,0,0);
			}
			tempData = token->data;
			

			// zpracovat parametr TODO

			pParamsNext(); // zpracovani dalsi parametru
		} else {
			// carka a pak neco jineho nez datatype
			throwException(2,0,0);
		}
	} else {
		// ani carka ani zavorka
		throwException(2,0,0);
	}

}

void pCommands(){
/**
 * <L curly brace> <commands> <R curly brace>
 */
	tToken * token;
	token = getToken();

	if (token->type != t_brace_l){   // left curly brace, start of block
		throwException(2,0,0);
	}
	

	pSingleCommand(); //parse prikazu

}

void pSingleCommand(){

	tToken * token;
	token = getToken();

	switch(token->type){

		case t_brace_r:
			// prava curly zavorka, konec bloku prikazu
			return;
			break;

		case t_kw_if :
			// IF STATEMENT
			pIf();
			break;

		case t_kw_while :
			// WHILE LOOP
			pWhile();
			break;

		case t_kw_return :
			// RETURN statement
			// asi rovnou volam precedencni TODO
			break;

		case t_kw_static :
			// static keyword
			// TODO laterz
			break;

		case t_simple_ident :
		case t_complete_ident :
			//  identifikator,
			// prirazeni hodnoty promene, volam funkci,
			tempData = token->data;
			
			token = getToken();

			if (token->type == t_assignment) {
				// a =
				pVar(token);
				break;     // toto mozna pujde pryc
			} else if (token->type == t_bracket_l) {
				// volani funkce

				if (strcmp(tempData,"ifj16.print") == 0) {
					//vyresit ifj16.print TODO
					//DELETE THIS
					token = getToken();
					while (token->type != t_bracket_r) {
						
						token = getToken();
					}
					// END OF DELETE BLOCK
				} else {
					// nacist argumenty funkce
					pExprParams();
				}

				// mozna si ho precedencni uz vyresi, takze za pvar() v assigment musim dat break;
				token = getToken();
				if (token->type != t_semicolon) {
					// missing semicolon
					throwException(2,0,0);
				}
			}
		break;


		case t_kw_int :
		case t_kw_string:
		case t_kw_double:
			// prijde data type
			// deklarujeme lokalni promenou
			tempType = token->type;
			tempStatic = 0;
			


			token = getToken();
			if (token->type != t_simple_ident) {
				throwException(2,0,0);
			}

			tempData = token->data;
			

			pVar(NULL);

		break;


		default:
			// neocekavany vstup
			throwException(2,0,0);

	} //end switch

	// rekurzivni volani na dalsi prikaz
	pSingleCommand();
}

void pExprParams(){
/*
* parametry pri volani funkce - prvni parametr
*/
	tToken * token;
	token = getToken();

	if (token->type == t_bracket_r) {
		//zadne parametry;
		return;
	} else {
		// zpracovani jednoho parametru, nevim jeste jak TODO
		pExprParamsNext();
	}
}
void pExprParamsNext(){
/*
* zpracovani dalsiho parametru pri volani funkce
*/
	tToken * token;
	token = getToken();

	if (token->type == t_bracket_r) {
		//zadne dalsi parametry;
		return;
	} else if (token->type == t_comma) {
		// zpracovani jednoho parametru, nevim jeste jak TODO
		//DELETE THIS
		token = getToken();
		//END OF DELETE BLOCK
		pExprParamsNext();
	} else {
		throwException(2,0,0);
	}
}

void pIf(){
/***
 * if ( <expr> ) <commands> else <commands>
 */

	tToken * token;

	//DELETE THIS
	token = getToken();
	while (token->type != t_bracket_r) {
		
		token = getToken();
	}
	// END OF DELETE BLOCK

	pCommands();

	token = getToken();
	if (token->type != t_kw_else){   // else
		throwException(2,0,0);
	}
	

	// block of code for else
	pCommands();

}
void pWhile(){
/**
* while ( <expr> ) { <commands> }
*/

	tToken * token;

	//DELETE THIS
	token = getToken();
	while (token->type != t_bracket_r) {
		
		token = getToken();
	}
	// END OF DELETE BLOCK


	pCommands();
}

