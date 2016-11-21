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
#include <stdlib.h>

/*
 * Structures
 */


/*
 * Struktura polozky mismatch tabulky
 */

typedef struct mmtItem{
	char c;
	int shiftValue;
	struct mmtItem *next;
} *mismatchTableItem;

/*
 * Jednosmerny seznam polozek mmtItem
 */

typedef struct {
	mismatchTableItem First;
	mismatchTableItem Act;
} mismatchTable;

void initMismatchTable(mismatchTable *);
void disposeMismatchTable(mismatchTable *);
void insertFirstMismatch(mismatchTable *, char c, int shiftValue);
int findChar(mismatchTable *, char c);
void updateShift(mismatchTable *, char c, int shiftValue);
void insertNext(mismatchTable *, char c, int shiftValue);


// Klic binarniho vyhledavani
typedef char *tableName;

typedef enum{
    var,
    function,
    class,
} NodeType;

//Vycet moznych typu
typedef enum {
    var_int,
    var_double,
    var_string,
} varType;

// Hodnota promenne
union {
    int intValue;
    double doubleValue;
    char *stringValue;
} varValue;

//Struktura tabulky symbolu
typedef struct tableSymbolVariable {
    varType type; // Promenna= typ promenne, Funkce= Typ navratove hodnoty, Class=nic
    varValue value; // Promenna= hodnota promenne, Funkce= vyuzijeme int hodnotu a do ni vlozime pocet argumentu, class= nic

} tabSymbol, *tabSymbolPtr;


//Struktura uzlu binarniho stromu
typedef struct tBTSNode {
    tableName key; // Klíč (název proměnné, třídy, funkce)
    NodeType nodeType; // Typ uzlu (proměnná, funkce, třída)

    //Struktura, kde se využívá vždy jen jeden prvek
    union {
        struct tBTSNode *functions; // Odkaz na funkce třídy
        int argNo; // Číslo argumentu funkce
} tBTSNode;

    tabSymbol data; // Data
	int inc;

    struct tBTSNode *variables; // Odkaz na proměnné třídy nebo funkce

    struct tBTSNode *lptr; // Pointer na levý podstrom
    struct tBTSNode *rptr; // Pointer na pravý podstrom
} BTSNode, *tBTSNodePtr;

// Struktura stromu
typedef struct {
    BTSNode *root;
    BTSNode *actClass;
    BTSNode *actFunction;
} mainTree;

/*
 * PROTOTYPES
 */

/*
 * IAL FUNKCE!
 */
int find(SString *str, SString *search);

/*
 * heapsort
 * @param str string (pole charu), kazdy znak stringu je razen dle ordinalni hodnoty vzestupne
 */
SString sort(SString *str);

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
char swap(char *a, char *b);

/*
 * Funkce ziska z argumentu str string, ktery pote zpracuje za ucelem upravy haldy na spravny format
 * @param str string se kterym se pracuje
 */
SString repairHeap(SString *str);

// FUNKCE NAD BINÁRNÍM STROMEM

/*
 * Funkce inicializuje binární strom
 */
void initTree(mainTree *tree);

/*
 * Funkce prohledá binární strom a najde příslušný uzel
 */
BTSNode searchForNode(tableName key, NodeType nodeType, BTSNode *start);

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
tNode *findArgument(BTSNode *start, int argNo);
#endif
