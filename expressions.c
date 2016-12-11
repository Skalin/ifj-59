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
#include "instrstack.h"

#define STR_ERROR   0
#define STR_SUCCESS 1
#define STR_ALLOCATION_SIZE 8  // Udává, kolik bude alokováno na začátku paměti. Pokud načítáme po jednom znaku, dojde k alokaci na násobky tohoto čísla

// TODO zkontrolovat správnost tabulky
char precTable[16][16] = {
		//    (   )   /   *   +   -   ==  !=  <   >   <=  >=  !   ,   ;   ID
		{'<','=','<','<','<','<','<','<','<','<','<','<','<','=','F','<'}, // (
		{'F','>','>','>','>','>','>','>','>','>','>','>','>','>','>','F'}, // )
		{'<','>','>','>','>','>','>','>','>','>','>','>','>','>','>','<'}, // /
		{'<','>','>','>','>','>','>','>','>','>','>','>','>','>','>','<'}, // *
		{'<','>','<','<','>','>','>','>','>','>','>','>','>','>','>','<'}, // +
		{'<','>','<','<','>','>','>','>','>','>','>','>','>','>','>','<'}, // -
		{'<','>','<','<','<','<','>','>','>','>','>','>','>','>','>','<'}, // ==
		{'<','>','<','<','<','<','>','>','>','>','>','>','>','>','>','<'}, // !=
		{'<','>','<','<','<','<','>','>','>','>','>','>','>','>','>','<'}, // <
		{'<','>','<','<','<','<','>','>','>','>','>','>','>','>','>','<'}, // >
		{'<','>','<','<','<','<','>','>','>','>','>','>','>','>','>','<'}, // <=
		{'<','>','<','<','<','<','>','>','>','>','>','>','>','>','>','<'}, // >=
		{'=','>','>','>','>','>','>','>','>','>','>','>','>','>','F','<'}, // !
		{'<','=','<','<','<','<','F','F','F','F','F','F','F','=','F','<'}, // ,
		{'<','F','<','<','<','<','<','<','<','<','<','<','F','=','F','<'}, // ;
		{'F','>','>','>','>','>','>','>','>','>','>','>','F','>','>','F'}  // ID
};

mainTree mTree;
int tempNodeCounter = 0;
int constCounter = 0;
int argCounter = 0;

//DELETE THIS
void stackPrint(tStack *stack) {
	for (int i = 1; i <= stack->counter; i++) {
		printf( "  Stack: pozice=%d obsah=%c type=%d\n", i, stack->data[i]->dataIt->data[0],stack->data[i]->typeIt );
	}
	//printf("  Stack counter=%d\n",stack->counter);
}

char* nodePrint(BTSNode *node) {
	if (node == NULL)
		return "NULL";

	return node->key;
}
//END DELETE

