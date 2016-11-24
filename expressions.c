/**
 * IFJ/IAL - Precedenční analýza
 * Varianta:    b/2/I
 * Soubor:      expressions.c
 * Tým:         59
 * Autoři:      Jan Hrbotický, xhrbot01@stud.fit.vutbr.cz
 *              Dominik Skála, xskala11@stud.fit.vutbr.cz
 *              Milan Hruban, xhruba08@stud.fit.vutbr.cz
 *              Martin Hons, xhonsm00@stud.fit.vutbr.cz
 *              David Hél, xhelda00@stud.fit.vutbr.cz
 */

#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "garbage_collector.h"
#include "expressions.h"
#include "error_handler.h"
#include "stack.h"
#include "iStack.h"
#include "lexical_analyzer.h"

#define STR_ERROR   0
#define STR_SUCCESS 1
#define STR_ALLOCATION_SIZE 8  // Udává, kolik bude alokováno na začátku paměti. Pokud načítáme po jednom znaku, dojde k alokaci na násobky tohoto čísla

char precTable[16][16] = {
  //  (   )   /   *   +   -   ==  !=  <   >   <=  >=  !   ,   ;   ID
    {'<','=','<','<','<','<','<','<','<','<','<','<','<',' ','F','<'} // (
    {'F','>','>','>','>','>','>','>','>','>','>','>','>',' ','>','F'} // )
    {'<','>','>','>','>','>','>','>','>','>','>','>','>',' ',' ','<'} // /
    {'<','>','>','>','>','>','>','>','>','>','>','>','>',' ','>','<'} // *
    {'<','>','<','<','>','>','>','>','>','>','>','>','>',' ','>','<'} // +
    {'<','>','<','<','>','>','>','>','>','>','>','>','>',' ',' ','<'} // -
    {'<','>','<','<','<','<','>','>','>','>','>','>','>',' ',' ','<'} // ==
    {'<','>','<','<','<','<','>','>','>','>','>','>','>',' ',' ','<'} // !=
    {'<','>','<','<','<','<','>','>','>','>','>','>','>',' ',' ','<'} // <
    {'<','>','<','<','<','<','>','>','>','>','>','>','>',' ',' ','<'} // >
    {'<','>','<','<','<','<','>','>','>','>','>','>','>',' ',' ','<'} // <=
    {'<','>','<','<','<','<','>','>','>','>','>','>','>',' ',' ','<'} // >=
    {'=','>','>','>','>','>','>','>','>','>','>','>','>',' ',' ','<'} // !
    {'<','=',' ','<','<',' ',' ',' ',' ',' ',' ',' ',' ','=','F','<'} // ,
    {'<','F',' ','<','<',' ',' ',' ',' ',' ',' ',' ',' ',' ','F','<'} // ;
    {'F','>','>','>','>','>','>','>','>','>','>','>','F',' ','>','F'} // ID
};

int argNum = 0;

bool isIdent(tToken *token) {
    if ((token->type >= t_simple_ident) && (token->type <= t_print))
        return true;
    return false;
}

bool isConst(tToken *token) {
    if ((token->type >= t_int) && (token->type <= t_string))
        return true;
    return false;    
}

varType variableType(tToken *token) {
    return var; // TODO
}

char getPrecChar(tToken *stackToken, tToken *inToken) {
    int stackTokenNum = stackToken->type;
    int inTokenNum = inToken->type;
    
    if (isIdent(stackToken) || isConst(stackToken)) {
        stackTokenNum = 15;
    }
    if (isIdent(inToken) || isConst(inToken)) {
        inTokenNum = 15;
    }
    return precTable[stackTokenNum][inTokenNum];
}

// Mění terminály na výrazy a odstraňuje závorky podle pravidel: E -> id  a  E -> (E)
tStackIt **chnToExp(tStack *stack, tStackIt *handle[]) {
    int i = 0;

    // Čteme ze zásobníku dokud nenarazíme na NONTERM
    while (stackTop(stack)->typeIt != NONTERM) {
        i++;
        // Pokud je handle větší než 3, vyvoláme syntaktickou chybu
        if (i > 3) throwException(2,0,0);
        handle[i] = stackTop(stack);
        stackPop(stack);
    }

    // Odstraníme ze zásobníku začátek handle '<'
    stackPop(stack);

    // Pravidlo E -> id
    if ((i == 1) && (isIdent(handle[0]->dataIt))) {
        handle[0]->typeIt = EXPR;
        stackPush(stack,handle[0]);
    }
    // Pravidlo E -> (E)
    else if ((i == 3) && (handle[0]->dataIt->type == t_bracket_r) && (isIdent(handle[1]->dataIt)) && (handle[2]->dataIt->type == t_bracket_l)) {
        stackPush(stack,handle[1]);
    }

    return handle;
}

