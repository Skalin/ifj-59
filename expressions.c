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
#include "typedef.h"
#include "garbage_collector.h"
#include "lexical_analyzer.h"
#include "expressions.h"
#include "error_handler.h"
#include "stack.h"
#include "iStack.h"

#define STR_ERROR   0
#define STR_SUCCESS 1
#define STR_ALLOCATION_SIZE 8  // Udává, kolik bude alokováno na začátku paměti. Pokud načítáme po jednom znaku, dojde k alokaci na násobky tohoto čísla

char precTable[16][16] = {
//    +    -    *    /    (    )    ID   <    >    <=   >=   ==  !=    !
//    (    )    /    *    +    -    ==   !=   <    >    <=   >=   !    ,    ;    ID      
    {'<', '<', '<', '<', '<', '=', '<', '<', '<', '<', '<', '<', '<', '<', ' ', ' '}, // (
    {'>', '>', '>', '>', 'F', '>', 'F', '>', '>', '>', '>', '>', '>', '>', ' ', ' '}, // )
    {'>', '>', '>', '>', '<', '>', '<', '>', '>', '>', '>', '>', '>', '>', ' ', ' '}, // /
    {'>', '>', '>', '>', '<', '>', '<', '>', '>', '>', '>', '>', '>', '>', ' ', ' '}, // *
    {'>', '>', '<', '<', '<', '>', '<', '>', '>', '>', '>', '>', '>', '>', ' ', ' '}, // +
    {'>', '>', '<', '<', '<', '>', '<', '>', '>', '>', '>', '>', '>', '>', ' ', ' '}, // -
    {'<', '<', '<', '<', '<', '>', '<', '>', '>', '>', '>', '>', '>', '>', ' ', ' '}, // ==
    {'<', '<', '<', '<', '<', '>', '<', '>', '>', '>', '>', '>', '>', '>', ' ', ' '}, // !=
    {'<', '<', '<', '<', '<', '>', '<', '>', '>', '>', '>', '>', '>', '>', ' ', ' '}, // <
    {'<', '<', '<', '<', '<', '>', '<', '>', '>', '>', '>', '>', '>', '>', ' ', ' '}, // >
    {'<', '<', '<', '<', '<', '>', '<', '>', '>', '>', '>', '>', '>', '>', ' ', ' '}, // <=
    {'<', '<', '<', '<', '<', '>', '<', '>', '>', '>', '>', '>', '>', '>', ' ', ' '}, // >=
    {'>', '>', '>', '>', '=', '>', '<', '>', '>', '>', '>', '>', '>', '>', ' ', ' '},  // !
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},  // ,
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},  // ;
    {'>', '>', '>', '>', 'F', '>', 'F', '>', '>', '>', '>', '>', '>', 'F', ' ', ' '}, // ID
};




bool isId(tToken *token) {
    if ((token->type >= t_simple_ident) && (token->type <= t_complete_ident))
        return true;
    return false;
}

bool isConst(tToken *token) {
    if ((token->type >= t_int) && (token->type <= t_string))
        return true;
    return false;    
}


char getPrecChar(tToken *stackToken, tToken *inToken) {
    int stackTokenNum = stackToken->type;
    int inTokenNum = inToken->type;
    
    if (isId(stackToken) || isConst(stackToken)) {
        stackTokenNum = 15;
    }
    if (isId(inToken) || isConst(inToken)) {
        inTokenNum = 15;
    }
    return precTable[stackTokenNum][inTokenNum];
}

// Načte handle a najde pravidla E -> i a E -> (E)
void chnToExp(tStack *stack, tStackIt *handle[]) {
    int i = 0;
    //tStackIt *handle[3];

    // Čteme ze zásobníku dokud nenarazíme na NONTERM
    while (topItemType() != NONTERM) {
        i++;
        // Pokud je handle větší než 3, vyvoláme syntaktickou chybu
        if (i > 3) throwException(2,0,0);
        handle[i] = stackTop(stack);
        stackPop(stack);
    }

    // Odstraníme ze zásobníku začátek handle '<'
    stackPop(stack);

    // Pravidlo E -> id
    if ((i == 1) && (handle[0]->typeIt == TERM) && (handle[0]->dataIt->type >= t_simple_ident) && (handle[0]->typeIt <= t_string)) {
        handle[0]->typeIt = EXPR;

        /*TOMUHLE NEROZUMÍM ALE MOŽNÁ TO TU MÁ BÝT (zřejmě je to uložení identifikátoru)
        copyString(&item->dataIt->attribute,&handle[0]->dataIt->attribute); */
    }
    // Pravidlo E -> (E)
    else if ((i == 3) && (handle[0]->dataIt->type == t_bracket_l) && (handle[1]->dataIt->type >= t_simple_ident) && (handle[1]->typeIt <= t_string) && (handle[2]->dataIt->type == t_bracket_r)) {
        handle[0]->typeIt = EXPR;
    }
    /* TOMUHLE TAKY NEROZUMÍM ALE MOŽNÁ TO TU MǍ BÝT
    else {
        addCharacter(&item->dataIt->attribute, 'E');
    }*/

    stackPush(stack,handle[0]);
    return handle;
}

