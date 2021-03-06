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

#include <string.h>
#include <malloc.h>
#include "typedef.h"
#include "ial.h"
#include "error_handler.h"
#include "garbage_collector.h"
#include "expressions.h"
#include "instrstack.h"

mainTree mTree;

// find a sort dle zadani

// pomocne fce pro find, tedy funkce pro MismatchTabulku

void initMismatchTable(mismatchTable *Table) {
    Table->First = NULL;
    Table->Act = NULL;
}

void disposeMismatchTable(mismatchTable *Table) {

    mismatchTableItem pom = NULL;

    while (Table->First != NULL) {
        Table->Act = Table->First;
        Table->First = Table->First->next;
        pom = Table->Act;
        plusFree(pom);
    }

    Table->Act = NULL;
}

void insertNext(mismatchTable *Table, char c, int shiftValue) {

    mismatchTableItem pom = plusMalloc(sizeof(mismatchTableItem));

    if (pom != NULL) {
        if (Table->First == NULL) {
            pom->c = c;
            pom->shiftValue = shiftValue;
            pom->next = NULL;
            Table->First = pom;
        } else {
            pom->next = Table->First;
            pom->c = c;
            pom->shiftValue = shiftValue;
            Table->First = pom;
        }
    } else {
        throwException(99, 0, 0);
    }
}

int findChar(mismatchTable *Table, char c) {
    int i = -1;
    Table->Act = Table->First;
    while (Table->Act != NULL) {
        if (c == Table->Act->c) {
            i++;
            return (i);
        }
        Table->Act = Table->Act->next;
    }
    return i;
}

int getShiftValue(mismatchTable *Table, char c) {

    Table->Act = Table->First;

    while (Table->Act->c != c) {
        Table->Act = Table->Act->next;
    }
    return Table->Act->shiftValue;
}

void updateShift(mismatchTable *Table, char c, int shiftValue) {

    Table->Act = Table->First;

    while (Table->Act->c != c) {
        Table->Act = Table->Act->next;
    }
    Table->Act->shiftValue = shiftValue;

}

// samotny find
int find(char str[], char search[]) {

    int i = 0;
    char item;
    int found = -1;
    int others = strLength(search);
    int stop = -1; // zarazka
    int shiftValue = others; // prvotni nastaveni shiftu

    if (others == 0) {
        found++;
        return found;
    } else if (strLength(str) < strLength(search)) {
        return found;
    }

    mismatchTable Table;
    initMismatchTable(&Table);
    //printf("mismatch table inicializovana\n");
    // cyklus naplni mismatch Tabulku znaky ze stringu "search"
    while (i < strLength(search)) {
        item = search[i];
        //printf("%d znak: %c\n", i, item);

        //printf("Je novy znak v tabulce? -1 = ne: %d\n", findChar(&Table, item));
        if (findChar(&Table, item) == -1) {
            if (search[i+1] != '\0') { // pokud toto neni posledni prvek
                insertNext(&(Table), item, strLength(search) - i - 1);
            } else { // jinak nastavime shift posledniho prvku dle boyer-moore algoritmu
                insertNext(&(Table), item, others);
            }
            //printf("Je znak v tabulce na pozici 0? Pokud ano, je tam: %d\n", findChar(&Table, item));
        } else {
            updateShift(&(Table), item, (strLength(search)-i-1));
        }
        i++;
    }


    //printf("Tabulka byla naplnena, nyni provedeme vyhledavani\n");
    while ((found == -1) && (stop < strLength(str))) { // dokud neni string nalezen nebo neni konec stringu nebo neni eof, hledam
        stop += shiftValue;
        //printf("Hodnota zarazky? %d\n", stop);

        for (i = 0; i < others; i++) {
            if (str[stop-i] == search[others-i-1]) {
                if (str[stop-others+1] == search[0]) {
                    found = stop-others+1;
                    break;
                }
            } else {
                if (findChar(&Table, str[stop-i]) == -1) {
                    shiftValue = others;
                } else {
                    shiftValue = getShiftValue(&(Table), str[stop-i]);
                }
                break;
            }
        }

    }

    disposeMismatchTable(&Table);

    return found;

}

