/**
 * IFJ/IAL - Lexikální analyzátor
 * Varianta:    b/2/I
 * Soubor:      table.c
 * Tým:         59
 * Autoři:      Jan Hrbotický, xhrbot01@stud.fit.vutbr.cz
 *              Dominik Skála, xskala11@stud.fit.vutbr.cz
 *              Milan Hruban, xhruba08@stud.fit.vutbr.cz
 *              Martin Hons, xhonsm00@stud.fit.vutbr.cz
 *              David Hél, xhelda00@stud.fit.vutbr.cz
 */
#include "ial.h"
#include "garbage_collector.h"
#include <string.h>
//Uzel BT
tBTSNodePtr symbolTable;


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

void TSInitSymbol (tabSymbol symbol) {
    //Pokud máme co inicializovat
    if (symbol != NULL) {
        //Inicializujeme data
        symbol.name= NULL;
        symbol.type= NULL;
        symbol.inc= 1;
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
            (*koren)->data = symbol;
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