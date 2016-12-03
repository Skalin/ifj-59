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
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "garbage_collector.h"
#include "expressions.h"
#include "error_handler.h"
#include "stack.h"
#include "ial.h"
#include "instrstack.h"
#include "lexical_analyzer.h"

#define STR_ERROR   0
#define STR_SUCCESS 1
#define STR_ALLOCATION_SIZE 8  // Udává, kolik bude alokováno na začátku paměti. Pokud načítáme po jednom znaku, dojde k alokaci na násobky tohoto čísla

// TODO zkontrolovat správnost tabulky
char precTable[15][15] = {
  //  (   )   /   *   +   -   ==  !=  <   >   <=  >=  !   ;   ID
    {'<','=','<','<','<','<','<','<','<','<','<','<','<','F','<'}, // (
    {'F','>','>','>','>','>','>','>','>','>','>','>','>','>','F'}, // )
    {'<','>','>','>','>','>','>','>','>','>','>','>','>','>','<'}, // /
    {'<','>','>','>','>','>','>','>','>','>','>','>','>','>','<'}, // *
    {'<','>','<','<','>','>','>','>','>','>','>','>','>','>','<'}, // +
    {'<','>','<','<','>','>','>','>','>','>','>','>','>','>','<'}, // -
    {'<','>','<','<','<','<','>','>','>','>','>','>','>','>','<'}, // ==
    {'<','>','<','<','<','<','>','>','>','>','>','>','>','>','<'}, // !=
    {'<','>','<','<','<','<','>','>','>','>','>','>','>','>','<'}, // <
    {'<','>','<','<','<','<','>','>','>','>','>','>','>','>','<'}, // >
    {'<','>','<','<','<','<','>','>','>','>','>','>','>','>','<'}, // <=
    {'<','>','<','<','<','<','>','>','>','>','>','>','>','>','<'}, // >=
    {'=','>','>','>','>','>','>','>','>','>','>','>','>','F','<'}, // !
    {'<','F','<','<','<','<','<','<','<','<','<','<','F','F','<'}, // ;
    {'F','>','>','>','>','>','>','>','>','>','>','>','F','>','F'}  // ID
};

int argNum = 0;

