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

#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "expressions.h"
#include "error_handler.h"
#include "lexical_analyzer.h"
#include "ial.h"

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

mainTree mTree;
int tempNodeCounter = 0;
int constCounter = 0;

//DELETE THIS
void stackPrint(tStack *stack) {
    for (int i = 1; i <= stack->counter; i++) {
       // printf( "  Stack: pozice=%d obsah=%c type=%d\n", i, stack->data[i]->dataIt->data[0],stack->data[i]->typeIt );
    }
    //printf("  Stack counter=%d\n",stack->counter);
}

char* nodePrint(BTSNode *node) {
    if (node == NULL)
        return "NULL";

    return node->key;
}
//END DELETE

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
    //DELETE THIS
   // printf("getPrecChar: [%2d][%2d] \'%c\'  vstupní token:|%s|\n",stackTokenNum,inTokenNum,precTable[stackTokenNum][inTokenNum],inToken->data);
    //END DELETE
    return precTable[stackTokenNum][inTokenNum];
}


tStackIt **chnToExp(tStack *stack, tStackIt *handle[3]) {
    //DELETE THIS
        stackPrint(stack);
    //END DELETE
    int i = 0;
    tStackIt *item = NULL;
    // Čteme ze zásobníku dokud nenarazíme na NONTERM
    while ((item = stackTop(stack))->typeIt != NONTERM) {
        i++;
        // Pokud je handle větší než 3, vyvoláme syntaktickou chybu
        if (i > 3) throwException(2,0,0);
        handle[i-1] = item;
     //   printf("  Handle[%d]=%c  ",i-1,handle[i-1]->dataIt->data[0]);
        stackPop(stack);
    }
    printf("\n");
    // Odstraníme ze zásobníku začátek handle '<'
    stackPop(stack);

    // Pravidlo E -> id
    if ((i == 1) && (handle[0]->typeIt == TERM) && ((isIdent(handle[0]->dataIt)) || (isConst(handle[0]->dataIt)))) {
        if (isConst(handle[0]->dataIt)) {
            //TODO vytvořit nový node a jeho název vložit do handle[0]
            // createNewNode("const" + constCounter,tempVar,var_int,0,1); - typ konstanty je v tokenu 
            
            // DELETE THIS
            tToken *token = initToken();
            updateToken(token,"MNOPQ"+constCounter); 
            tStackIt *item = itemInit(token);
            item->typeIt = EXPR;
            handle[0] = item;
            //END DELETE
            constCounter++;
        }
        handle[0]->typeIt = EXPR;
        stackPush(stack,handle[0]);
        handle[0] = NULL;
        // DELETE THIS
      //  printf("  redukce E->id\n");
        // END DELETE
    }
    // Pravidlo E -> (E)
    else if ((i == 3) && (handle[0]->dataIt->type == t_bracket_r) && (handle[1]->typeIt==EXPR) && (handle[2]->dataIt->type == t_bracket_l)) { 
        stackPush(stack,handle[1]);
        handle[0] = NULL;
    }
    return handle;
}

