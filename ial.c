/**
 * IFJ/IAL - Lexikální analyzátor
 * Varianta:    b/2/I
 * Soubor:      ial.c
 * Tým:         59
 * Autoři:      Jan Hrbotický, xhrbot01@stud.fit.vutbr.cz
 *              Dominik Skála, xskala11@stud.fit.vutbr.cz
 *              Milan Hruban, xhruba08@stud.fit.vutbr.cz
 *              Martin Hons, xhonsm00@stud.fit.vutbr.cz
 *              David Hél, xhelda00@stud.fit.vutbr.cz
 */
#include "ial.h"
#include "garbage_collector.h"
#include <stdlib.h>
#include <string.h>
#include "error_handler.h"

// find a sort dle zadani

// pomocne fce pro find

void initMismatchTable(mismatchTable *Table) {
	Table->First = NULL;
	Table->Act = Table->First;
}

void disposeMismatchTable(mismatchTable *Table) {
	mismatchTableItem pom = NULL;

	while (Table->First != NULL) {
		pom = Table->First;
		Table->First = Table->First->next;
		free(pom);
	}
}

void insertNext(mismatchTable *Table, char c, int shiftValue) {

	mismatchTableItem pom = malloc(sizeof(struct mmtItem));

	if (pom != NULL) {
		if (Table == NULL) {
			pom->c = c;
			pom->shiftValue = shiftValue;
			pom->next = NULL;
			Table->First = pom;
		} else {
			pom = Table->First;
			Table->First->next = pom;
			Table->First->c = c;
			Table->First->shiftValue = shiftValue;
		}
	} else {
		throwException(99,0,0);
	}
}

int findChar(mismatchTable *Table, char c) {
	int i = -1;
	Table->Act = Table->First;
	while (Table->Act != NULL) {
		i++;
		if (c == Table->Act->c) {
			break;
		}
		Table->Act = Table->Act->next;
	}

	return (i);
}

int getShiftValue(mismatchTable *Table, char c) {
	int i = 0;
	int position = findChar(Table, c);

	Table->Act = Table->First;
	while (i < position) {
		Table->Act = Table->Act->next;
		i++;
	}
	return Table->Act->shiftValue;
}

void updateShift(mismatchTable *Table, char c, int shiftValue) {
	int i = 0;
	int position = findChar(Table, c);
	Table->Act = Table->First;
	while (i < position) {
		Table->Act = Table->Act->next;
		i++;
	}

	Table->Act->shiftValue = shiftValue;

}

// samotny find
int find(SString *str, SString *search) {

	int i = 0, j = 0;
	int found = 0;
	int others = strLength(search);
	int textLength = strLength(str);
	int stop = -1; // zarazka
	int shiftValue = others; // prvotni nastaveni shiftu
	mismatchTable Table;
	initMismatchTable(&Table);

	// cyklus naplni mismatch Tabulku znaky ze stringu "search"
	while (search->data[i] != '\0' || search->data[i] != EOF) {
			if (findChar(&Table, search->data[i]) < 0) {
				if (search->data[i+1] != '\0') { // pokud toto neni posledni prvek
					insertNext(&Table, search->data[i], strLength(search) - i - 1);
				} else { // jinak nastavime shift posledniho prvku dle boyer-moore algoritmu
					insertNext(&Table, search->data[i], others);
				}
			} else {
				updateShift(&Table, search->data[i], (strLength(search)-i-1));
			}
			i++;
	}

	i = 0; // jen pro jistotu

	while (found == 0 || str->data[stop] != '\0' || str->data[i] != EOF || stop > textLength) { // dokud neni string nalezen nebo neni konec stringu nebo neni eof, hledam
		stop += shiftValue;
		for (i = others-1, j = 0; i >= 0, j <= others-1; i--, j++) {
			if (str->data[stop-j] != search->data[i]) { // pokud se nam dva znaky ve stringu neshoduji, vyskocime z jednoho cyklu a posuneme se shiftem
				break;
			}
			if (str->data[stop-others+1] == search->data[0]) {
				found = stop-others+1;
				break;
			}
			shiftValue = getShiftValue(&(Table), search->data[i]);
		}
	}

	disposeMismatchTable(&Table);

	return found;

}

// swap pro heapsort
char swap(char *a, char *b) {
    char c = '\0';
    
    c = *a;
    *a = *b;
    *b = c;
}

