/**
 * IFJ/IAL - Lexikální analyzátor
 * Varianta:    b/2/I
 * Soubor:       lexical_analyzer.h
 * Tým:         59
 * Autoři:      Jan Hrbotický, xhrbot01@stud.fit.vutbr.cz
 *              Dominik Skála, xskala11@stud.fit.vutbr.cz
 *              Milan Hruban, xhruba08@stud.fit.vutbr.cz
 *              Martin Hons, xhonsm00@stud.fit.vutbr.cz
 *              David Hél, xhelda00@stud.fit.vutbr.cz
 */
#ifndef LEXICAL_ANALYZER
#define LEXICAL_ANALYZER

#include "typedef.h"

/*
 * Definice
 */

#define NUMBER_OF_KEY_WORDS 17
#define NUMBER_OF_RESERVED_WORDS

// pole stavu pro debug lexu
static const char *tokenTypeString[] = {
		"t_bracket_l","t_bracket_r","t_div","t_multi","t_plus","t_minus","t_comparasion","t_comparasion_ne","t_greater","t_less","t_less_eq","t_greater_eq","t_excl_mark","t_semicolon","t_simple_ident","t_complete_ident","t_int","t_double","t_double_e","t_string","t_error","t_assignment","t_brace_l","t_brace_r","t_sq_bracket_l","t_sq_bracket_r","t_simple_comment","t_block_comment_start","t_block_comment_end","t_eof","t_comma","t_kw_class","t_kw_static","t_kw_boolean","t_kw_double","t_kw_int","t_kw_string","t_kw_void","t_kw_while","t_kw_for","t_kw_break","t_kw_return","t_kw_continue","t_kw_do","t_kw_if","t_kw_else","t_kw_true","t_kw_false","t_find","t_sort","t_length","t_substring","t_compare","t_read_int","t_read_double","t_read_string","t_print"
};

/*
 * Jednotlivé stavy automatu
 */
typedef enum {
    LA_START,   //Startovací stav
    LA_KEYWORD, // Klíčové slovo
    LA_INT,     //Int
    LA_DOT_DOUBLE, //Int s tečkou
    LA_DOUBLE, //Double
    LA_DOUBLE_pE, // Double s 'e'
    LA_DOUBLE_E_SIGN, //Znaménkové e
    LA_DOUBLE_E, //Konečné double
    LA_SIMPLE_IDENT, // jednoduchý indentifikátor
    LA_COMPLETE_IDENT, // Kompletní identifikátor
    LA_STRING_PREP, // Začátek a tělo stringu
    LA_STRING, // Kompletní string
    LA_EOF, // EOF
    LA_DIV, // Dělení '/'
    LA_SIMPLE_COMMENT, // Jednořádkový komentář '//'
    LA_BLOCK_COMMENT_END, // Konec blokového komentáře '*/'
    LA_MULTI, // Násobení '*'
    LA_BLOCK_COMMENT_START, // Začátek blokového komentáře '/*'
    LA_PLUS, // Plus '+'
    LA_MINUS, // Minus '-'
    LA_SQ_BRACKET_L, // Hranatá závorka, levá '['
    LA_SQ_BRACKET_R, // Hranatá závorka, pravá ']'
    LA_BRACKET_L, // Levá závorka '('
    LA_BRACKET_R, // Pravá závorka ')'
    LA_BRACE_L, // Levá složená závorka '{'
    LA_BRACE_R, // Prava slozena zavorka '}'
    LA_GREATER, // Větší než '>'
    LA_GREATER_EQ, // Vetsi rovno '>='
    LA_LESS, // Mensi '<'
    LA_LESS_EQ, // Mensi rovno '<='
    LA_ASSIGNMENT, // Prirazeni '='
    LA_COMPARASION, // Porovnani '=='
    LA_EXCL_MARK, // Vykricnik '!'
    LA_COMPARASION_NE, // Nerovna se '!='
    LA_SEMICOLON, // Strednik ';'
    LA_BACKSLASH, // Backslash '\'
    LA_DOUBLE_BACKSLASH, // Escape baskslashe '\\'
    LA_TAB, // Escape odtabování '\t'
	LA_NEW_LINE, // Escape noveho radku '\n'
    LA_QUOTE, // Escape uvozovek '"'
    LA_OCT1, // První znak octanového čísla
    LA_OCT2_Z,  // Druhý znak octalového čísla (nulový)
    LA_OCT2_NZ, // Druhý znak octalového čísla (nenulový)
    // Keywords
	LA_KW_BOOLEAN,
	LA_KW_BREAK,
	LA_KW_CLASS,
	LA_KW_CONTINUE,
	LA_KW_DO,
	LA_KW_DOUBLE,
	LA_KW_ELSE,
	LA_KW_FALSE,
	LA_KW_FOR,
	LA_KW_IF,
	LA_KW_INT,
	LA_KW_RETURN,
	LA_KW_STRING,
	LA_KW_STATIC,
	LA_KW_TRUE,
	LA_KW_VOID,
	LA_KW_WHILE,
} tStatus;


/* Globální token */
extern tToken token;

/*
 * Získá token z analyzátoru a vrátí jej
 * @param token
 * @return jeden načtený token z analyzátoru
 */
tToken * getToken();

/*
 * Inicializuje token a vrací pointer na token
 * @param token
 * @return ukazatel na inicializovaný token
 */
tToken * initToken();

/*
 * Ruší již předem vytvořený token
 * @param token
 */
void destroyToken(tToken * token);

/*
 * Funkce aktualizuje hodnotu tokenu na hodnotu z parametru string
 */
tToken * updateToken(tToken * token, char *string);

/*
 * Projde pole keyword a přiřadí korektně k tokenu "id" z pole keyword
 * @param token
 */
void keywordCheckToken(tToken * token);

/*
 * Naplní type tokenu
 * @param type
 */
void fillToken(tToken * token, tokenType type);

/*
 * Naplni obsah bufferu predanym tokenem
 * @param token
 */
void tokenReturnToken(tToken * token);

/*
 * Funkce ziska z LA trimistne octalove cislo a prevede jej na char, ktery vrati
 * @param octalArray
 */
char octToAscii(char *octalArray);

/*
 * Funkce tiskne typ tokenu
 * @param token, jehoz typ se vytiskne
 */
void printToken(tToken *token);

#endif