// Vyhledává pravidla pro aritmetické a porovnávací instrukce
void reduceExp(BTSNode *targetNode, tStackIt *handle[3], instrStack *iStack, tStack *stack) {
    // Pokud byl výraz zredukován již v chnToExpr, neděláme nic
    if (handle[0] == NULL) {
        //DELETE THIS
         //   printf("  nedelame nic\n");
        //END DELETE
        return;
    }
    
    Instr *instr = NULL;
    instr = instrItemInit();
    BTSNode *start = mTree.actFunction;
    
    if (start != NULL) {
       start = mTree.actClass;
    }
    
    // Jedná se o aritmetickou nebo porovnávací instrukci
    if ((handle[0]->typeIt == EXPR) && (handle[2]->typeIt == EXPR)) {

        
        
        // TODO vytvořit tempnode, jeho pointer přiřadit do id3 a pushnout jeho název na stack
        instr->Id3 = createNewNode("temp"+tempNodeCounter,temp,var_null,0,1);
        tToken *token = initToken();
        updateToken(token,"temp"+tempNodeCounter); 
        tStackIt *item = itemInit(token);
        item->typeIt = EXPR;
        stackPush(stack,item);
        
        // Najdeme uzly
        instr->Id1 = searchForNode(handle[2]->dataIt->data,var,NULL);
        instr->Id2 = searchForNode(handle[0]->dataIt->data,var,NULL);
        
        
        
        // DELETE THIS
       // printf(" \x1B[32m Vytvoření instrukce: \x1B[0m%s = %s operace %s\n","temp"+tempNodeCounter,nodePrint(instr->Id1),nodePrint(instr->Id2));
        // END DELETE
        tempNodeCounter++;
        
        switch (handle[1]->dataIt->type) {
            case t_plus: ;// E -> E+E
                instr->type = insPlus;
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
                instr->Id3 = NULL;
                instrStackPush(iStack,instr);
                break;
            case t_comparasion_ne: // E -> E!=E
                instr->type = insNotEqual;
                instr->Id3 = NULL;
                instrStackPush(iStack,instr);
                break;
            case t_less: // E -> E<E
                instr->type = insLess;
                instr->Id3 = NULL;
                instrStackPush(iStack,instr);
                break;
            case t_less_eq: // E -> E<=E
                instr->type = insLessOrEqual;
                instr->Id3 = NULL;
                instrStackPush(iStack,instr);
                break;
            case t_greater: // E -> E>E
                instr->type = insGreater;
                instr->Id3 = NULL;
                instrStackPush(iStack,instr);
                break;
            case t_greater_eq: // E -> E>=E
                instr->type = insGreaterOrEqual;
                instr->Id3 = NULL;
                instrStackPush(iStack,instr);
                break;
            default: // Syntaktická chyba
                throwException(2,0,0);
                break;
        }
    }
    else { // TODO je to tu vůbec potřeba?
        printf("\x1B[31m ANO!! ten id tam byl potřeba :-)\x1B[0m\n");
        throwException(2,0,0);
    }
}

/* Funkce provádí Zpracování aritmetických výrazů
 * @param ukazatel na cílový uzel 
 * @return vrací poslední načtený token (možná nebude potřeba)
 */
