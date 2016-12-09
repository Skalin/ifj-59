/**
 * IFJ/IAL - Syntaktická analýza
 * Varianta:    b/2/I
 * Soubor:      parser.c
 * Tým:         59
 * Autoøi:      Jan Hrbotický, xhrbot01@stud.fit.vutbr.cz
 *              Dominik Skála, xskala11@stud.fit.vutbr.cz
 *              Milan Hruban, xhruba08@stud.fit.vutbr.cz
 *              Martin Hons, xhonsm00@stud.fit.vutbr.cz
 *              David Hél, xhelda00@stud.fit.vutbr.cz
 */

#include <string.h>
#include "typedef.h"
#include "parser.h"
#include "garbage_collector.h"
#include "expressions.h"
#include "error_handler.h"
#include "lexical_analyzer.h"
#include "ial.h"

//pomocne info o tokenu
tokenType tempType;
int tempStatic;
char *tempData;



// nabyva TRUE pokud parsujeme tridu main (metoda run musi byt v ni)
int isInMain = FALSE;
//nabyva true pri parsovnani metody run
int isInRun = FALSE;

// TODO TODO TODO naplneni help structure vsude kde je potreba
// kontrola semanticke chyby 8, natavit na 1 pri inicializaci rpomene

void pParse(){
	global.hasMain = FALSE;
	global.hasRun = FALSE;

	tToken * token;
	token = getToken();
	//printToken(token);
	
		// no main.run
	if (token->type == t_eof){
		throwException(3,0,0);
	}

	if(token->type != t_kw_class){
		throwException(2,0,0);
	}

	

	pClass();

	token = getToken();
	//printToken(token);

	while (token->type == t_kw_class){
		
		pClass();
		token = getToken();
		//printToken(token);
	}

	if(token->type != t_eof) {
		throwException(2,0,0);    // TODO syntax?
	}
	

	if ((global.hasMain && global.hasRun) == FALSE) {   // program nema bud tridu main nebo metodu run - semanticka chyba
		throwException(3,0,0);
	}
	
	//completeInstr();  //TODO
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
	//printToken(token);

	if (token->type != t_simple_ident){
		throwException(2,0,0);
	}

	if (strcmp(token->data, "Main") == 0){   // nasli jsme tridu main
		global.hasMain = TRUE;
		isInMain = TRUE;
	}
	// zkontrolovat jestli identifikator tridy uz neexistuje
	BTSNode * node;
	node = searchForNode(token->data, class, NULL); //TODO start??
	
	if (node != NULL){
		// pokus o definici tridy se stejnym jmenem
		throwException(3,0,0);
	}
	
	// vytvorit tridu v tabulce symbolu
	createNewNode(token->data, class, var_null, 1, 1);	

	token = getToken();
	//printToken(token);

	if(token->type != t_brace_l){
		throwException(2,0,0);
	}
	  

	pClassBody();


}