// swap pro heapsort
void swap(char *a, char *b) {
    //printf("Bude prohozen znak %c a %c \n", *a, *b);
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
char *repairHeap(char str[], int length) {

    int i = 0, isBiggestNotAtTop = 1;

    char biggestChar = '\0';
    int strlength = length;

    while (strlength) {
        if (str[i] > biggestChar) {
            biggestChar = str[i];
        }
        i++;
        strlength--;
    }

    for (i = length-1; i >= 0; i--) {


        isBiggestNotAtTop = 0;
        //printf("Slovo str nyni vypada takto: %s\n", str);
        //printf("Znak na pozici %d je %c\n",i,str[i]);

        if (biggestChar == str[0]) {
            return str;
        }


        if ((i % 2) == 0) {
            if ((str[i] > str[(makeEven(i)/2)-1]) && (str[i-1] > str[(makeEven(i)/2)-1])) {
                isBiggestNotAtTop = 1;
                if (str[i] >= str[i-1]) {
                    swap(&str[i], &str[(makeEven(i)/2)-1]);
                } else {
                    swap(&str[i-1], &str[(makeEven(i)/2)-1]);
                }
                //printf("SUDE I: I je: %d a zesudele I je: %d\n", i, makeEven(i));
            }
            if (str[i] > str[(makeEven(i)/2)-1]) {
                isBiggestNotAtTop = 1;
                swap(&str[i], &str[(makeEven(i)/2)-1]);
                //printf("SUDE II: I je: %d a zesudele I je: %d\n", i, makeEven(i));
            }
        } else {
            if (str[i] > str[(makeEven(i)/2)-1]) {
                isBiggestNotAtTop = 1;
                swap(&str[i], &str[(makeEven(i)/2)-1]);
            }
            //printf("LICHE I: I je: %d a zesudele I je: %d\n", i, makeEven(i));
        }
    }

    if (isBiggestNotAtTop == 1)
        repairHeap(str, length);

    return str;
}


// samotny heapsort
char *sort(char str[]) {
    char *helpString = str;

    int length = strLength(helpString);
    while (length) {

        repairHeap(helpString, length);

        swap(&helpString[0], &helpString[length-1]);

        length--;
    }

    return helpString;
}



//Uzel BT
tBTSNodePtr symbolTable;


int argNo = 0;



void initTree(mainTree *tree) {
    tree = NULL;
}

BTSNode *searchForNode(tableName key, NodeType nodeType, BTSNode *start) {
    if(mTree.root == NULL) {
        return NULL;
    } else {
        if (start == NULL)
            start = mTree.root;

        if (start != NULL) {

            // Pokud nalezneme klic
            if ((strcmp(key, start->key)) == 0) {
                // Pokud je to typ ktery jsme hledali, vratime ho
                if (start->nodeType == nodeType)
                    return start;
            }
                // Pokud mame hledat v pravem podstromu
            else if (strcmp(key, start->key) > 0) {
                return (start->rptr == NULL ? NULL : searchForNode(key, nodeType, start->rptr));
            }
                // Pokud mame hledat v levem podstromu
            else if (strcmp(key, start->key) < 0){
                return start->lptr == NULL ? NULL : searchForNode(key, nodeType, start->lptr);

            }
                // V ostatnich pripadech (Chuck norris on STDin?) se jedna o chybu
            else
                throwException(99, 0, 0);
        }
    }
    return NULL;
}


void addNode(BTSNode *newItem, BTSNode *start) {
    if(start != NULL) {

        if (strcmp(newItem->key, start->key) > 0) {

            // Pokud nemame uzel kam vlozit
            if (start->rptr != NULL) {
                addNode(newItem, start->rptr);
            }
                // Pokud ho mame kam vlozit
            else
                start->rptr = newItem;
            if (newItem->nodeType == function)
                mTree.actFunction = newItem;
            if (newItem->nodeType == class)
                mTree.actClass = newItem;

        } else if (strcmp(newItem->key, start->key) < 0) {
            // Pokud nemame uzel kam vlozit
            if (start->lptr != NULL) {
                addNode(newItem, start->lptr);
            }
                // Pokud ho mame kam vlozit
            else
                start->lptr = newItem;
            if (newItem->nodeType == function)
                mTree.actFunction = newItem;
            if (newItem->nodeType == class)
                mTree.actClass = newItem;

            // If there is anything else throw error
        } else {
            throwException(99, 0, 0);
        }
    } else {
        throwException(99, 0, 0);
    }
}

void initNode(BTSNode *node) {
    node->key = NULL;
    node->nodeType = var;
    node->argNo = 0;
    node->data.value.intValue = 0;
    node->data.value.doubleValue = 0.0;
    node->data.value.stringValue = "";
    node->data.type = var_null;
    node->inc = 0;
    node->functions = NULL;
    node->iStack = NULL;
    node->lptr = NULL;
    node->rptr = NULL;
    node->variables = NULL;
}

BTSNode *createNewNode(char *id, NodeType nodeType, varType variableType, int status, int inc) {
    if(argNo != 0)
        argNo = 0;
// a odkud tady vstupuje tem mtree
    // Inicializace noveho uzlu
    BTSNode *newNode;
    newNode = plusMalloc(sizeof(BTSNode));
    initNode(newNode);
    newNode->key = id;
    newNode->nodeType = nodeType;
    newNode->inc = inc;

    //printf("jsem po initu zakladnich hodnot\n");

    // Urceni zacatku podle typu uzlu
    BTSNode *start = plusMalloc(sizeof(BTSNode));
    start = NULL;

    switch(newNode->nodeType) {
        case var:
            newNode->data.type = variableType;
            newNode->variables = NULL; // Neni potrebne u promenne
            //printf("Datatype a variables jsou ulozeny\n");
            if (status) {
                //printf("pred nastavenim startu");
                start = mTree.actClass->variables;
            } else {
                start = mTree.actFunction->variables;
            }
            //printf("Jsem po dokonceni ukladani mTree do startu\n");
            break;
        case function:
            newNode->data.type = variableType; // Nastavime navratovou hodnotu funkce
            newNode->variables = NULL;
            start = mTree.actClass->functions;
            break;
        case class:
            newNode->functions = NULL;
            newNode->variables = NULL;
            start = mTree.root;
            break;
        case temp:
            newNode->data.type = variableType;
            newNode->variables = NULL; // Neni potrebne u promenne
            if (status) {
                start = mTree.actClass->variables;
            } else {
                start = mTree.actFunction->variables;
            }
            //printf("Jsem po dokonceni ukladani mTree do startu\n");
            break;
    }

    //printf("jsem za switchem\n");

    if (newNode->nodeType == class && mTree.root == NULL) { // Pokud neexistuje korenovy uzel a jedna se o classu
        //printf("Nepridal jsem nodu, koncim na sigsegv\n");
        mTree.root = newNode;
        mTree.actClass = newNode;
    } else if (newNode->nodeType == function) { // Pokud ve tride neexistuji funkce
        //printf("Nepridal jsem nodu, koncim na sigsegv\n");
        if (mTree.actClass->functions == NULL){
            mTree.actClass->functions = newNode;
        }
        mTree.actFunction = newNode;
        instrStack stc;
        instrStackInit(&stc);
        mTree.actFunction->iStack = &stc;
    } else if (newNode->nodeType == var && mTree.actClass->variables == NULL && status == 1) { // Pokud ve tride neexistuji zadne staticke promenne
        //printf("Nepridal jsem nodu, koncim na sigsegv\n");
        mTree.actClass->variables = newNode;
    } else if (newNode->nodeType == var && mTree.actFunction != NULL && mTree.actFunction->variables == NULL && !status) { // Pokud ve funkci neexistuji zadne promenne
        //printf("Nepridal jsem nodu, koncim na sigsegv\n");
        mTree.actFunction->variables = newNode;
   // } else if (newNode->nodeType == class){
   //     mTree.actClass = newNode;
    } else { // Jinak se klasicky prida uzel
        //printf("Nepridal jsem nodu, koncim na sigsegv\n");
        addNode(newNode, start);
    }

    //printf("Jsem za uzlem\n");
    return newNode;
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
    mTree.actFunction->data.value.intValue = argNo;

    if (mTree.actFunction->variables != NULL)
        addNode(argument, mTree.actFunction->variables);
    else
        mTree.actFunction->variables = argument;
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


void Print_tree2(BTSNode *TempTree, char* sufix, char fromdir)
/* vykresli sktrukturu binarniho stromu */

{
    if (TempTree != NULL)
    {
        char* suf2 = (char*) malloc(strlen(sufix) + 4);
        strcpy(suf2, sufix);
        if (fromdir == 'L')
        {
            suf2 = strcat(suf2, "  |");
            printf("%s\n", suf2);
        }
        else
            suf2 = strcat(suf2, "   ");
        Print_tree2(TempTree->rptr, suf2, 'R');
        printf("%s  +-[%c,%s]\n", sufix, TempTree->key, nodePrint(TempTree));
        strcpy(suf2, sufix);
        if (fromdir == 'R')
            suf2 = strcat(suf2, "  |");
        else
            suf2 = strcat(suf2, "   ");
        Print_tree2(TempTree->lptr, suf2, 'L');
        if (fromdir == 'R') printf("%s\n", suf2);
        free(suf2);
    }
}

void Print_tree(BTSNode *TempTree)
{
    printf("Struktura binarniho stromu:\n");
    printf("\n");
    if (TempTree != NULL)
        Print_tree2(TempTree, "", 'X');
    else
        printf("strom je prazdny\n");
    printf("\n");
    printf("=================================================\n");
}
