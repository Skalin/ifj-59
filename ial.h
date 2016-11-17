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

// Klic binarniho vyhledavani
typedef char *tableName;

typedef enum{
    var,
    function,
    class,
}NodeType;

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
}varValue;

//Struktura tabulky symbolu
typedef struct tableSymbolVariable {
    varType type; // Promenna= typ promenne, Funkce= Typ navratove hodnoty, Class=nic
    varValue value; // Promenna= hodnota promenne, Funkce= vyuzijeme int hodnotu a do ni vlozime pocet argumentu, class= nic

}tabSymbol, *tabSymbolPtr;


//Struktura uzlu binarniho stromu
typedef struct tBTSNode {
    tableName key; // Klíč (název proměnné, třídy, funkce)
    NodeType nodeType; // Typ uzlu (proměnná, funkce, třída)

    //Struktura, kde se využívá vždy jen jeden prvek
    union {
        struct tBTSNode *functions; // Odkaz na funkce třídy
        int argNo; // Číslo argumentu funkce
    };

    tabSymbol data; // Data

    struct tBTSNode *variables; // Odkaz na proměnné třídy nebo funkce

    struct tBTSNode *lptr; // Pointer na levý podstrom
    struct tBTSNode *rptr; // Pointer na pravý podstrom
}BTSNode, *tBTSNodePtr;

// Struktura stromu
typedef struct {
    BTSNode *root;
    BTSNode *actClass;
    BTSNode *actFunction;
}mainTree;

/*
 * PROTOTYPES
 */
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
