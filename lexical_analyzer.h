/**
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

/**
  *Include všech souborů
  */

#include "lexical_analyzer.c"

/**
 * Definice
 */
#define NUMBER_OF_KEY_WORDS 17
#define NUMBER_OF_RESERVED_WORDS

/**
 * Prototyp funkce
 */
void printKeyWordTable(); // Vytiskne obsah tabulky klíčových slov


/**
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


/**
 * Struktura tokenu
 */
typedef struct
{
    tStatus status;  // Status konečného automatu
    char data[]; // Data, která obshahuje
    unsigned int length; // Délka, počet charů
    unsigned int allocated; // Status, jestli byl alokován
} tToken;

// Globální token
extern tToken token;