char *addIntToStr(char *str, int integer) {
	/*char buffer[512];
	sprintf(buffer, "%d", 1);
	strncat(str, buffer, 512);
	return buffer;*/
	return NULL;
}

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
		stackTokenNum = 15;
	}
	if (isIdent(inToken) || isConst(inToken)) {
		inTokenNum = 15;
	}
	//DELETE THIS
	printf("getPrecChar: [%2d][%2d] \'%c\'  vstupni token:|%s|\n",stackTokenNum,inTokenNum,precTable[stackTokenNum][inTokenNum],inToken->data);
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
		printf("  Handle[%d]=%c  ",i-1,handle[i-1]->dataIt->data[0]);
		stackPop(stack);
	}
	printf("\n");
	// Odstraníme ze zásobníku začátek handle '<'
	stackPop(stack);

	// Pravidlo E -> id
	if ((i == 1) && (handle[0]->typeIt == TERM) && ((isIdent(handle[0]->dataIt)) || (isConst(handle[0]->dataIt)))) {
		if (isConst(handle[0]->dataIt)) {
			//TODO vytvořit nový node a jeho název vložit do handle[0]
			BTSNode *node = createNewNode("ABCDEFGH" + constCounter,temp,var_int,0,1); // TODO typ konstanty je v tokenu

			if (handle[0]->dataIt->type == t_int) {
				node->data.type = var_int;
				node->data.value.intValue = atoi(handle[0]->dataIt->data);
			}
			else if (handle[0]->dataIt->type == t_double){
				node->data.type = var_double;
				node->data.value.doubleValue = atof(handle[0]->dataIt->data);
			}
			else if (handle[0]->dataIt->type == t_double_e){
				node->data.type = var_double;
				node->data.value.doubleValue = atof(handle[0]->dataIt->data);
			}
			else if (handle[0]->dataIt->type == t_string){
				node->data.type = var_string;
				node->data.value.stringValue = handle[0]->dataIt->data;
			}
			// DELETE THIS
			tToken *token = initToken();
			updateToken(token,"ABCDEFGH"+constCounter);
			tStackIt *item = itemInit(token);
			item->typeIt = EXPR;
			handle[0] = item;
			//END DELETE
			constCounter++;
		}
		handle[0]->typeIt = EXPR;
		stackPush(stack,handle[0]);
		handle[0] = NULL;
		stackPrint(stack);
		// DELETE THIS
		// printf("  redukce E->id\n");
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
		instr->Id3 = createNewNode("abcdefgh"+tempNodeCounter,temp,var_null,0,1);
		tToken *token = initToken();
		updateToken(token,"abcdefgh"+tempNodeCounter);
		tStackIt *item = itemInit(token);
		item->typeIt = EXPR;
		stackPush(stack,item);

		// Najdeme uzly
		instr->Id1 = searchForNode(handle[2]->dataIt->data,var,mTree.actFunction->variables);
		instr->Id2 = searchForNode(handle[0]->dataIt->data,var,mTree.actFunction->variables);

		if (instr->Id1 == NULL) {
			instr->Id1 = searchForNode(handle[2]->dataIt->data,temp,mTree.actFunction->variables);
		}
		if (instr->Id2 == NULL) {
			instr->Id2 = searchForNode(handle[0]->dataIt->data,temp,mTree.actFunction->variables);
		}



		// DELETE THIS
		printf(" \x1B[32m vytvoreni instrukce: \x1B[0m%s = %s operace %s\n","temp"+tempNodeCounter,nodePrint(instr->Id1),nodePrint(instr->Id2));
		// END DELETE
		tempNodeCounter++;

		switch (handle[1]->dataIt->type) {
			case t_plus: ;// E -> E+E
				instr->type = insPlusTmp;
				instrStackPush(iStack,instr);
				break;
			case t_minus: // E -> E-E
				instr->type = insMinusTmp;
				instrStackPush(iStack,instr);
				break;
			case t_multi: // E -> E*E
				instr->type = insMuxTmp;
				instrStackPush(iStack,instr);
				break;
			case t_div: // E -> E/E
				instr->type = insDivTmp;
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
	else {
		throwException(2,0,0);
	}
}

/* Funkce provádí Zpracování aritmetických výrazů
 * @param ukazatel na cílový uzel
 * @return vrací poslední načtený token (možná nebude potřeba)
 */
tToken *expression(BTSNode *targetNode, int isArg) {
	/* Pokud jsme mimo funkci nebo jsme ve funkci run, ukládáme instrukce na globální instrukční stack.
	 * V opačném případě na instruční stack aktuální funkce */
	instrStack *localIStack = global.iStack;
	if ((mTree.actFunction != NULL) && (strcmp(mTree.actFunction->key, "run") != 0)) {
		localIStack = mTree.actFunction->iStack;
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
			if (!isArg && (targetNode == NULL) && (token->type == t_bracket_r)){
				break;
			}
				// Jsme na konci výrazu
			else if ((token->type == t_semicolon) || ((isArg) && ((token->type == t_bracket_r) || token->type == t_comma))){
				printf("\x1B[32m  Vytvoření instrukce:\x1B[0m TargetNode = %c\n",stackTop(stack)->dataIt->data[0]);
				instr->Id3 = targetNode;
				instr->Id1 = searchForNode(stackTop(stack)->dataIt->data,var,mTree.actFunction->variables);
				if (instr->Id1 == NULL)
					instr->Id1 = searchForNode(stackTop(stack)->dataIt->data,temp,mTree.actFunction->variables);
				if (instr->Id1 == NULL) {
					targetNode = NULL;
					break;
				}
				instr->Id2 = NULL;
				instr->type = insAssignment;
				instrStackPush(localIStack,instr);
				// Pokud zpracováváme argument a není poslední, tak zpracováváme dál
				if ((isArg) && (token->type == t_comma)) {
					BTSNode *node = createNewNode("01234567" + argCounter,temp,var_null,0,1);
					targetNode->variables = node;
					//printf("----------------%s->variables = %s\n",nodePrint(targetNode),nodePrint(node));
					argCounter++;
					expression(node,1);
				}
				targetNode->inc = 1;
				break;
			}
		}
			// Jedná se o funkci uvnitř výrazu
		else if ((isIdent(topTerm(stack))) && (token->type == t_bracket_l)) {
			// Jedná se o vestavěnou funkci
			if ((strcmp(topTerm(stack)->data, "ifj16.readInt") == 0) || (strcmp(topTerm(stack)->data, "ifj16.readDouble") == 0) || (strcmp(topTerm(stack)->data, "ifj16.readString") == 0) || (strcmp(topTerm(stack)->data, "ifj16.length") == 0) || (strcmp(topTerm(stack)->data, "ifj16.substr") == 0) || (strcmp(topTerm(stack)->data, "ifj16.compare") == 0) || (strcmp(topTerm(stack)->data, "ifj16.find") == 0) || (strcmp(topTerm(stack)->data, "ifj16.sort") == 0)) {
				BTSNode *tempNode = createNewNode("abcdefgh"+tempNodeCounter,temp,var_null,0,1);
				tempNodeCounter++;
				printf("---------------------Zavolano functionCall\n");
				functionCall(tempNode,NULL,topTerm(stack)->data);
				printf("---------------------Konec functionCall\n");
				item->typeIt = EXPR;
				copyString(&item->dataIt->data,&tempNode->key);
				stackPush(stack,item);
			}
				// Situace kdy ifj16.print je součástí výrazu = sémantická chyba
			else if (strcmp(topTerm(stack)->data, "ifj16.print") == 0) {
				throwException(3,0,0); // TODO doplnit správný kód chyby
			}
				// Jedná se o nevestavnou funkci
			else {
				BTSNode *functionNode = searchForNode(topTerm(stack)->data,function,mTree.actClass->functions);
				// Pokud funkce neexistuje nebo je void
				if ((functionNode == NULL) || (functionNode->data.type == var_null)) {
					throwException(3,0,0); // TODO doplnit správný kód chyby
				}
				BTSNode *tempNode = createNewNode("abcdefgh"+tempNodeCounter,temp,var_null,0,1);
				tempNodeCounter++;
				printf("---------------------Zavolano functionCall\n");
				functionCall(tempNode,functionNode,topTerm(stack)->data);
				printf("---------------------Konec functionCall\n");
				item->typeIt = EXPR;
				copyString(&item->dataIt->data,&tempNode->key);
				stackPush(stack,item);
			}
			token = getToken();
			if (token->type != t_semicolon) {
				throwException(2,0,0); // TODO doplnit správný kód chyby
			}
				break;
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
	return NULL;
}

void functionCall(BTSNode *targetNode, BTSNode *functionNode, char *functionName) {
	instrStack *localIStack = global.iStack;
	if ((mTree.actFunction != NULL) && (strcmp(mTree.actFunction->key, "run") != 0)) {
		instrStackCopy(localIStack, mTree.actFunction->iStack);
	}



	// TODO když funkce nemá argumenty, id2 instrukce functioncall je NULL
	Instr *instr = instrItemInit();
	instr->Id3 = targetNode;
	instr->Id1 = functionNode;

	BTSNode *node = createNewNode("01234567" + argCounter,temp,var_null,0,0);
	argCounter++;
	expression(node,1);
	instr->Id2 = node;

	// Pokud se jedná o vestavěnou funkci
	if (instr->Id1 == NULL) { // TODO možná zbytečná podmínka
		// Volání funkce má argumenty
		if (node->inc != 0) {
			instr->Id1 = instr->Id2;
			instr->Id2 = instr->Id2->variables;
		}
		else {
			instr->Id1 = NULL;
			instr->Id2 = NULL;
		}
	}


	if (strcmp(functionName, "ifj16.readInt") == 0) {
		instr->type = insIfj16readInt;
	}
	else if (strcmp(functionName, "ifj16.readDouble") == 0) {
		instr->type = insIfj16readDouble;
	}
	else if (strcmp(functionName, "ifj16.readString") == 0) {
		instr->type = insIfj16readString;
	}
	else if (strcmp(functionName, "ifj16.length") == 0) {
		instr->type = insIfj16lenght;
	}
	else if (strcmp(functionName, "ifj16.substr") == 0) {
		instr->type = insIfj16substr;
	}
	else if (strcmp(functionName, "ifj16.compare") == 0) {
		instr->type = insIfj16compare;
	}
	else if (strcmp(functionName, "ifj16.find") == 0) {
		instr->type = insIfj16find;
	}
	else if (strcmp(functionName, "ifj16.sort") == 0) {
		instr->type = insIfj16sort;
	}
	else if (strcmp(functionName, "ifj16.print") == 0) {
		instr->type = insIfj16print;
	}
	else {
		instr->type = insFunctionCall;
	}

	instrStackPush(localIStack,instr);
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

void copyString(char *str1[], char *str2[]) {
	int i = 0;
	str1[i] = '\0';
	while(str2[i] != '\0') {
		str1[i] = str2[i];
		i++;
	}
	str1[i] = '\0';
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

	char buffer[257];
	char *str;

	if ((str = fgets(buffer, sizeof(buffer),stdin)) != NULL) {
		str[strlen(str)-1] = '\0';
	} else {
		throwException(7, 0, 0);
	}
	return str;
}

void print(char *string) {
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
