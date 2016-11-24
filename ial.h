/**
 * IFJ/IAL - Tabulka symbolů
 * Varianta:    b/2/I
 * Soubor:      ial.h
 * Tým:         59
 * Autoři:      Jan Hrbotický, xhrbot01@stud.fit.vutbr.cz
 *              Dominik Skála, xskala11@stud.fit.vutbr.cz
 *              Milan Hruban, xhruba08@stud.fit.vutbr.cz
 *              Martin Hons, xhonsm00@stud.fit.vutbr.cz
 *              David Hél, xhelda00@stud.fit.vutbr.cz
 */



#ifndef IFJ_59_TABLE_H_
#define IFJ_59_TABLE_H_

#include "expressions.h"
#include "typedef.h"

/*
 * Structures
 */



/*
 * PROTOTYPES
 */

/*
 * IAL FUNKCE!
 */

void initMismatchTable(mismatchTable *);
void disposeMismatchTable(mismatchTable *);
int findChar(mismatchTable *, char c);
void updateShift(mismatchTable *, char c, int shiftValue);
void insertNext(mismatchTable *, char c, int shiftValue);


int find(String str, String search);

/*
 * heapsort
 * @param str string (pole charu), kazdy znak stringu je razen dle ordinalni hodnoty vzestupne
 */
String sort(String str);

/*
 * pomocne fce pro sort
 */

/*
 * Funkce kontroluje delitelnost dvema, pokud prvek neni delitelny dvema, pricte mu jednicku.
 * Funkce slouzi k zjednoduseni vypoctu pozice prvku v repairHeap fci
 * @param i vstupni parametr
 */
int makeEven(int i);

/*
 * Funkce provadi vymenu hodnot a a b
 * @param *a prvek a, pres ktery vratime hodnotu b
 * @param *b prvek b, pres ktery vratime hodnotu a
 */
void swap(char *a, char *b);

/*
 * Funkce ziska z argumentu str string, ktery pote zpracuje za ucelem upravy haldy na spravny format
 * @param str string se kterym se pracuje
 */
String repairHeap(String str);

// FUNKCE NAD BINÁRNÍM STROMEM

/*
 * Funkce inicializuje binární strom
 */
void initTree(mainTree *tree);

/*
 * Funkce prohledá binární strom a najde příslušný uzel
 */
BTSNode *searchForNode(tableName key, NodeType nodeType, BTSNode *start);

/*
 * Funkce přidá nový uzel do BS
 */
void addNode(BTSNode *newItem, BTSNode *start);

/*
 * Funkce vytvoří nový uzel, inicializuje ho a přidá ho do stromu
 */
void createNewNode(char *id, NodeType nodeType, varType variableType, int status);


/*
 * Funkce vytvoří argument a přidá ho k příslušné funkci
 */
void addArgument(char *id, varType type);

/*
 * Funkce nalezne argument ve funkci podle jeho pořadí
 */
BTSNode *findArgument(BTSNode *start, int argNo);
#endif
