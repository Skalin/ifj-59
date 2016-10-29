/*
 * IFJ/IAL - Lexikální analyzátor
 * Varianta:    b/2/I
 * Subor:       lexical_analyzer.h
 * Tým:         59
 * Autoři:      Jan Hrbotický, xhrbot01@stud.fit.vutbr.cz
 *              Dominik Skála, xskala11@stud.fit.vutbr.cz
 *              Milan Hruban, xhruba08@stud.fit.vutbr.cz
 *              Martin Hons, xhonsm00@stud.fit.vutbr.cz
 *              David Hél, xhelda00@stud.fit.vutbr.cz
 */

/*
  *Include všech souborů
  */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/*
 * Definice
 */
#define TRUE 1
#define FALSE 0 // jen pro poradek, aby tu ta druha hodnota byla, hh
#define NUMBER_OF_KEY_WORDS 17
#define NUMBER_OF_RESERVED_WORDS

// Globalni promenne pro pocitani radku a sloupcu, bude potreba v lex.c a v error.c
int GlobalRow = 0;
int GlobalLine = 0;

/*
 * Prototyp funkce
 */
void printKeyWordTable(); // Vytiskne obsah tabulky klíčových slov


/*
 * Jednotlivé stavy automatu
 */
typedef enum {
    LA_START,   //Startovací stav										*
    LA_KEYWORD, // Klíčové slovo
    LA_INT,     //Int													*
    LA_DOT_DOUBLE, //Int s tečkou										*
    LA_DOUBLE, //Double													*
    LA_DOUBLE_pE, // Double s 'e'										*
    LA_DOUBLE_E_SIGN, //Znaménkové e									*
    LA_DOUBLE_E, //Konečné double										*
    LA_SIMPLE_IDENT, // jednoduchý indentifikátor						*
    LA_COMPLETE_IDENT, // Kompletní identifikátor						*
    LA_STRING_PREP, // Začátek a tělo stringu							*
    LA_STRING, // Kompletní string
    LA_EOF, // EOF														*
    LA_DIV, // Dělení '/'												*
    LA_SIMPLE_COMMENT, // Jednořádkový komentář '//'					*
    LA_BLOCK_COMMENT_END, // Konec blokového komentáře '*/'				*
    LA_MULTI, // Násobení '*'											*
    LA_BLOCK_COMMENT_START, // Začátek blokového komentáře '/*'			*
    LA_PLUS, // Plus '+'												*
    LA_MINUS, // Minus '-'												*
    LA_SQ_BRACKET_L, // Hranatá závorka, levá '['						*
    LA_SQ_BRACKET_R, // Hranatá závorka, pravá ']'						*
    LA_BRACKET_L, // Levá závorka '('									*
    LA_BRACKET_R, // Pravá závorka ')'									*
    LA_BRACE_L, // Levá složená závorka '{'								*
    LA_BRACE_R, // Prava slozena zavorka '}'							*
    LA_GREATER, // Větší než '>'										*
    LA_GREATER_EQ, // Vetsi rovno '>='									*
    LA_LESS, // Mensi '<'												*
    LA_LESS_EQ, // Mensi rovno '<='										*
    LA_ASSIGNMENT, // Prirazeni '='										*
	LA_COMPARASION, // Porovnani '=='									*
    LA_EXCL_MARK, // Vykricnik '!'										*
    LA_COMPARASION_NE, // Nerovna se '!='								*
    LA_SEMICOLON, // Strednik ';'										*
	LA_BACKSLASH, // Backslash '\'
	LA_DOUBLE_BACKSLASH, // Escape baskslashe '\\'
	LA_TAB, // Escape odtabování '\t'
	LA_NEW_LINE // Escape noveho radku '\n'
	LA_QUOTE, // Escape uvozovek '"'
	LA_OCT1, // První znak octanového čísla
	LA_OCT2, // Druhý znak octanového čísla
	LA_OCT, // Třetí znak octanového čísla, finální octanové číslo
    // Keywords
    LA_BOOLEAN,
    LA_BREAK,
    LA_CLASS,
    LA_CONTINUE,
    LA_DO,
    LA_DOUBLE,
    LA_ELSE,
    LA_FALSE,
    LA_FOR,
    LA_IF,
    LA_INT,
    LA_RETURN,
    LA_STRING,
    LA_STATIC,
    LA_TRUE,
    LA_VOID,
    LA_WHILE,
} tStatus;

/*
 * Struktura tokenu
 */
typedef struct
{
    tStatus status;  // Status konečného automatu
    char data[]; // Data, která obshahuje
    unsigned int length; // Délka, počet charů
    unsigned int allocated; // Status, jestli byl alokován
} tToken;

/* Globální token */
extern tToken token;

/*
 * Získá token z analyzátoru a vrátí jej
 * @param token
 * @return jeden načtený token z analyzátoru
 */
tToken * getToken(tToken * token);

/*
 * Inicializuje token a vrací pointer na token
 * @param token
 * @return ukazatel na inicializovaný token
 */
tToken * initToken(tToken * token);

/*
 * Ruší již předem vytvořený token
 * @param token
 */
void destroyToken(tToken * token);

/*
 * Funkce aktualizuje hodnotu tokenu na hodnotu z parametru string
 * @param token
 * @param string
 */
tToken * updateToken(tToken * token, char *string);

/*
 * Projde pole keyword a přiřadí korektně k tokenu "id" z pole keyword
 * @param token
 */
void keywordCheckToken(tToken * token);

void tokenReturnToken(tToken * token);