void reduceExp(tStackIt *handle[3]) {
    Instr *instr = instrItemInit();

    // Jedná se o aritmetickou nebo porovnávací instrukci
    if ((handle[0]->typeIt == EXPR) && (handle[2]->typeIt == EXPR)) {
        switch (handle[1]->dataIt->type) {
            case t_plus: // E -> E+E
                instr->type = insPlus;
                break;
            case t_minus: // E -> E-E
                instr->type = insMinus;
                break;
            case t_multi: // E -> E*E
                instr->type = insMux;
                break;
            case t_div: // E -> E/E
                instr->type = insDiv;
                break;
            case t_comparasion: // E -> E==E
                instr->type = insEqual;
                break;
            case t_comparasion_ne: // E -> E!=E
                instr->type = insNotEqual;
                break;
            case t_less: // E -> E<E
                instr->type = insLess;
                break;
            case t_less_eq: // E -> E<=E
                instr->type = insLessOrEqual;
                break;
            case t_greater: // E -> E>E
                instr->type = insGreater;
                break;
            case t_greater_eq: // E -> E>=E
                instr->type = insGreaterOrEqual;
                break;
            default: // Syntaktická chyba
                throwException(2,0,0);
                break;
        }
    }
    // E -> (E)
/*    else if () {

    }*/
    // Syntaktická chyba
    else {
        throwException(2,0,0);
    }
    // instrStackPush(iStack,instr);
}


void expression(tExpType expType, char *funcName) {
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
    while (1) {
        /* Vyskočí z cyklu, pokud topTerm je roven ';' a
         *   jedná se o podmínku a na vstupu je ')'
         *   nebo se jedná o argument a na vstupu je ',' nebo ')'
         *   nebo se jedná o přiřazení a na vstupu je ';'
         *   (v posledním případě před vyskočením ještě vygeneruje instrukci)
         */
        if (topTerm()->type == t_semicolon) {
            if (((expType == expCond) && (token->type == t_bracket_r)) ||
                ((expType == expArg) && ((token->type == t_comma) || (token->type == t_bracket_r))) ||
                ((expType == expAssign) && (token->type == t_semicolon)))
                break;
        }

        switch (getPrecChar(topTerm(),token)) { // TODO
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
                break;
            case '=':
                // Vloží aktuální token na zásobník
                item = itemInit();
                item->dataIt = token;
                item->typeIt = TERM;
                stackPush(stack,item);

                //Načte nový token
                token = getToken();
                break;
            case '>': ; // Stejná situace se středníkem jako v první case
                tStackIt *handle[3];
                chnToExp(stack,handle);
                reduceExp(handle);
                break;
            default:
                // Syntaktická chyba
                throwException(2,0,0);
                break;
        }
    }
    // TODO uvolnit paměť
}

SString substr(SString *str, int i, int n) {

	SString helpStr;
    initString(&helpStr);

    while (i <= (i + n)) {
		if (str->data[i] == EOF || isspace(str->data[i])) {
			throwException(10, GlobalRow, GlobalColumn);
		}
        addCharacter(&helpStr, str->data[i]);
        i++;
    }

	return helpStr;
}

void initString(SString *str){

	if ((plusMalloc(sizeof(SString) + sizeof(char)*STR_ALLOCATION_SIZE)) != NULL) {
		str->data[0] = '\0';
		str->length = 0;
		str->allocatedSize = STR_ALLOCATION_SIZE;
	} else {
		throwException(99,0,0); //chyba alokace paměti
	}


}

int addCharacter(SString *str, char c){
  
    if ((str->allocatedSize) <= (str->length + 1)) {
		if (plusRealloc(str, sizeof(SString) + (sizeof(char)*(str->allocatedSize))) != NULL) {
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
}

void copyString(SString *str1, SString *str2) {

	if (str2->allocatedSize < strLength(str1)) {
		if (plusRealloc(str2, sizeof(SString) + (sizeof(char)*(str2->allocatedSize))) != NULL) {
			str2->allocatedSize = str2->length + STR_ALLOCATION_SIZE;
		} else {
			throwException(99,0,0); //chyba alokace paměti
		}
	}
	strClear(str2);
	str2->length = str1->length;
	str2->data = str1->data;
}

int compareString(SString *str1, SString *str2) {
   //porovná dva zadané řetězce str1 a str2 a vrátí celočíselnou hodnotu dle toho, zda je str1 před, roven, nebo za str2
   int result = strcmp(str1->data, str2->data);
   if (result == 0) {
      return result;
   } else if (result < 0) {
      return (result = -1);
   } else {
      return (result = 1);
   }
    
}

int strLength(SString *str) {
	//vrátí délku řetězce (počet znaků) zadaného jedním parametrem str
	int len = str->length;
	return len;
}

int strEqual(char *str1, char *str2) {
	int equal = !strcmp(str1, str2);
	return equal;
}

void strClear(SString *str) {
	// funkce sloužící k vymazání řetězce
	str->length = 0;
	str->data[0] = '\0';
}

void destroyString (SString *str) {
	// funkce k uvolnění z paměti
	if (str != NULL) {
		plusFree(str->data);
	}
}



SString readString(){
	int c = getchar();
	SString str;
	initString(&str);
	int i = 0;


	while (c != EOF || c != '\n') {
		addCharacter(&str, (char) c);
		i++;
		c = getchar();
	}
	addCharacter(&str, '\0');
	return str;
}

void print(char *string) {
	// nejaka podminka kvuli typu vstupu..
	printf("%s", string);

}


int readInt() {
	SString str;
	initString(&str);
	str = readString();
	int number = 0;
	int i = 0;

	int length = str.length;

	while (str.data[i] != '\0') {
		if (!isdigit(str.data[i])) {
			throwException(7, GlobalRow, GlobalColumn);
		}
		number += (str.data[i]-48) * (int)pow(10,length-i-1);
		i++;
	}
	destroyString(&str);
	return number;
}

double readDouble(){
	SString str;
	initString(&str);
	str = readString();
	char *end;
	double doubleNumber = strtod(str.data, &end);

	if (*end != '\0' || doubleNumber < 0) {
		throwException(7, GlobalRow, GlobalColumn);
	}

	destroyString(&str);

	return doubleNumber;
}

