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

/*
 * Structures
 */

typedef struct {
	char c;
	int shiftValue;
} mismatchTable;

// Klic binarniho vyhledavani
typedef char *tableName;

//Vycet moznych typu
typedef enum {
    var_int,
    var_double,
    var_string,
    var_simpleident,
    var_completeident,
} varType;

// Hodnota promenne
typedef union {
    int intValue;
    double doubleValue;
    char *stringValue;
    char *simpleIdentValue;
    char *completeIdentValue;
}varValue;

//Struktura tabulky symbolu
typedef struct tableSymbolVariable {
    int inc; //Byl inicializovan
    tableName name; //Nazev symbolu
    varType type; // Typ promenne
    varValue value; // Hodnota promenne
}tabSymbol, *tabSymbolPtr;


//Struktura uzlu binarniho stromu
typedef struct tBTSNode {
    tableName key; // Klíč
    tabSymbol data; // Data
    struct tBTSNode *lptr; // Pointer na levý podstrom
    struct tBTSNode *rptr; // Pointer na pravý podstrom
}*tBTSNodePtr;

//Externi promenna tabulky symbolu
extern tBTSNodePtr symbolTable;

/*
 * PROTOTYPES
 */

/*
 * IAL FUNKCE!
 */
int find(SStr *str, SStr *search);

/*
 * IAL FUNKCE!
 */
String sort(SStr *str);

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