// Vyhledává pravidla pro aritmetické a porovnávací instrukce
void reduceExp(char *targetId, tStackIt *handle[3]) {
    Instr *instr = instrItemInit(instr);

    // Najde identifikátor cílové proměnné
    instr->Id3 = searchForNode(targetId,var,ptrAktTridy);  // TODO
    if (instr->Id3->NodeType == function) {
        instr->Id3->variables[argNum];
        argNum++;
    }

    // Pokud se jedná se o aritmetickou nebo porovnávací instrukci
    if ((handle[0]->typeIt == EXPR) && (handle[2]->typeIt == EXPR)) {

        instr->Id1 = searchForNode(handle[2],var,ptrAktFunkceNeboTridy);
        instr->Id2 = searchForNode(handle[0],var,ptrAktFunkceNeboTridy);

        switch (handle[1]->dataIt->type) {
            case t_plus: // E -> E+E
                instr->type = insPlus;
                if (instr->Id3)
                instrStackPush(iStack,instr); // TODO iStack nahradit skutečným názvem instručního stacku
                break;
            case t_minus: // E -> E-E
                instr->type = insMinus;
                instrStackPush(iStack,instr);
                break;
            case t_multi: // E -> E*E
                instr->type = insMux;
                instrStackPush(iStack,instr);
                break;
            case t_div: // E -> E/E
                instr->type = insDiv;
                instrStackPush(iStack,instr);
                break;
            case t_comparasion: // E -> E==E
                instr->type = insEqual;
                instrStackPush(iStack,instr);
                break;
            case t_comparasion_ne: // E -> E!=E
                instr->type = insNotEqual;
                instrStackPush(iStack,instr);
                break;
            case t_less: // E -> E<E
                instr->type = insLess;
                instrStackPush(iStack,instr);
                break;
            case t_less_eq: // E -> E<=E
                instr->type = insLessOrEqual;
                instrStackPush(iStack,instr);
                break;
            case t_greater: // E -> E>E
                instr->type = insGreater;
                instrStackPush(iStack,instr);
                break;
            case t_greater_eq: // E -> E>=E
                instr->type = insGreaterOrEqual;
                instrStackPush(iStack,instr);
                break;
            default: // Syntaktická chyba
                throwException(2,0,0);
                break;
        }
    }
    // Pokud se jedná o jednoduché přiřazení
    else if (handle[0]->typeIt == EXPR) {
        instr->type = insAssignment;
        instr->Id1 = searchForNode(handle[0],var,ptrAktFunkceNeboTridy);
        instrStackPush(iStack,instr);
    }
    else {
        throwException(2,0,0);
    }
}

