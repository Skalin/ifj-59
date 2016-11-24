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

#include <stdio.h>

/*
 * Struktura typů tokenů
 */

#ifndef TYPEDEF
#define TYPEDEF

#define TRUE 1
#define FALSE 0 // jen pro poradek, aby tu ta druha hodnota byla, hh

typedef enum {  
/*****TYPY TOKENŮ POUŽÍVANÉ VE VÝRAZECH********/
    // Závorky
    t_bracket_l,        // (
    t_bracket_r,        // )

    // Operátory
    t_div,              // /
    t_multi,            // *    
    t_plus,             // +
    t_minus,            // - 
    
    // Porovnávací operátory
    t_comparasion,      // ==
    t_comparasion_ne,   // !=
    t_greater,          // >
    t_less,             // <
    t_less_eq,          // <=
    t_greater_eq,       // >=

    // Negace
    t_excl_mark,        // !

    // Oddělovače
    t_comma,            // ,
    t_semicolon,        // ;  
    
    // Identifikátory
    t_simple_ident,     // 15
    t_complete_ident,   // 16    
    
    // Datové typy
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
 * Struktura stringu (SString)
 */

typedef struct SStr{
	char *data;
	int length;		        // délka řetězce
	int allocatedSize;	  // alokovaná paměť
} SString;




/*
 * Struktura tokenu
 */

typedef struct {
    tokenType type;  // Typ tokenu
    SString attribute;
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
    expAssign
} tExpType;

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
    insAssignment
}InstrType;

 typedef struct Instr {
     BTSNode *Id1; // Adresa prvního operandu
     BTSNode *Id2; // Adresa druhého operandu
     BTSNode *Id3; // Adresa, kam se uloží výsledek operace
     InstrType type;
 }Instr;

typedef struct {
    Instr **dataInstr;
    int count;
    int alloc;
}instrStack;

#endif
