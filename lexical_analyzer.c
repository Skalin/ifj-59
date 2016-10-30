/**
 * IFJ/IAL - Lexikální analyzátor
 * Varianta:    b/2/I
 * Soubor:       lexical_analyzer.c
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
#include "typedef.h"
#include "lexical_analyzer.h"
#include "garbage_collector.h"
#include "error_handler.h"
// some coding

void keywordCheckToken(tToken *token) {
    //Tabulky
    char * keyWordTable[] = {
        "boolean","break","class","continue","do",
        "double","else","false","for","if","int",
        "return","String","static","true","void","while"
    };

	tStatus keyWordTokenTable[] = {
		t_kw_boolean, t_kw_break, t_kw_class, t_kw_continue, t_kw_do, 
		t_kw_double, t_kw_else, t_kw_false, t_kw_for, t_kw_if, t_kw_int,
		t_kw_return, t_kw_string, t_kw_static, t_kw_true, t_kw_void, t_kw_while,
	};
	token->type = LA_SIMPLE_IDENT;

    // For cyklus prohledá první tabulku a pokud v ní nalezne shodu v tokenu (strcmp()), přiřadí do tToken type příslušnou hodnotu z druhé tabulky
    // DONE Jan Hrbotický
    for (int i=0; i<(NUMBER_OF_KEY_WORDS-1); i++) {
        if (strcmp(keyWordTable[i], token->data) == 0)
            token->type = keyWordTokenTable[i];
    }
}


// Pomocne objekty
tToken * t_buffer;

// Body

tToken * initToken(tToken * token) {
    // Inicializace tokenu, prvni malloc, pak inicializace jednotlivych slozek
    // POZOR, ZDE SE MUSÍ IMPLEMENTOVAT CELÝ NOVÝ SOUBOR, KTERÝ BUDE OBSHAOVAT FUNKCE MALLOC, FREE, REALLOC, A ZRUŠENÍ
    // Jedná se o to, že všechny data budou v listovém seznamu (viz 1. úkol IAL)

	unsigned int mallocSize = 16;

	token = plusMalloc(sizeof(tToken) + sizeof(char)*mallocSize);
    // TODO mám tady vytvářet nový token nebo používám globalní?

    token->type = t_error;   // nastaví token do počátečního stavu
    token->data[0] = '\0';      // inicializace všech prvků na výchozí hodnoty
    token->length = 0;
    token->allocated = 0;

    return token;
}

tToken * updateToken(tToken * token, char *string) {
   // Alokace mista pokud je potreba, zvyseni delky ve strukture (lenght), kontrola jestli alokace probehla uspesne
    // Pomoci strncat() pridat novy retezec nakonec
    // POZOR, ZDE SE MUSÍ IMPLEMENTOVAT CELÝ NOVÝ SOUBOR, KTERÝ BUDE OBSHAOVAT FUNKCE MALLOC, FREE, REALLOC, A ZRUŠENÍ
    // Jedná se o to, že všechny data budou v listovém seznamu (viz 1. úkol IAL)

    unsigned int stringLength = strlen(string);

    if (token->allocated < (stringLength + token->length) ) {     // pokud je alokováno méně než je potřeba
        token = plusRealloc(token, sizeof(tToken) + sizeof(char)*(stringLength+token->length) );   //TODO
        token->allocated = stringLength + token->length;      // update hodnoty allocated v tokenu
    }

    strncat(token->data, string, stringLength);      // připojení stringu na konec tokenu
    token->length = token->length + stringLength;   // update délky tokenu

    return token;
}

void tokenReturnToken(tToken * token) {
    // Do tokenu přiřadí načtené hodnoty z pomocného tokenu t_buffer
    t_buffer = token;
}

void destroyToken(tToken * token) {
    // Zruší daný token
    // POZOR, ZDE SE MUSÍ IMPLEMENTOVAT CELÝ NOVÝ SOUBOR, KTERÝ BUDE OBSHAOVAT FUNKCE MALLOC, FREE, REALLOC, A ZRUŠENÍ
    // Jedná se o to, že všechny data budou v listovém seznamu (viz 1. úkol IAL)

    plusFree(token);
}

void fillToken(tToken * token, tStatus status) {
    // Nastaví status tokenu
    token->status = status;
}



tToken * getToken(tToken * token, char *file){
    // Připojí se do souboru a postupně načte následující token (+ o něm přidá informace do struktury tToken)

	GlobalRow = 0;
	GlobalColumn = 0;

    char c = '\0'; // inicializovaná proměnná c s výchozí hodnotou \0

	FILE * fp;
	fp = fopen (file, "r"); // stačí nám soubor pouze pro čtení

	initToken(token);
	token->status = LA_START;
	int i;

	char buffer[32];

	while (TRUE) { // TRUE je definována jako 1 v .h souboru
		c = fgetc(fp);
		GlobalRow++; // pozice na radku, resetuje se pri kazdem novem radku..
		if (c == '\n') {
			GlobalColumn++; // pocet radku
			GlobalRow = 0; // reset pozice na radku
		}
		i++; // delka "retezce"

		buffer[i-1] = c; // pole je cislovano od 0

		switch(token->status) {
			case LA_START:	// pocatecni stav automatu
				if (isspace(c)) {
					continue;
				} else if (c == EOF) {	// EOF
					token->status = LA_EOF;
					break;
				// oddelovac
				} else if (c == 59) { // ;
					token->status = LA_SEMICOLON;
					break;
				// konec oddelovacu
				// zavorky
				} else if (c == 91) { // [
					token->status = LA_SQ_BRACKET_L;
					break;
				} else if (c == 93) { // ]
					token->status = LA_SQ_BRACKET_R;
					break;
				} else if (c == 40) { // (
					token->status = LA_BRACKET_L;
					break;
				} else if (c == 41) { // )
					token->status = LA_BRACKET_R;
					break;
				} else if (c == 123) { // {
					token->status = LA_BRACE_L;
					break;
				} else if (c == 125) { // }
					token->status = LA_BRACE_R;
					break;
				// konec zavorek
				// matematicke operace
				} else if (c == 47) { // /
					token->status = LA_DIV;
					continue;
				} else if (c == 42) { // *
					token->status = LA_MULTI;
					continue;
				} else if (c == 43) { // +
					token->status = LA_PLUS;
					break;
				} else if (c == 45) { // -
					token->status = LA_MINUS;
					break;
				} else if (c == 62) { // >
					token->status = LA_GREATER;
					continue;
				} else if (c == 60) { // <
					token->status = LA_LESS;
					continue;
				} else if (c == 33) { // !
					token->status = LA_EXCL_MARK;
					continue;
				} else if (c == 61) { // =
					token->status = LA_ASSIGNMENT;
					continue;
				// konec mat. operaci
				// identifikatory
				} else if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == 95 || c == 36) { // LA_SIMPLE_IDENT
					token->status = LA_SIMPLE_IDENT;
					continue;
				// konec identifikatoru
				// cislice
				}else if (c >= 48 && c <= 57) { // 0..9
					token->status = LA_INT;
					continue;
				// konec cislic
				// zacatek stringu
				} else if (c == 34) { // "
					token->status = LA_STRING_PREP;
					continue;
				// konec stringu
				} else {
					throwException(1, GlobalRow, GlobalColumn);
				}

			// identifikatory
			case LA_SIMPLE_IDENT:
				if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == 95 || c == 36) { // a..z,A..Z,_,$
					continue;
				} else if (c == 46) { // .
					token->status = LA_COMPLETE_IDENT;
					continue;
				} else if (isspace(c)) {
					break;
				} else {
					throwException(1, GlobalRow, GlobalColumn);
				}

			case LA_COMPLETE_IDENT:
				if (((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c == 95) || (c == 36))) { // a..z,A..Z,_,$
					continue;
				} else if (isspace(c)) {
					break;
				} else {
					throwException(1, GlobalRow, GlobalColumn);
				}
			// konec identifikatoru

			// cisla
			case LA_INT:
				if (c >= 48 && c <= 57) { // 0..9
					continue;
				} else if (c == 46) { // .
					token->status = LA_DOT_DOUBLE;
					continue;
				} else if (c == 101 || c == 69) { // e nebo E
					token->status = LA_DOUBLE_pE;
					continue;
				} else if (isspace(c)) {
					break;
				} else {
					throwException(1, GlobalRow, GlobalColumn);
				}

			case LA_DOT_DOUBLE:
				if (c >= 48 && c <= 57) { // 0..9
					token->status = LA_DOUBLE;
					continue;
				} else {
					throwException(1, GlobalRow, GlobalColumn);
				}

			case LA_DOUBLE:
				if (c >= 48 && c <= 57) { // 0..9
					continue;
				} else if ((c == 101) || (c == 69)) { // e nebo E
					token->status = LA_DOUBLE_pE;
					continue;
				} else if (isspace(c)) {
					break;
				} else {
					throwException(1, GlobalRow, GlobalColumn);
				}

			case LA_DOUBLE_pE:
				if (c >= 48 && c <= 57) { // 0..9
					token->status = LA_DOUBLE_E;
					continue;
				} else if (c == 43 || c == 45) { // + nebo -
					token->status = LA_DOUBLE_E_SIGN;
					continue;
				} else {
					throwException(1, GlobalRow, GlobalColumn);
				}

			case LA_DOUBLE_E_SIGN:
				if (c >= 48 && c <= 57) { // 0..9
					token->status = LA_DOUBLE_E;
					continue;
				} else {
					throwException(1, GlobalRow, GlobalColumn);
				}

			case LA_DOUBLE_E:
				if (c >= 48 && c <= 57) { // 0..9
					continue;
				} else if (isspace(c)) {
					break;
				} else {
					throwException(1, GlobalRow, GlobalColumn);
				}

			// string
			case LA_STRING_PREP:
				if (c == 92) {
					token->status = LA_BACKSLASH;
					continue;
				} else if (c == 34) { // ""
					token->status = LA_STRING;
					break;
				} else { // "xxxxxx
					continue;
				}
			case LA_BACKSLASH:
				if (c == 34) { // "\"
					token->status = LA_QUOTE;
					continue;
				} else if (c == 92) {
					token->status = LA_DOUBLE_BACKSLASH;
					continue;
				} else if (c == 110) { // "\n
					token->status = LA_NEW_LINE;
					continue;
				} else if (c == 116) { // "\t
					token->status = LA_TAB;
			// oktalovy cisla zatim kasleme, viz TODO
			//	} else if (c >= 48 && c <= 51) { // octalovy cisla -> \0 .. \3
			//		token->status = LA_OCT1;
			//		continue;
			//
				}
			case LA_QUOTE:
				if (c == 34) { // "\""
					token->status = LA_STRING;
					break;
				} else { // "\"x
					token->status = LA_STRING_PREP;
					continue;
				}
			case LA_DOUBLE_BACKSLASH:
				if (c == 34) {
					token->status = LA_STRING;
					break;
				} else {
					token->status = LA_STRING_PREP;
					continue;
				}
			case LA_NEW_LINE:
				if (c == 34) { // "\n"
					token->status = LA_STRING;
					break;
				} else { // "\nx
					token->status = LA_STRING_PREP;
					continue;
				}
			case LA_TAB:
				if (c == 34) { // "\t"
					token->status = LA_STRING;
					break;
				} else { // "\tx
					token->status = LA_STRING_PREP;
					continue;
				}

			// zde pak bude octal, jeste neni doresen jak ma koncit

			// dalsi porovnani KA
			case LA_GREATER:
				if (c == 61) { // >=
					token->status = LA_GREATER_EQ;
					break;
				} else if (isspace(c)) {
					break;
				} else {
					throwException(1, GlobalRow, GlobalColumn);
				}

			case LA_LESS:
				if (c == 61) { // <=
					token->status = LA_LESS_EQ;
					break;
				} else if (isspace(c)) {
					break;
				} else {
					throwException(1, GlobalRow, GlobalColumn);
				}

			case LA_ASSIGNMENT:
				if (c == 61) { // ==
					token->status = LA_COMPARASION;
					break;
				} else if (isspace(c)) {
					break;
				} else {
					throwException(1, GlobalRow, GlobalColumn);
				}

			case LA_EXCL_MARK:
				if (c == 61) { // !=
					token->status = LA_COMPARASION_NE;
					break;
				} else if (isspace(c)) {
					break;
				} else {
					throwException(1, GlobalRow, GlobalColumn);
				}

			// komentare
			case LA_DIV:
				if (c == 47) {
					token->status = LA_SIMPLE_COMMENT;
					break;
				} else if (c == 42) {
					token->status = LA_BLOCK_COMMENT_START;
					break;
				} else if (isspace(c)) {
					break;
				} else {
					throwException(1, GlobalRow, GlobalColumn);
				}

			case LA_MULTI:
				if (c == 47) {
					token->status = LA_BLOCK_COMMENT_END;
					break;
				} else if (isspace(c)) {
					break;
				} else {
					throwException(1, GlobalRow, GlobalColumn);
				}
			default:
				break;
		} // konec switche

		if (i == 32) { // pokud zaplnim buffer, nahraju data do tokenu, prictu delku bufferu a vynuluju buffer
			updateToken(token, buffer);
			token->length += i;
			for (int j = 0; j < i; j++) {
				buffer[j] = '\0';
			}
			i = 0;
		}
	} //cyklus

	keywordCheckToken(token);
	token->length += i;
	updateToken(token, buffer);

	return token;
}

/*
 * TODO:
 * prevod oktalovych cisel na decimalni a nasledny prevod na ASCII
 * vyresit alokaci
 */