// pomocna funkce makeEven pro zjednoduseni vypoctu pozice prvku
int makeEven(int i) {
	if ((i % 2) != 0) {
		i += 1;
	}
	return i;
}

// fce pro korektni nastaveni pozice nejvetsiho prvku na zacatek haldy
SString repairHeap(SString *str) {

	int i = 0, j = 0;
	for (i = str->length-1; i > 0; --i) {
		j = 0;
		if ((i % 2) == 0) {
			j = 1;
			if ((str->data[i] > str->data[(makeEven(i)/2)-1]) && (str->data[i-1] > str->data[(makeEven(i)/2)-1])) {
				if (str->data[i] >= str->data[i-1]) {
					swap(&str->data[i], &str->data[(makeEven(i)/2)-1]);
				} else {
					swap(&str->data[i-1], &str->data[(makeEven(i)/2)-1]);
				}
			}
			if (str->data[i] > str->data[(makeEven(i)/2)-1]) {
				swap(&str->data[i], &str->data[(makeEven(i)/2)-1]);
			}
		} else {
			j = 1;
			if (str->data[i] > str->data[(makeEven(i)/2)-1]) {
				swap(&str->data[i], &str->data[(makeEven(i)/2)-1]);
			}
		}
	}
	if (j == 1)
		repairHeap(str);

	return *str;
}


// samotny heapsort
SString sort(SString *str) {
	SString helpString;
	initString(&(helpString));
    copyString(str, &helpString);



    int biggestNumber = 0;
	int length = strLength(&helpString);
    while (length) {

		repairHeap(&helpString);

		biggestNumber = helpString.data[0];

/*
 * zbytecne, protoze biggest number bude prvni
        for (int i = 0; i < helpString->length; i++) {
            if ((i+1) == helpString->length) {
                break;
            }
            biggestNumber = (helpString->data[i] > helpString->data[i+1] ? helpString->data[i] : helpString->data[i+1]);
        }
  */
        swap(&helpString.data[biggestNumber], &helpString.data[length-1]);
        
        length--;
    }

    return helpString;
}



//Uzel BT
tBTSNodePtr symbolTable;

// Hlavní strom
mainTree *mTree;

int argNo = 0;


void initTree(mainTree *tree) {
    mTree = tree;
    mTree->root= NULL;
    mTree->actClass= NULL;
    mTree->actFunction = NULL;
}

BTSNode searchForNode(tableName key, NodeType nodeType, BTSNode *start) {
    if(mTree->root != NULL) {

    } else {
        if (start == NULL)
            start= mTree->root;
        else {
            // Pokud nalezneme klic
            if(strcmp(key, start->key) == 0) {
                // Pokud je to typ ktery jsme hledali, vratime ho
                if (start->nodeType == nodeType)
                    return start;
            }
            // Pokud mame hledat v pravem podstromu
            else if(strcmp(key, &start->key) > 0) {
                return start->rptr == NULL ?  NULL : searchForNode(key, nodeType, start->rptr);
            }
            // Pokud mame hledat v levem podstromu
            else if (strcmp(key, &start->key) < 0)
                return start->lptr == NULL ?  NULL : searchForNode(key, nodeType, start->lptr);
            // V ostatnich pripadech (Chuck norris on STDin?) se jedna o chybu
            else
                throwException(99,0,0);
        }
    }
    return NULL;
}

void addNode(BTSNode *newItem, BTSNode *start) {
    if(begin != NULL) {
        if(strcmp(&newItem->key, &start->key) > 0) {
            // Pokud nemame uzel kam vlozit
            if(start->rptr != NULL) {
                addNode(newItem, start->rptr);
            }
            // Pokud ho mame kam vlozit
            else
                start->rptr = newItem;
                if(newItem->nodeType == function)
                    mTree->actFunction = newItem;
                if(newItem->nodeType == class)
                    mTree->actClass == newItem;

        } else if(strcmp(&newItem->key, &start->key) < 0) {
            // Pokud nemame uzel kam vlozit
            if(start->lptr != NULL) {
                addNode(newItem, start->lptr);
            }
                // Pokud ho mame kam vlozit
            else
                start->lptr = newItem;
            if(newItem->nodeType == function)
                mTree->actFunction = newItem;
            if(newItem->nodeType == class)
                mTree->actClass == newItem;

        // If there is anything else throw error
        } else
            throwException(99,0,0);
    }   else
        throwException(99,0,0);
}

