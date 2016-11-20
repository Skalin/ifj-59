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

mismatchTable initMismatchTable(mismatchTable);
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

/*
 * Obě funkce volají příslušné fce binárního stromu na inicializaci, případně odstranění ze stromu
 */
void TSInit(void);
void TSDispose(void);

/*
 * Funkce vloží symbol do tabulky
 * @param symbol Symbol, který chceme vložit
 * @return Navrací pointer na danou vloženou položku
 */
tabSymbol *TSInsert(tabSymbol symbol);
/*
 * Funkce vloží data příslušného datového typu do tabulky
 * @param symbol data Data, která chceme vložit
 * @return Navrací pointer na danou položku
 */
tabSymbol *TSInsertInt(tableName name, int data);
tabSymbol *TSInsertDouble(tableName name, double data);
tabSymbol *TSInsertString(tableName name, char *data);
tabSymbol *TSInsertSimpleIdent(tableName name, char *data);
tabSymbol *TSInsertCompleteIdent(tableName name, char *data);
tabSymbol TSInsertFunction(tableName name, char *data);
tabSymbol TSInsertClass(tableName name, char *data);

/*
 * Funkce inicializuje symbol
 * @param symbol Symbol, který chceme inicializovat
 * @return
 */
void TSInitSymbol (tabSymbol symbol);
/*
 * Funkce najde v daném stromu požadovanou položku
 * @param root Kořen, ve kterém hledáme
 * @param key Klíč, podle kterého hledáme
 * @return Navrací danou položku, případně NULL pokud ji nenajde
 */
tBTSNodePtr BTSSearch (tBTSNodePtr root, tableName key);

/*
 * Funkce vloží symbol do BS
 * @param root Pointer na BS
 * @param key klíč, podle kterého hledáme položku na případné přepsání
 * @param symbol symbol, který chceme vložit
 * @return Navrací pointer na danou vloženou položku
 */
static tBTSNodePtr BTSInsert(tBTSNodePtr *root, tableName key, tabSymbol symbol);
/*
 * Funkce smaže BS daného kořenu
 * @param symbol kořen, který chceme smazat
 * @return
 */
static void BTSDispose(tBTSNodePtr *root);
#endif