tToken *expression(BTSNode *targetNode, tExpType expType) {
   /* printf("\n");
    
    BTSNode *pokusnode = createNewNode("AHOJ",var,var_int,0,1);
    pokusnode =searchForNode("AHOJ", var, NULL);
    printf("node=|%s|\n",nodePrint(pokusnode));
    
    printf("\n-----------------------------------\n");*/
    /* Pokud jsme mimo funkci nebo jsme ve funkci run, ukládáme instrukce na globální instrukční stack. 
     * V opačném případě na instruční stack aktuální funkce */ 
    instrStack *localIStack = global.iStack;
    if ((mTree.actFunction != NULL) || (strcmp(mTree.actFunction->key, "run") != 0)) {
		instrStackCopy(localIStack, mTree.actFunction->iStack); 
    }
    
    // Inicializujeme zásobník a vložíme na něj terminál ';'
    tStack *stack = NULL;
    stack = stackInit(stack);

    tToken *token = initToken();
    fillToken(token, t_semicolon);

    tStackIt *item = itemInit(token);
    item->typeIt = TERM;
    stackPush(stack,item);

    token = getToken();
    Instr *instr = NULL;
    instr = instrItemInit(instr);
       
    
    while (TRUE) {
        if (topTerm(stack)->type == t_semicolon) {
            // Jsme na konci podmínky
            if ((targetNode == NULL) && (token->type == t_bracket_r)){ 
                printf("  jsme na konci podminky!!\n");
                break;
            }
            // Jsme na konci výrazu
            else if (token->type == t_semicolon) {
             //   printf("\x1B[32m  Vytvoření instrukce:\x1B[0m TargetNode = %c\n",stackTop(stack)->dataIt->data[0]);
                instr->Id3 = targetNode;
                instr->Id1 = searchForNode(stackTop(stack)->dataIt->data,temp,NULL);
                instr->Id2 = NULL;
                instr->type = insAssignment;
                instrStackPush(localIStack,instr);
                break;
            }
            
            //TODO Co když je teď načtený token roven ','?
        } 
        // Jedná se o funkci uvnitř výrazu
        else if ((isIdent(topTerm(stack))) && (token->type == t_bracket_l)) {            
            /* Vytvořím instrukci, kde: 
             *   - id3 je proměnná v aktuální funkci
             *   - id1 je řetězec s id volané funkce
             *   - id2 je pole argumentů
             *   - type je insFunctionCall
             */
            //instr->Id3 = targetId; 
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
        // Pokud token do výrazu nepatří, jedná se o syntaktickou chybu
        else if (token->type > t_string) {
            throwException(2,0,0);
        }
        
        switch (getPrecChar(topTerm(stack),token)) {
            case '<': ; // Tento středník tu musí být jinak to řve error :-)
                // Vloží znak '<' za topTerm
                tToken *lessToken = initToken();
                fillToken(lessToken, t_less);
                item = itemInit(lessToken);
                item->typeIt = NONTERM;
                stackShift(stack,item);

                // Vloží aktuální token na zásobník
                item = itemInit(token);
                item->typeIt = TERM;
                stackPush(stack,item);
                stackPrint(stack);

                //Načte nový token
                token = getToken();
                break;
            case '=':
                // Vloží aktuální token na zásobník
                item = itemInit(token);
                item->typeIt = TERM;
                //stack->counter++;
                stackPush(stack,item);
                stackPrint(stack);

                //Načte nový token
                token = getToken();
                break;
            case '>': ; // Stejná situace se středníkem jako v první case
                tStackIt *handle[3];
                chnToExp(stack,handle);
                reduceExp(targetNode,handle,localIStack,stack);
                break;
            default:
                // Syntaktická chyba
                throwException(2,0,0);
                break;
        }
    }
    stackDestroy(stack); 
}

void functionCall(BTSNode *targetNode) {
    // TODO když funkce nemá argumenty, id2 instrukce functioncall je NULL
    Instr *instr = instrItemInit();
    
    if (targetNode == NULL) {
        // TODO jedná se o void funkci
        int out = expression('F',expArg);
        
        //DELETE THIS
        int i = 0;
        //END DELETE
        while (out == 0) {
            //TODO BTSNode *node = createNewNode("arg" + argCounter,arg,var_int,0,1);
            expression('F',expArg);
        }
    }
    else {
        //createNewNode("arg" + argCounter,arg,var_int,0,1);
        expression('F',expArg);
    }
    instr->Id3 = targetNode;
    instr->type = insFunctionCall;
    //instrStackPush(iStack,instr);
}

char *substr(char str[], int i, int n) {

	char *realString = '\0';
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

void copyString(char str1[], char str2[]) {
	strcpy(str1, str2);
}

int compareString(char str1[], char str2[]) {
   //porovná dva zadané řetězce str1 a str2 a vrátí celočíselnou hodnotu dle toho, zda je str1 před, roven, nebo za str2
	int result = strcmp(str1, str2);
	if (result < 0) {
		result = -1;
	} else if (result > 0) {
		result = 1;
	}

	return result;

}

int strLength(char str[]) {
	//vrátí délku řetězce (počet znaků) zadaného jedním parametrem str
	int length = strlen(str);
	return length;
}

int strEqual(char str1[], char str2[]) {
	int equal = !strcmp(str1, str2);
	return equal;
}

void strClear(char str[]) {
	// funkce sloužící k vymazání řetězce
	int length = strLength(str);
	while (length != 0) {
		str[length] = '\0';
		length--;
	}
}


char *readString(){
	int c = getchar();
	char *str = '\0';
	int i = 0;


	while (c != EOF || c != '\n') {
		str[i] = (char)c;
		i++;
		c = getchar();
	}
	return str;
}

void print(char string[]) {
	// nejaka podminka kvuli typu vstupu..
	printf("%s", string);

}


int readInt() {
	char *str = readString();
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
	char *str = readString();
	char *end;
	double doubleNumber = strtod(str, &end);

	if (*end != '\0' || doubleNumber < 0) {
		throwException(7, 0, 0);
	}

	return doubleNumber;
}