void createNewNode(char *id, NodeType nodeType, varType variableType, int status) {
    if(argNo != 0)
        argNo = 0;

    // Inicializace noveho uzlu
    BTSNode *newNode = plusMalloc(sizeof(BTSNode));
    &newNode->key = id;
    newNode->nodeType = nodeType;
	newNode->inc = 0;
    newNode->lptr = NULL;
    newNode->rptr = NULL;

    // Urceni zacatku podle typu uzlu
    BTSNode *start;

    if (newNode->nodeType == var) {
        newNode->data.type = variableType;
        newNode->variables = NULL; // Neni potrebne u promenne

        if (status == 1)
            start = mTree->actClass->variables;
        else
            start = mTree->actFunction->variables;
    }
    else if (newNode->nodeType == function) {
        newNode->data.type = variableType; // Nastavime navratovou hodnotu funkce
        newNode->variables = NULL;
        start= mTree->actClass->functions;
    }
    else if (newNode->nodeType == class) {
        newNode->functions = NULL;
        newNode->variables = NULL;
        start= mTree->root;
    }

    // Pokud neexistuje korenovy uzel a jedna se o classu
    if (newNode ->nodeType == class) {
        if (mTree->root == NULL) {
            mTree->root = newNode;
            mTree->actClass = newNode;
        }
    }
    // Pokud se jedna o funkci a v aktivni classe nemame aktivni funkci
    else if (newNode ->nodeType == function) {
        if(mTree->actClass->functions == NULL) {
            mTree->actClass->functions = newNode;
            mTree->actFunction = newNode;
        }
    }
    // Pokud se jedna o promennou
    else if (newNode ->nodeType == var) {
        if(status) {
            if(mTree->actClass->variables == NULL)
                mTree->actClass->variables = newNode;
        }
        else if (mTree->actFunction->variables == NULL) {
            if(mTree->actFunction != NULL)
                mTree->actFunction->variables = newNode;
        }
    }
    else
        addNode(newNode, start);
}

void addArgument(char *id, int type) {
    BTSNode *argument = plusMalloc(sizeof(BTSNode));
    &argument->key = id;
    argument->nodeType = var;
    argument->data.type = type;
    argument->lptr = NULL;
    argument->rptr = NULL;

    argNo++;
    argument->argNo = argNo;
    mTree->actFunction->data.value.intValue = argNo;

    if (mTree->actFunction->variables != NULL)
        addNode(argument, mTree->actFunction->variables);
    else
        mTree->actFunction->variables = argument;
}

tNode *findArgument(BTSNode *start, int argNo) {
    if (begin != NULL) {
        if(start->nodeType == var) {
            if(start->argNo == argNo)
                return start;
        }

        BTSNode *result;
        result= findArgument(start->lptr, argNo);
        if (result == NULL)
            result = findArgument(start->rptr, argNo);

        return found;

    } else
        return NULL;
}







// OLD


void TSInit(void) {
    BTSInit(&symbolTable);
}

void TSDispose(void) {
    BTSDispose(&symbolTable);
}

tabSymbol * TSInsert(tabSymbol symbol) {
    // Pokud se uspesne vlozi, navrati se
    if(tBTSNodePtr root = BTSInsert(&symbolTable, symbol.name, symbol))
        return &(root->data);
    //V opacnem pripade se vrati NULL
    else
        return NULL;
}

tabSymbol TSInsertInt(tableName name, int data) {
    // Vytvoreni promenne
    tabSymbol symbol;

    // Inicializace dat
    symbol.inc = 1;
    symbol.name = name;
    symbol.type = var_int;
    symbol.value.intValue = data;

    // Navraceni symbolu do binarniho stromu
    return TSInsert(symbol);
}

tabSymbol TSInsertDouble(tableName name, double data) {
    // Vytvoreni promenne
    tabSymbol symbol;

    // Inicializace dat
    symbol.inc = 1;
    symbol.name = name;
    symbol.type = var_double;
    symbol.value.doubleValueValue = data;

    // Navraceni symbolu do binarniho stromu
    return TSInsert(symbol);
}