bool isIdent(tToken *token) {
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
    
    if (isIdent(stackToken) || isConst(stackToken)) {
        stackTokenNum = 14;
    }
    if (isIdent(inToken) || isConst(inToken)) {
        inTokenNum = 14;
    }
    printf("posilam [%d][%d]\n",stackTokenNum,inTokenNum);
    return precTable[stackTokenNum][inTokenNum];
}


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
void reduceExp(BTSNode *targetId, tStackIt *handle[3], instrStack *iStack) {
    Instr *instr = NULL;
    instr = instrItemInit();
    BTSNode *start = NULL; // TODO global.mTree->actFunction;
    
    if (start != NULL) {
       // TODO start = global.mTree->actClass;
    }

    // Jedná se o argument ne/definované funkce
    if (instr->Id3 == NULL) {       
        // Vytvořím nový uzel typu param s klíčem targetId + argNum
        argNum++;
    }

    // Pokud se jedná se o aritmetickou nebo porovnávací instrukci
    if ((handle[0]->typeIt == EXPR) && (handle[2]->typeIt == EXPR)) {

        instr->Id1 = searchForNode(handle[2]->dataIt->data,var,start);
        instr->Id2 = searchForNode(handle[0]->dataIt->data,var,start);

        switch (handle[1]->dataIt->type) {
            case t_plus: // E -> E+E
                instr->type = insPlus;
                if (instr->Id3)
                instrStackPush(iStack,instr);
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
        instr->Id1 = searchForNode(handle[0]->dataIt->data,var,start);
        instrStackPush(iStack,instr);
    }
    else {
        throwException(2,0,0);
    }
}

void expression(BTSNode *targetId, tExpType expType) {
    // Otestováno: isIdent, isConst, getPrecChar, topTerm
/*
    // DELETE - testování interních funkcí v expressions (aktualne chnToExp)  
    tStack *teststack = NULL;
    teststack = stackInit(teststack);
    tToken *testtoken = NULL;
    tStackIt *testitem = NULL;
    
    testtoken = initToken();
    fillToken(testtoken, t_semicolon);
    updateToken(testtoken,";");
    testitem = itemInit();
    testitem->dataIt = testtoken;
    testitem->typeIt = TERM;
    stackPush(teststack,testitem);
    
    testtoken = initToken();
    fillToken(testtoken, t_int);
    updateToken(testtoken,"<");
    testitem = itemInit();
    testitem->dataIt = testtoken;
    testitem->typeIt = NONTERM;
    stackPush(teststack,testitem);
    
    testtoken = initToken();
    fillToken(testtoken, t_int);
    updateToken(testtoken,"ID");
    testitem = itemInit();
    testitem->dataIt = testtoken;
    testitem->typeIt = TERM;
    stackPush(teststack,testitem);
       
    int j = 1;
    while (j <= 1) {
        printf("%2d. krok--------------\n",j);
        printf("   Obsah stacku: ");
        
        int i = 0;
        while (teststack->counter-i > 0) {
            printf("|%s",teststack->data[teststack->counter-i]->dataIt->data);
            i++;
        }
        printf("|\n");

        tStackIt *testhandle[3];
        chnToExp(teststack,testhandle);
        j++;
    }
   
    
    printf("\n\nTESTY PROSLY!!\n");
    printf("topterm=%s\n",topTerm(teststack)->data);
    
    // END DELETE*/
    
    
    
    /* Pokud jsme mimo funkci nebo jsme ve funkci run, ukládáme instrukce na globální instrukční stack. 
     * V opačném případě na instruční stack aktuální funkce */ 
    instrStack *localIStack = global.iStack;
    if ((global.mTree->actFunction != NULL) || (strcmp(global.mTree->actFunction->key, "run") != 0)) {
		instrStackCopy(localIStack, global.mTree->actFunction->iStack); // Zatím neexistuje ale bude
    }
    
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
    Instr *instr = NULL;
    instr = instrItemInit(instr);
       
    
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
                // Zpracování dalšího argumentu
                if (token->type == t_comma) {
                    expression(targetId, expArg);
                }
                else if (token->type == t_bracket_r) {
                    if (argNum == 0) {
                        // Funkce bez parametrů. Může a nemusí být void
                    }
                    argNum = 0;
                    break;
                }
            }
            else if ((expType == expAssign) && (token->type == t_semicolon)) {
                break;
            }
        }      
        // Jedná se o funkci uvnitř výrazu
        if (isIdent(topTerm(stack)) && token->type == t_bracket_l) {            
            /* Vytvořím instrukci, kde: 
             *   - id3 je proměnná v aktuální funkci
             *   - id1 je řetězec s id volané funkce
             *   - id2 je pole argumentů
             *   - type je insFunctionCall
             */
            instr->Id3 = targetId; 
            /* TODO tady budu muset najít uzel s klíčem nejvyššího terminálu, pokud neexistuje tak ho vytvořit a pointer na něj dát do id2
            instr->Id1 = searchForNode(topTerm(stack)->data,function,start);
            if (instr->Id1 == NULL) {
                instr->Id1 = Nově vytvořený uzel
            }
            */
            instr->type = insFunctionCall;
            
            /* TODO Vytvořit uzel, nahrát do něj všechny argumenty
             * instrukci vložit do stacku a pokračovat dál ve zpracovávání výrazu.
             * Pokud uzel nemá argumenty zrušit ho, do id2 dát NULL (funcCnt by se v tomho případě asi nemusela inkrementovat)
             * a pokračovat ve zpravocání výrazu
                instr->Id2 = createNewNode(funcCnt); 
                expression(funcCnt, expArg);
                instrStackPush(iStack,instr);*/
        }
        // Jedná se o void funkci
        else if (expType == expVoid) {
            instr->Id3 = NULL;
            instr->Id1 = targetId;
            instr->type = insFunctionCall;
            
            /* TODO Vytvořit uzel, nahrát do něj všechny argumenty
             * instrukci vložit do stacku a pokračovat dál ve zpracovávání výrazu.
             * Pokud uzel nemá argumenty zrušit ho, do id2 dát NULL (funcCnt by se v tomho případě asi nemusela inkrementovat)
             * ale už nepokračovat ve zpravocání výrazu
                instr->Id2 = createNewNode(funcCnt); 
                expression(funcCnt, expArg);
                instrStackPush(iStack,instr);*/
            break;
        }
        // Syntaktická chyba
        else if (token->type <= t_string) {
            throwException(2,0,0);
        }


        switch (getPrecChar(topTerm(stack),token)) {
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
                reduceExp(targetId,handle,localIStack);
                break;
            default:
                // Syntaktická chyba
                throwException(2,0,0);
                break;
        }
    }
    stackDestroy(stack);
}

void completeInstr() {
    /* Funkce je zavolána na konci syntaktické analýzy
     * Prochází iStack a mění instrukci insFunctionCall na posloupnost aritmetických instrukcí
     * Zjistí, zda se jedná o vestavěnou funkci
     * Pokud ne zkontroluje počet parametrů
     * Na svém konci volá interpret (asi)  
     */    
    
    /*
    while (není konec istacku) {
        if (najde instrukci insFunctionCall) {
        
        
            //Detekce vestavěných funkcí
            switch () {
                case "ifj16.readInt":
                    expression();
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
            }
            
        }
    }*/
}

String substr(String str, int i, int n) {

	String realString = '\0';
	int j = 0;

    while (i <= (i + n)) {
		if (str[i] == EOF || isspace(str[i])) {
			throwException(10, 0, 0);
		}
        realString[j] = str[i];
		j++;
        i++;
    }
	return realString;
}

void copyString(String str1, String str2) {
	int i = 0;
	while (str1[i] != '\0' || str1[i] != EOF || str2[i] != EOF) {
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
			throwException(7, 0, 0);
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
		throwException(7, 0, 0);
	}

	return doubleNumber;
}

