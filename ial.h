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
 * Jednosmerny seznam polozek mmtItem alias mismatch tabulka
 */

typedef struct {
	mismatchTableItem First;
	mismatchTableItem Act;
} mismatchTable;

void initMismatchTable(mismatchTable *);
void disposeMismatchTable(mismatchTable *);
int findChar(mismatchTable *, char c);
void updateShift(mismatchTable *, char c, int shiftValue);
void insertNext(mismatchTable *, char c, int shiftValue);


// Klic binarniho vyhledavani (název funkce, třídy nebo proměnné)
typedef char *tableName;

// Typ uzlu (ve stromu pozname, jestli se jedna o funkci, třídu nebo proměnnou
typedef enum{
    var,
    function,
    class,
} NodeType;

//Vycet moznych typu (pouze u proměnných a funkcí). U proměnných je to jejich typ, u funkcí značí jejich návratový typ
typedef enum {
    var_int,
    var_double,
    var_string,
    var_void,
} varType;

// Hodnota promenne, union zajišťuje, že v paměti zabírá místo pouze největší hodnota z nich
union varValue{
    int intValue;
    double doubleValue;
    char *stringValue;
};

//Struktura tabulky symbolu
typedef struct tableSymbolVariable {
    varType type; // U promenne= typ promenne | U funkce= Typ navratove hodnoty | U tridy=nic, NULL
    union varValue value; // U promenne- hodnota promenne | U trid a funkci tuto promennou nepouzivame NULL
} tabSymbol, *tabSymbolPtr;


//Struktura uzlu binarniho stromu
typedef struct tBTSNode {
    tableName key; // Klíč (název proměnné, třídy, funkce)
    NodeType nodeType; // Typ uzlu (proměnná, funkce, třída)

    //Struktura, kde se využívá vždy jen jeden prvek, pokud se jedna o třídu, využije se první prvek, pokud u proměnnou, která je argumentem funkce, pak se využije druhá
    struct tBTSNode *functions; // Odkaz na funkce třídy
    int argNo; // Číslo argumentu funkce

    tabSymbol data; // Data, obsahuje strukturu tabSymbol (Struktura tabulky symbolu hned nad touto strukturou)
	int inc; // Označení, jestli byla proměnná inicializovaná

    struct tBTSNode *variables; // Odkaz na proměnné třídy nebo funkce

    struct tBTSNode *lptr; // Pointer na levý podstrom
    struct tBTSNode *rptr; // Pointer na pravý podstrom
} BTSNode, *tBTSNodePtr;

// Struktura stromu
typedef struct {
    BTSNode *root; // Kořen stromu
    BTSNode *actClass; // Jaká třída je právě aktivní, resp. v jaké třídě se nacházíme
    BTSNode *actFunction; // Jaká funkce je aktivní, resp. v jaké funkci se nacházíme
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
void swap(char *a, char *b);

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
