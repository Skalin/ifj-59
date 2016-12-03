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

// find a sort dle zadani

// pomocne fce pro find, tedy funkce pro MismatchTabulku

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

	mismatchTableItem pom = malloc(sizeof(struct mismatchTableItem));

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
int find(String str, String search) {

	int i = 0, j = 0;
	int found = -1;
	int others = strLength(search);
	int textLength = strLength(str);
	int stop = -1; // zarazka
	int shiftValue = others; // prvotni nastaveni shiftu
	mismatchTable Table;
	initMismatchTable(&Table);

	if (others == 0) {
		return 0;
	} else if (strLength(str) < strLength(search)) {
		return found;
	}

	// cyklus naplni mismatch Tabulku znaky ze stringu "search"
	while (search[i] != '\0' || search[i] != EOF) {
			if (findChar(&Table, search[i]) < 0) {
				if (search[i+1] != '\0') { // pokud toto neni posledni prvek
					insertNext(&Table, search[i], strLength(search) - i - 1);
				} else { // jinak nastavime shift posledniho prvku dle boyer-moore algoritmu
					insertNext(&Table, search[i], others);
				}
			} else {
				updateShift(&Table, search[i], (strLength(search)-i-1));
			}
			i++;
	}

	i = 0; // jen pro jistotu

	while (found == -1 || str[stop] != '\0' || str[i] != EOF || stop > textLength) { // dokud neni string nalezen nebo neni konec stringu nebo neni eof, hledam
		stop += shiftValue;
		for (i = others-1, j = 0; i >= 0 && j <= others-1; i--, j++) {
			shiftValue = getShiftValue(&(Table), search[i]);
			if (str[stop-j] != search[i]) { // pokud se nam dva znaky ve stringu neshoduji, vyskocime z jednoho cyklu a posuneme se shiftem
				break;
			}
			if (str[stop-others+1] == search[0]) {
				found = stop-others+1;
				break;
			}
		}
	}

	disposeMismatchTable(&Table);

	return found;

}

// swap pro heapsort
void swap(char *a, char *b) {
    char c = *a;
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
String repairHeap(String str) {

	int i = 0, j = 0;
	for (i = strLength(str)-1; i > 0; --i) {
		j = 0;
		if ((i % 2) == 0) {
			if ((str[i] > str[(makeEven(i)/2)-1]) && (str[i-1] > str[(makeEven(i)/2)-1])) {
				j = 1;
				if (str[i] >= str[i-1]) {
					swap(&str[i], &str[(makeEven(i)/2)-1]);
				} else {
					swap(&str[i-1], &str[(makeEven(i)/2)-1]);
				}
			}
			if (str[i] > str[(makeEven(i)/2)-1]) {
				j = 1;
				swap(&str[i], &str[(makeEven(i)/2)-1]);
			}
		} else {
			if (str[i] > str[(makeEven(i)/2)-1]) {
				j = 1;
				swap(&str[i], &str[(makeEven(i)/2)-1]);
			}
		}
	}
	if (j == 1)
		repairHeap(str);

	return str;
}


// samotny heapsort
String sort(String str) {
	String helpString = str;

	int length = strLength(helpString);
    while (length) {

		repairHeap(helpString);

/*
 * zbytecne, protoze biggest number bude prvni
        for (int i = 0; i < helpString->length; i++) {
            if ((i+1) == helpString->length) {
                break;
            }
            biggestNumber = (helpString->data[i] > helpString->data[i+1] ? helpString->data[i] : helpString->data[i+1]);
        }
  */
        swap(&helpString[0], &helpString[length-1]);
        
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

BTSNode *searchForNode(tableName key, NodeType nodeType, BTSNode *start) {
    if(mTree->root == NULL) {

    } else {
        if (start == NULL)
            start = mTree->root;

		// Pokud nalezneme klic
		if(strcmp(key, start->key) == 0) {
			// Pokud je to typ ktery jsme hledali, vratime ho
			if (start->nodeType == nodeType)
				return start;
		}
		// Pokud mame hledat v pravem podstromu
		else if(strcmp(key, start->key) > 0) {
			return start->rptr == NULL ?  NULL : searchForNode(key, nodeType, start->rptr);
		}
		// Pokud mame hledat v levem podstromu
		else if (strcmp(key, start->key) < 0)
			return start->lptr == NULL ?  NULL : searchForNode(key, nodeType, start->lptr);
		// V ostatnich pripadech (Chuck norris on STDin?) se jedna o chybu
		else
			throwException(99,0,0);
    }
    return NULL;
}

void addNode(BTSNode *newItem, BTSNode *start) {
    if(start != NULL) {
        if(strcmp(newItem->key, start->key) > 0) {
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
                    mTree->actClass = newItem;

        } else if (strcmp(newItem->key, start->key) < 0) {
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
                mTree->actClass = newItem;

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
    newNode->key = id;
    newNode->nodeType = nodeType;
	newNode->inc = 0;
    newNode->lptr = NULL;
    newNode->rptr = NULL;

    // Urceni zacatku podle typu uzlu
    BTSNode *start = NULL;
    switch(newNode->nodeType) {
    case var:
        newNode->data.type = variableType;
        newNode->variables = NULL; // Neni potrebne u promenne

        if (status == 1)
            start = mTree->actClass->variables;
        else
            start = mTree->actFunction->variables;
        break;
    case function:
        newNode->data.type = variableType; // Nastavime navratovou hodnotu funkce
        newNode->variables = NULL;
        start= mTree->actClass->functions;
        break;
    case class:
        newNode->functions = NULL;
        newNode->variables = NULL;
        start= mTree->root;
        break;
    }

    // Pokud neexistuje korenovy uzel a jedna se o classu
    if (newNode ->nodeType == class && mTree->root == NULL) {
        mTree->root = newNode;
        mTree->actClass = newNode;
    } // Pokud ve tride neexistuji funkce
    else if (newNode ->nodeType == function && mTree->actClass->functions == NULL) {
            mTree->actClass->functions = newNode;
            mTree->actFunction = newNode;
    }
    // Pokud ve tride neexistuji zadne staticke promenne
    else if (newNode ->nodeType == var && mTree->actClass->variables == NULL && status) {
        mTree->actClass->variables = newNode;
    }
    // Pokud ve funkci neexistuji zadne promenne
    else if (newNode->nodeType == var && mTree->actFunction->variables == NULL && mTree->actFunction != NULL) {
        mTree->actFunction->variables = newNode;
    }
    // Jinak se klasicky prida uzel
    else
        addNode(newNode, start);
}

void addArgument(char *id, varType type) {
    BTSNode *argument = plusMalloc(sizeof(BTSNode));
    argument->key = id;
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

BTSNode *findArgument(BTSNode *start, int argNo) {
    if (start != NULL) {
        if(start->nodeType == var) {
            if(start->argNo == argNo)
                return start;
        }

        BTSNode *result;
        result = findArgument(start->lptr, argNo);
        if (result == NULL)
            result = findArgument(start->rptr, argNo);

        return result;

    } else
        return NULL;
}

/*
 * POZOR! JE TŘEBA VYUŽÍVAT SString struktury tedy postup pro uložení struktury doporučuji následující
 *
 * Provede se inicializace stringu / SString *str;
 *
 */