tabSymbol TSInsertString(tableName name, char *data) {
    // Vytvoreni promenne
    tabSymbol symbol;

    // Inicializace dat
    symbol.inc = 1;
    symbol.name = name;
    symbol.type = var_string;
    symbol.value.stringValueValue = data;

    // Navraceni symbolu do binarniho stromu
    return TSInsert(symbol);
}

tabSymbol TSInsertSimpleIdent(tableName name, char *data) {
    // Vytvoreni promenne
    tabSymbol symbol;

    // Inicializace dat
    symbol.name = name;
    symbol.type = var_simpleident;
    symbol.value.simpleIdentValue = data;

    // Navraceni symbolu do binarniho stromu
    return TSInsert(symbol);
}

tabSymbol TSInsertCompleteIdent(tableName name, char *data) {
    // Vytvoreni promenne
    tabSymbol symbol;

    // Inicializace dat
    symbol.inc = 1;
    symbol.name = name;
    symbol.type = var_completeidentident;
    symbol.value.completeIdentValue = data;

    // Navraceni symbolu do binarniho stromu
    return TSInsert(symbol);
}

tabSymbol TSInsertFunction(tableName name, char *data) {
    // Vytvoreni promenne
    tabSymbol symbol;

    // Inicializace dat
    symbol.inc = 1;
    symbol.name = name;
    symbol.type = var_function;
    symbol.isFunction = 1;
    symbol.argument = NULL;

    // Navraceni symbolu do binarniho stromu
    return TSInsert(symbol);
}
tabSymbol TSInsertClass(tableName name, char *data) {
    // Vytvoreni promenne
    tabSymbol symbol;

    // Inicializace dat
    symbol.inc = 1;
    symbol.name = name;
    symbol.type = var_class;
    symbol.isClass = 1;

    // Navraceni symbolu do binarniho stromu
    return TSInsert(symbol);
}

void TSInitSymbol (tabSymbol symbol) {
    //Pokud máme co inicializovat
    if (symbol != NULL) {
        //Inicializujeme data
        symbol.name= NULL;
        symbol.type= NULL;
        symbol.inc= 1;
        symbol.isFunction= 0;
        symbol.isArgument= 0;
        symbol.argument= NULL;
    }
}

tBTSNodePtr BTSSearch (tBTSNodePtr root, tableName key) {
    // Pokud máme kde hledat
    if (root != NULL) {
        // Pokud nalezneme, navrátíme hodnotu kořene
        if (strcmp(root->data.name, key) == 0)
            return root;
        //Případně hledáme rekurzivně vpravo
        else if (strcmp(root->data.name, key) > 0)
            return BTSSearch(root->rptr, key);
        // Nebo vlevo
        else
            return BTSSearch(root->lptr, key);
    // Pokud nemáme kde hledat, vrací funkce NULL
    } else
        return NULL;
}

static tBTSNodePtr BTSInsert(tBTSNodePtr *root, tableName key, tabSymbol symbol) {
    // Pokud neexistuje žádný kořen
    if ( (*root) == NULL) {
        //Alokujeme paměť pro kořen
        *root = plusMalloc(sizeof(struct tBTSNode));

        //Inicializujeme data
        (*root)->key = key;
        (*root)->data = symbol;
        (*root)->lptr = NULL;
        (*root)->rptr = NULL;
    //Pokud neexistuje
    } else {
        // Pokud je klíč nalezen
        if (strcmp((*root)->key, key) == 0) {
            // Přepíšeme data v nalezeném uzlu a kořen navrátíme
            (*root)->data = symbol;
            return *root;
        // Pokud je klíč více vpravo, voláme rekurzivně funkci nad pravým podstromem
        } else if (strcmp((*root)->key, key) > 0)
            return BTSinsert(&((*root)->rptr), key, symbol);
        // Obdobně pokud je vlevo
        else
            return BTSinsert(&((*root)->lptr), key, symbol);
    }
    // Pokud funkcí spustí Chuck Norris...
    return NULL;
}

static void BTSDispose(tBTSNodePtr *root) {
    if((*root) != NULL) {
        //Uvolneni leveho podstromu
        BTSDispose(&((*root)->lptr));

        //Uvolneni praveho podstromu
        BTSDispose(&((*root)->rptr));

        // Kořen inicializován na NULL, neexistuje
        *root= NULL;
    }
}