void expression(char *targetId, tExpType expType) {
    // Inicializujeme zásobník a vložíme na něj znak ';'
    tStack *stack = NULL;
    stack = stackInit(stack);

    tToken *token = initToken();
    fillToken(token, t_semicolon);

    tStackIt *item = itemInit();
    item->dataIt = token;
    item->typeIt = TERM;
    stackPush(stack,item);

    token = getToken();

    // TODO - obsluha vestavěných funkcí
    Instr *instr = instrItemInit();
    instr->Id3 = searchForNode(targetId,var,ptrAktTridy);


    switch (targetId) {
        case "ifj16.readInt":

            break;
        case "ifj16.readDouble":
            break;
        case "ifj16.readString":
            break;
        case "ifj16.length":
            break;
        case "ifj16.substr":
            break;
        case "ifj16.compare":
            break;
        case "ifj16.find":
            break;
        case "ifj16.sort":
            break;
    }*/

    while (TRUE) {
        /* Vyskočí z cyklu, pokud topTerm je roven ';' a
         *   jedná se o podmínku a na vstupu je ')'
         *   nebo se jedná o argument a na vstupu je ',' nebo ')'
         *   nebo se jedná o přiřazení a na vstupu je ';'
         *   (v posledním případě před vyskočením ještě vygeneruje instrukci)
         */
        if (topTerm(stack)->type == t_semicolon) {
            if ((expType == expCond) && (token->type == t_bracket_r)) {
                break;
            }
            else if (expType == expArg) {

                if (token->type == t_comma) {
                    expression(targetId, expArg);
                    break;
                }
                else if (token->type == t_bracket_r) {
                    argNum = 0;
                    break;
                }
            }
            else if ((expType == expAssign) && (token->type == t_semicolon)) {
                break;
            }
        }

        // Jedná se o funkci uvnitř výrazu
        else if (isIdent(topTerm()) && token->type == t_bracket_l) {
            token = getToken();
            tokenCounter++;
            expression(topTerm()->data,expArg);
        }
        // Syntaktická chyba
        else if (token->type <= t_string) {
            throwException(2,0,0);
        }


        switch (getPrecChar(topTerm(),token)) {
            case '<': ; // Tento středník tu musí být jinak to řve error :-)
                // Vloží znak '<' na zásobník
                tToken *lessToken = initToken();
                fillToken(lessToken, t_less);
                item = itemInit();
                item->dataIt = lessToken;
                item->typeIt = NONTERM;
                stackPush(stack,item);

                // Vloží aktuální token na zásobník
                item = itemInit();
                item->dataIt = token;
                item->typeIt = TERM;
                stackPush(stack,item);

                //Načte nový token
                token = getToken();
                tokenCounter++;
                break;
            case '=':
                // Vloží aktuální token na zásobník
                item = itemInit();
                item->dataIt = token;
                item->typeIt = TERM;
                stackPush(stack,item);

                //Načte nový token
                token = getToken();
                tokenCounter++;
                break;
            case '>': ; // Stejná situace se středníkem jako v první case
                tStackIt *handle[3];
                chnToExp(stack,handle);
                reduceExp(targetId,handle);
                break;
            default:
                // Syntaktická chyba
                throwException(2,0,0);
                break;
        }
    }
    stackDestroy(stack);
}

String substr(String str, int i, int n) {

	String realString = '\0';
	int j = 0;

    while (i <= (i + n)) {
		if (str[i] == EOF || isspace(str[i])) {
			throwException(10, GlobalRow, GlobalColumn);
		}
        realString[j] = str[i];
		j++;
        i++;
    }
	return realString;
}

/* asi nepotrebne
int addCharacter(String *str, char c){
  
    if ((str->allocatedSize) <= (str->length + 1)) {
		if (plusRealloc(str, sizeof(String) + (sizeof(char)*(str->allocatedSize))) != NULL) {
			str->allocatedSize = str->length + STR_ALLOCATION_SIZE;
		} else {
			throwException(99,0,0); //chyba alokace paměti
			return STR_ERROR;
		}
	str->data[str->length] = c;
	str->length++;
	str->data[str->length] = '\0';

	return STR_SUCCESS;
	} else {
		return 0;
	}
}*/

void copyString(String str1, String str2) {
	int i = 0;
	while (str1[i] != '\0' || str1[i] != EOF) {
		str2[i] = str1[i];
		i++;
	}
}

int compareString(String str1, String str2) {
   //porovná dva zadané řetězce str1 a str2 a vrátí celočíselnou hodnotu dle toho, zda je str1 před, roven, nebo za str2
	int result = strcmp(str1, str2);
	if (result < 0) {
		result = -1;
	} else if (result > 0) {
		result = 1;
	}

	return result;

}

int strLength(String str) {
	//vrátí délku řetězce (počet znaků) zadaného jedním parametrem str
	int length = 0;

	while (str[length] != '\0' || str[length] != EOF) {
		length++;
	}
	return length;
}

int strEqual(String str1, String str2) {
	int equal = !strcmp(str1, str2);
	return equal;
}

void strClear(String str) {
	// funkce sloužící k vymazání řetězce
	int length = strLength(str);
	while (length != 0) {
		str[length] = '\0';
		length--;
	}
}


String readString(){
	int c = getchar();
	String str = '\0';
	int i = 0;


	while (c != EOF || c != '\n') {
		str[i] = (char)c;
		i++;
		c = getchar();
	}
	return str;
}

void print(String string) {
	// nejaka podminka kvuli typu vstupu..
	printf("%s", string);

}


int readInt() {
	String str = readString();
	int number = 0;
	int i = 0;

	int length = strLength(str);

	while (str[i] != '\0') {
		if (!isdigit(str[i])) {
			throwException(7, GlobalRow, GlobalColumn);
		}
		number += (str[i]-48) * (int)pow(10,length-i-1);
		i++;
	}
	return number;
}

double readDouble(){
	String str = readString();
	char *end;
	double doubleNumber = strtod(str, &end);

	if (*end != '\0' || doubleNumber < 0) {
		throwException(7, GlobalRow, GlobalColumn);
	}

	return doubleNumber;
}

