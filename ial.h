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

#include "typedef.h"

/*
 * Structures
 */
// struktury presunuty do typedef.h


/*
 * PROTOTYPES
 */

/*
 * IAL FUNKCE!
 */


/*
 * Funkce provede inicializaci mismatch tabulky (tabulky neshodnych znaku) pro Boyer-Moore algoritmsu
 * @param *Table Ukazatel na inicializovanou mismatch tabulku
 */
void initMismatchTable(mismatchTable *Table);

/*
 * Funkce provede kompletni "zniceni" mismatch tabulky (tabulky neshodnych znaku) pro Boyer-Moore algoritmus
 * @param *Table Ukazatel na rusenou mismatch tabulku
 */
void disposeMismatchTable(mismatchTable *Table);

/*
 * Funkce vrati pozici na ktere je znak c v MismatchTabulce
 * @param *Table Mismatch Tabulka
 * @param * c Znak, podle ktereho hledame pozici v tabulce
 */
int findChar(mismatchTable *Table, char c);

/*
 * Funkce vrati hodnotu shiftu dle znaku, ktery tabulce predame
 * @param *Table Tabukla neshodnych znaku
 * @param c Znak, podle ktereho hledame shiftValue
 */
int getShiftValue(mismatchTable *Table, char c);

/*
 * Funkce zaktualizuje hodnotu "shiftValue" v tabulce MismatchValue, pokud jiz dany prvek obsahuje
 * @param *Table Mismatch Tabulka
 * @param c znak podle ktereho vyhledavame v tabulce
 * @param shiftValue hodnota, kterou upravime
 */
void updateShift(mismatchTable *Table, char c, int shiftValue);

/*
 * Funkce vlozi dalsi prvek do tabulky neshod (Mismatch table), prvek ma znak c a hodnotu shiftValue
 * @param *Table Tabulka mismatch hodnot
 * @param c vkladany znak
 * @param shiftValue vkladana hodnota shiftvalue
 */
void insertNext(mismatchTable *Table, char c, int shiftValue);

/*
 * Funkce provede vyhledavani stringu dle Boyer-Moore algoritmu, viz dokumentace
 * @param str String ve kterem vyhledavame
 * @param search Vyhledavane slovo
 */
int find(char str[], char search[]);

/*
 * Funkce sort, ktera za pomoci heapsort algoritmu seradi znaky ve stringu vzestupne dle ordinalni hodnoty
 * @param str String (pole charu)
 */
char *sort(char str[]);

/*
 * pomocne fce pro sort
 */

/*
 * Funkce kontroluje delitelnost dvema, pokud prvek neni delitelny dvema, pricte mu jednicku.
 * Funkce slouzi k zjednoduseni vypoctu pozice prvku v repairHeap fci
 * @param i Sudovane cislo
 */
int makeEven(int i);

/*
 * Funkce provadi vymenu hodnot a a b
 * @param *a Znak a, pres ktery vratime hodnotu b
 * @param *b Znak b, pres ktery vratime hodnotu a
 */
void swap(char *a, char *b);

/*
 * Funkce ziska z argumentu str string, ktery pote zpracuje za ucelem upravy haldy na spravny format
 * @param str string se kterym se pracuje
 */
char *repairHeap(char str[], int length);

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
