/**
 * IFJ/IAL - Typedef
 * Varianta:    b/2/I
 * Soubor:       typedef.h
 * Tým:         59
 * Autoři:      Jan Hrbotický, xhrbot01@stud.fit.vutbr.cz
 *              Dominik Skála, xskala11@stud.fit.vutbr.cz
 *              Milan Hruban, xhruba08@stud.fit.vutbr.cz
 *              Martin Hons, xhonsm00@stud.fit.vutbr.cz
 *              David Hél, xhelda00@stud.fit.vutbr.cz
 */


/*
 * Struktura typů tokenů
 */

#ifndef TYPEDEF
#define TYPEDEF

#define TRUE 1
#define FALSE 0 // jen pro poradek, aby tu ta druha hodnota byla, hh



typedef enum {  
/*****TYPY TOKEN� POU��VAN� VE V�RAZECH********/
	// Z�vorky
	t_bracket_l,        // (
	t_bracket_r,        // )

	// Oper�tory
	t_div,              // /
	t_multi,            // *    
	t_plus,             // +
	t_minus,            // - 

	// Porovn�vac� oper�tory
	t_comparasion,      // ==
	t_comparasion_ne,   // !=
	t_greater,          // >
	t_less,             // <
	t_less_eq,          // <=
	t_greater_eq,       // >=

	// Negace
	t_excl_mark,        // !

	// Odd�lova�e
	
	t_semicolon,        // ;  

	// Identifik�tory
	t_simple_ident,     // 15
	t_complete_ident,   // 16    

	// Datov� typy
	t_int,              // 17
	t_double,           // 18
	t_double_e,         // 19
	t_string,           // 20
	/**********************************************/

	//Error status
	t_error, 

	// Operators
	t_assignment, 

	//Brackets
	t_brace_l, // {
	t_brace_r, // }
	t_sq_bracket_l,     // [
	t_sq_bracket_r,     // ],  

	// Comments
	t_simple_comment, 
	t_block_comment_start,
	t_block_comment_end,   

	// Other
	t_eof,
    t_comma,            // ,

	// Keywords
	t_kw_class,
	t_kw_static,
	t_kw_boolean,
	t_kw_double,
	t_kw_int,
	t_kw_string,
	t_kw_void,
	t_kw_while,
	t_kw_for,
	t_kw_break,
	t_kw_return,
	t_kw_continue,
	t_kw_do,
	t_kw_if,
	t_kw_else,
	t_kw_true,
	t_kw_false,

	// Integrated functions for strings
	t_find,
	t_sort,
	t_length,
	t_substring,
	t_compare,

	// Integrated functions for input and output
	t_read_int,
	t_read_double,
	t_read_string,
	t_print
} tokenType;

/*
 * Datovy typ string
 */
typedef char* String;

/*
 * Struktura tokenu
 */


typedef struct{
	tokenType type;  // Typ tokenu
	String attribute;
	unsigned int length; // Délka, počet charů
	unsigned int allocated; // Status, jestli byl alokován
	char data[]; // Data, která obshahuje
} tToken;


/*
 * Typy výrazů 
 */
typedef enum {
	expCond,
	expArg,
	expAssign,
	expVoid
} tExpType;



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
	var_init = 10,
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
	NodeType nodeType; // Typ uzlu (proměnná, funkce, třída, argumenty)

	//Struktura, kde se využívá vždy jen jeden prvek, pokud se jedna o třídu, využije se první prvek, pokud u proměnnou, která je argumentem funkce, pak se využije druhá
	struct tBTSNode *functions; // Odkaz na funkce třídy
	int argNo; // Číslo argumentu funkce

	tabSymbol data; // Data, obsahuje strukturu tabSymbol (Struktura tabulky symbolu hned nad touto strukturou)
	int inc; // Označení, jestli byla proměnná inicializovaná

	struct tBTSNode *variables; // Odkaz na proměnné třídy nebo funkce


	struct tBTSNode *lptr; // Pointer na levý podstrom
	struct tBTSNode *rptr; // Pointer na pravý podstrom
	
	struct instructionStack *iStack;
} BTSNode, *tBTSNodePtr;

// Struktura stromu
typedef struct MTree{
	BTSNode *root; // Kořen stromu
	BTSNode *actClass; // Jaká třída je právě aktivní, resp. v jaké třídě se nacházíme
	BTSNode *actFunction; // Jaká funkce je aktivní, resp. v jaké funkci se nacházíme
} mainTree;

typedef enum {
	// BUILT-IN FUNCTIONS
	insIfj16readInt,
	insIfj16readDouble,
	insIfj16readString,
	insIfj16lenght,
	insIfj16substr,
	insIfj16compare,
	insIfj16find,
	insIfj16sort,
	insIfj16print,
	//
	// MATH
	insPlus, // Sčítání
	insMinus, // Odečítání
	insMux, // Násobení
	insDiv, // Dělení
	//
	//COMPARE
	insEqual, // Je rovno
	insNotEqual, // Neni rovno
	insLess, // Je mensi
	insLessOrEqual, // Je mensi nebo rovno
	insGreater, // Je vetsi
	insGreaterOrEqual, // Je vetsi nebo rovno
	insAssignment,
	insFunctionCall,
	//Condition
	insCond,
	insIf,
	insIfEnd,
	insElse,
	insCondEnd,
    //WHILE
    insWhile,
    insEndWhile,
}InstrType;

typedef struct Instr {
	BTSNode *Id1; // Adresa prvního operandu
	BTSNode *Id2; // Adresa druhého operandu
	BTSNode *Id3; // Adresa, kam se uloží výsledek operace
	InstrType type;
}Instr;

typedef struct instructionStack{
	Instr **dataInstr;
	int count;
	int alloc;
}instrStack;

#endif
