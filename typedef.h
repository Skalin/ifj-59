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

#include <stdio.h>
#include <stdlib.h>

typedef enum {
	//Error status
	t_error,

    // Date types
    t_int, 
    t_double,
    t_double_e,
    t_string,
    t_simple_ident,
    t_complete_ident,

    // Operators
    t_div, 
    t_multi,
    t_plus,
    t_minus,
    t_greater,
    t_greater_eq,
    t_less,
    t_less_eq,
    t_assignment, 
    t_comparasion,
    t_excl_mark,
    t_comparasion_ne,

    //Brackets
    t_sq_bracket_l, // [
    t_sq_bracket_r, // ]
    t_bracket_l, // (
    t_bracket_r, // )
    t_brace_l, // {
    t_brace_r, // }

    // Comments
	t_simple_comment, 
	t_block_comment_start,
	t_block_comment_end,   

	// Other
	t_semicolon,
    t_comma,
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
	t_print,
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

#endif