void pClassBody(){
/**
** body of class. definice statickych promenych, funkci
**/

	tToken * token;
	token = getToken();
	//printToken(token);

	if (token->type == t_kw_static){       // funkce nebo globalni promena
		 //static

		token = getToken();
		//printToken(token);

		// pokud je dalsi token datovy typ ( boolean jsem tam nedal, kdyztak doplnit jestli budem delat rozsireni (Kappa))
		if (token->type == t_kw_int || token->type == t_kw_string || token->type == t_kw_double || token->type == t_kw_void ){

			// ulozime si typ tokenu
			tempType = token->type;
			tempStatic = 1;

			
			// static dataType - musi nasledovat identifikator
			token = getToken();
			//printToken(token);

			if (token->type != t_simple_ident){
				throwException(2,0,0);
			}

			 // ulozime si identifikator
			 tempData = token->data;
			

			token = getToken();
			//printToken(token); // nacist dalsi token, bud zavorka - funkce, jinak promena

			if (token->type == t_bracket_l) {
				
				if (strcmp(tempData,"run") == 0) { // funkce 'run'
					if (isInMain) {               // a jsme v class Main
						global.hasRun = TRUE;
						isInRun = TRUE;
					} else {
						// semanticka chyba, nemuze byt funkce run jinde nez v class Main
						// tak prej muze, i kdyz se mi to nezda
						//throwException(3,0,0);
					}
					if (tempType != t_kw_void) {
					// navratovy typ run musi byt void
						if (isInMain){
							throwException(3,0,0);
						}
					}
				}
				pFunction();
			} else {
				
				if (tempType == t_kw_void){
					throwException(2,0,0);
				}
				pVar(token, 1);
			}

				pClassBody(); // pokravujeme ve zpracovani zbytku tela tridy

		} else {
			// syntax error za keyword 'static' musi nasledovat datatype
			throwException(2,0,0);
		}
			// end  if (token->type == t_kw_static)
	} /*else if (token->type == t_kw_int || token->type == t_kw_string || token->type == t_kw_double) {
		// data type - promena (neni globalni)

		// ulozime si typ tokenu
		tempType = token->type;                  //Nakonec to neni povolene, 
		tempStatic = 0;
		

		token = getToken();printToken(token);

		//musi nasledovat identifikator
		if (token->type != t_simple_ident){
			throwException(2,0,0);
		}
		// ulozime si identifikator
		tempData = token->data;
		

		pVar(NULL); //volame funkci pro parsovani promene

		pClassBody(); // pokravujeme ve zpracovani zbytku tela tridy

	}*/ else if (token->type == t_brace_r) {
		
		isInMain = FALSE;
		// dalsi token je prava curly zavorka, konec tela  tridy vracime se do funkce pClass(); ( a z ni hned zpatku do funkce pParse();

	} else {
	// token neni ani kw 'static', ani zavorka na konec funkce - syntax error
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
	BTSNode * node;
	node = searchForNode(tempData, function, mTree.actClass); //TODO start??
	
	
	if (node != NULL){
		// pokus o definici funkce se stejnym jmenem //pokud na to neprijdem tak tady echame throwexception
		throwException(3,0,0);                // TADY SE MUSI Nejak vyresit pokus uz ji vytvoril Martin, doplnit data,oddelat exceptin
	} else {
	// ulozit do tab. symbolu
	
	createNewNode(tempData, function, tempToVar(tempType), 1, 1); //TODO INT STATUS
	}

	pParams();  // parse parametru

	pCommands(); // parse tela funkce
	//vystupujeme z funkce
	isInRun = FALSE;

}
void pVar(tToken *token, int dataType){
/**
 * variable assign
 * <type> ID = <expr>;
 * <type> ID;
 * int dataType = 0-> prirazeni ; dataType = 1 -> inicializace(+mozne prirazeni)
 *
 */
	// v temp mame identifikator a typ promene
	// parametr je posledni nacteny token3

	if (token == NULL) {
		token = getToken();
		//printToken(token);
	}

	//musime vytvorit uzel
	// kontrolovat jestli uz neexistuje
	BTSNode * node;
	node = searchForNode(tempData, var, mTree.actFunction);
    createNewNode(tempData, var, tempToVar(tempType), tempStatic, 1);
	/*
	if (dataType == 1) {
		//inicializace promene, uzel nemuze existovat, vytvorime novy
		if (node != NULL){
			throwException(3,0,0);
		}
		createNewNode(tempData, var, tempToVar(tempType), tempStatic, 1);  // TODO status??
		node = searchForNode(tempData, var, NULL);
	} else {
		//prirazeni, uzel musi existovat
		if (node == NULL){
			throwException(3,0,0);
		}
		
	}*/

	

	if (token->type == t_semicolon) { // neprirazujem zadnou hodnotu, konec funkce
		return;
	}

	if (token->type == t_assignment) {
        // DELETE THIS
        tToken *testtoken = initToken(); 
        fillToken(testtoken, t_simple_ident);
        updateToken(testtoken,"VYSL");
        //END DELETE
		expression(node, 0); // TODO  NODE
	
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
	//printToken(token);

  // leva zavorka uz nactena v pClass

  //
  if (token->type == t_kw_int || token->type == t_kw_string || token->type == t_kw_double) {
	  
    if (isInRun == TRUE){
	// run nemuze mit parametry    
    	throwException(6,0,0);
    }	  
    
    tempType = token->type;
    tempStatic = 0;

    //nacist identifikator
    token = getToken();
	  //printToken(token);
    if (token->type != t_simple_ident) {
      throwException(2,0,0);
    }
    tempData = token->data;
    

    // zpracovat parametr TODO
    addArgument(tempData, tempToVar(tempType));		  

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
	//printToken(token);

	if (token->type == t_bracket_r) {
		// uzaviraci zavorka, zadny dalsi parametr
		
	} else if (token->type == t_comma) {
		// carka, nasleduje dalsi parametr
		
		token = getToken();
		//printToken(token);

		if (token->type == t_kw_int || token->type == t_kw_string || token->type == t_kw_double) {
			tempType = token->type;

			

			//nacist identifikator
			token = getToken();
			//printToken(token);
			if (token->type != t_simple_ident) {
				throwException(2,0,0);
			}
			tempData = token->data;
			

			// zpracovat parametr TODO
			addArgument(tempData, tempToVar(tempType));

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
	//printToken(token);

	if (token->type != t_brace_l){   
		throwException(2,0,0);
	}
	

	pSingleCommand(); //parse prikazu

}

void pSingleCommand(){

	tToken * token;
	token = getToken();
	//printToken(token);

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
			//DELETE THIS
			token = getToken();
			//printToken(token);
			while (token->type != t_semicolon) {
				
			token = getToken();
				//printToken(token);
			}
			// END OF DELETE BLOCK
			break;

		case t_simple_ident :
		case t_complete_ident :
			//  identifikator,
			// prirazeni hodnoty promene, volam funkci,
			tempData = token->data;
			
			token = getToken();
			//printToken(token);

			if (token->type == t_assignment) {
				// a =
				pVar(token,0);
				
			} else if (token->type == t_bracket_l) {
				// volani funkce
				//vytvorit uzel nebo najit
				BTSNode * node;
				node = searchForNode(tempData, function, mTree.actClass); //TODO start??
                if (node == NULL){
                    throwException(3,0,0);
                }
				
				//mozna tady musim vytvorit NODE pokud neexistuje
				
				functionCall(NULL,node);
				
				token=getToken();
				if (token->type != t_semicolon){
					throwException(2,0,0);
				}
				

				// sem pridat check na strednik pokud to bude potreba
			}
			else {
				// ident musi nasledovat prirazeni nebo volani fce
				throwException(2,0,0);
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
			//printToken(token);
			if (token->type != t_simple_ident) {
				throwException(2,0,0);
			}

			tempData = token->data;
			

			pVar(NULL,1);

		break;


		default:
			// neocekavany vstup
			throwException(2,0,0);

	} //end switch

	// rekurzivni volani na dalsi prikaz
	pSingleCommand();
}



void pIf(){
/***
 * if ( <expr> ) <commands> else <commands>
 */

	tToken * token;
    getToken();

	//vytvorit instrukce pro condition, if
	expression(NULL, 0); //TODO

	pCommands();

	token = getToken();printToken(token);
	if (token->type != t_kw_else){   // else
		throwException(2,0,0);
	}
	// instrukce endif , else 

	// block of code for else
	pCommands();
	
	//instrukce endcond

}
void pWhile(){
/**
* while ( <expr> ) { <commands> }
*/

	// instrukce while
	expression(NULL, 0); //TODO
	


	pCommands();
	// instrukce endwhile
}

varType tempToVar(tokenType temp) {
	varType type = var_null;
	switch (temp) {
		case t_kw_int:
			type = var_int;
			break;
		case t_kw_double:
			type = var_double;
			break;
		case t_kw_string:
			type = var_string;
			break;
		case t_kw_void:
			type = var_void;
			break;
		default:
			// pro jistotu
			throwException(99, 0, 0);
			break;
	}

	if (type == var_null) {
		throwException(99, 0, 0);
	}
	return type;
}


