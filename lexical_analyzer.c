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

void fillToken(tToken * token, tokenType type) {
    // Nastaví typ tokenu
    token->type = type;
}


tToken * getToken(tToken * token, char *file){
    // Připojí se do souboru a postupně načte následující token (+ o něm přidá informace do struktury tToken)

	GlobalRow = 0;
	GlobalColumn = 0;

    char c = '\0'; // inicializovaná proměnná c s výchozí hodnotou \0

	FILE * fp;
	fp = fopen (file, "r"); // stačí nám soubor pouze pro čtení

	initToken(token);
	token->type = LA_START;

	tStatus status = LA_START;

	char buffer[32];
	memset(&buffer, 0, 32);
	int i;

	while (TRUE) { // TRUE je definována jako 1 v .h souboru
		c = fgetc(fp);
		
		GlobalRow++; // pozice na radku, resetuje se pri kazdem novem radku..
		if (c == '\n') {
			GlobalColumn++; // pocet radku
			GlobalRow = 0; // reset pozice na radku
		}

		switch(status) {
			case LA_START:	// pocatecni stav automatu
				while(isspace(c)) { 
					c = fgetc(fp);
				}
				if (c == EOF) {	// EOF	
					token->type = t_eof;
					return token;
				// oddelovac
				} else if (c == 59) { // ;
					token->type = t_semicolon;
					return token;
				// konec oddelovacu
				// zavorky
				} else if (c == 91) { // [
					token->type = t_sq_bracket_l;
					return token;
				} else if (c == 93) { // ]
					token->type = t_sq_bracket_r;
					return token;
				} else if (c == 40) { // (
					token->type = t_bracket_l;
					return token;
				} else if (c == 41) { // )
					token->type = t_bracket_r;
					return token;
				} else if (c == 123) { // {
					token->type = t_brace_l;
					return token;
				} else if (c == 125) { // }
					token->type = t_brace_r;
					return token;
				// konec zavorek
				// matematicke operace
				} else if (c == 47) { // /
					status = LA_DIV;
					break;
				} else if (c == 42) { // *
					status = LA_MULTI;
					break;
				} else if (c == 43) { // +
					token->type = t_plus;
					break;
				} else if (c == 45) { // -
					token->type = t_minus;
					break;
				} else if (c == 62) { // >
					status = LA_GREATER;
					break;
				} else if (c == 60) { // <
					status = LA_LESS;
					break;
				} else if (c == 33) { // !
					status = LA_EXCL_MARK;
					break;
				} else if (c == 61) { // =
					status = LA_ASSIGNMENT;
					break;
				// konec mat. operaci
				// identifikatory
				} else if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == 95 || c == 36) { // LA_SIMPLE_IDENT
					buffer[i] = c;
					i++;
					status= LA_SIMPLE_IDENT;
				// konec identifikatoru
				// cislice
				} else if (c >= 48 && c <= 57) { // 0..9
					buffer[i] = c;
					i++;
					status= LA_INT;
				// konec cislic
				// zacatek stringu
				} else if (c == 34) { // "
					status = LA_STRING_PREP;
				// konec stringu
				} else {
					throwException(1, GlobalRow, GlobalColumn);
				}
				break;

			// identifikatory
			case LA_SIMPLE_IDENT:
				if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == 95 || c == 36) { // a..z,A..Z,_,$
					buffer[i] = c;
					i++;
				} else if (c == 46) { // .
					status = LA_COMPLETE_IDENT;
					buffer[i] = c;
					i++;
				} else {
					ungetc(c, fp);
					token = updateToken(token, buffer);
					keywordCheckToken(token);
					return token;
				}
				break;

			case LA_COMPLETE_IDENT:
				if (((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c == 95) || (c == 36))) { // a..z,A..Z,_,$
					buffer[i] = c;
					i++;
				} else {
					ungetc(c, fp);
					token = updateToken(token, buffer);
					token->type= t_complete_ident;
					return token;	
				}
				break;
			// konec identifikatoru

			// cisla
			case LA_INT:
				if (c >= 48 && c <= 57) { // 0..9
					buffer[i] = c;
					i++;
				} else if (c == 46) { // .
					buffer[i] = c;
					i++;
					status = LA_DOT_DOUBLE;
				} else if (c == 101 || c == 69) { // e nebo E
					buffer[i] = c;
					i++;
					status = LA_DOUBLE_pE;
				} else {
					ungetc(c, fp);
					token = updateToken(token, buffer);
					token->type= t_int;
					return token;	
				}
				break;

			case LA_DOT_DOUBLE:
				if (c >= 48 && c <= 57) { // 0..9
					buffer[i] = c;
					i++;
					status = LA_DOUBLE;
				} else {
					throwException(1, GlobalRow, GlobalColumn);
				}
				break;

			case LA_DOUBLE:
				if (c >= 48 && c <= 57) { // 0..9
					buffer[i] = c;
					i++;
				} else if ((c == 101) || (c == 69)) { // e nebo E
					buffer[i] = c;
					i++;
					status = LA_DOUBLE_pE;
				} else {
					ungetc(c, fp);
					token = updateToken(token, buffer);
					token->type= t_double;
					return token;
				}
				break;

			case LA_DOUBLE_pE:
				if (c >= 48 && c <= 57) { // 0..9
					buffer[i] = c;
					i++;
					status = LA_DOUBLE_E;
				} else if (c == 43 || c == 45) { // + nebo -
					buffer[i] = c;
					i++;
					status = LA_DOUBLE_E_SIGN;
				} else {
					throwException(1, GlobalRow, GlobalColumn);
				}

			case LA_DOUBLE_E_SIGN:
				if (c >= 48 && c <= 57) { // 0..9
					buffer[i] = c;
					i++;
					status = LA_DOUBLE_E;
				} else {
					throwException(1, GlobalRow, GlobalColumn);
				}

			case LA_DOUBLE_E:
				if (c >= 48 && c <= 57) { // 0..9
					buffer[i] = c;
					i++;
				} else {
					ungetc(c, fp);
					token = updateToken(token, buffer);
					token->type= t_double_e;
					return token;
				}

			// string
			case LA_STRING_PREP:
				if (c == 92) { // "\"
					buffer[i] = c;
					i++;
					status = LA_BACKSLASH;
				} else if (c == 34) { // ""
					buffer[i] = c;
					i++;
					ungetc(c, fp);
					token = updateToken(token, buffer);
					token->type= t_string;
					return token;
				} else { // "xxxxxx
					buffer[i] = c;
					i++;
				}
				break;
			case LA_BACKSLASH:
				if (c == 34) { // "\"
					buffer[i] = c;
					i++;
					status = LA_QUOTE;
				} else if (c == 92) {
					buffer[i] = c;
					i++;
					status = LA_DOUBLE_BACKSLASH;
				} else if (c == 110) { // "\n
					buffer[i] = c;
					i++;
					status = LA_NEW_LINE;
				} else if (c == 116) { // "\t
					buffer[i] = c;
					i++;
					status = LA_TAB;
			// oktalovy cisla zatim kasleme, viz TODO
			//	} else if (c >= 48 && c <= 51) { // octalovy cisla -> \0 .. \3
			//		token->status = LA_OCT1;
			//		continue;
			//
				} else {
					buffer[i] = c;
					i++;
					status = LA_STRING_PREP;	
				}
				break;
			case LA_QUOTE:
				if (c == 34) { // "\""
					buffer[i] = c;
					i++;
					ungetc(c, fp);
					token = updateToken(token, buffer);
					token->type= t_string;
					return token;
				} else { // "\"x
					status = LA_STRING_PREP;
				}
				break;
			case LA_DOUBLE_BACKSLASH:
				if (c == 34) {
					buffer[i] = c;
					i++;
					ungetc(c, fp);
					token = updateToken(token, buffer);
					token->type= t_string;
					return token;
				} else {
					status = LA_STRING_PREP;
				}
				break;
			case LA_NEW_LINE:
				if (c == 34) { // "\n"
					buffer[i] = c;
					i++;
					ungetc(c, fp);
					token = updateToken(token, buffer);
					token->type= t_string;
					return token;
				} else { // "\nx
					status = LA_STRING_PREP;
				}
				break;
			case LA_TAB:
				if (c == 34) { // "\t"
					buffer[i] = c;
					i++;
					ungetc(c, fp);
					token = updateToken(token, buffer);
					token->type= t_string;
					return token;
				} else { // "\tx
					status = LA_STRING_PREP;
				}
				break;

			// zde pak bude octal, jeste neni doresen jak ma koncit

			// dalsi porovnani KA
			case LA_GREATER:
				if (c == 61) { // >=
					buffer[i] = c;
					i++;
					ungetc(c, fp);
					token = updateToken(token, buffer);
					token->type= t_greater_eq;
					return token;
				} else {
					buffer[i] = c;
					i++;
					ungetc(c, fp);
					token = updateToken(token, buffer);
					token->type= t_greater;
					return token;
				}
				break;
			case LA_LESS:
				if (c == 61) { // <=
					buffer[i] = c;
					i++;
					ungetc(c, fp);
					token = updateToken(token, buffer);
					token->type= t_less_eq;
					return token;
				} else {
				 	buffer[i] = c;
				 	i++;
					ungetc(c, fp);
					token = updateToken(token, buffer);
					token->type= t_less;
					return token;
				}
				break;
			case LA_ASSIGNMENT:
				if (c == 61) { // ==
					buffer[i] = c;
					i++;
					ungetc(c, fp);
					token = updateToken(token, buffer);
					token->type= t_comparasion;
					return token;
				} else {
					buffer[i] = c;
					i++;
					ungetc(c, fp);
					token = updateToken(token, buffer);
					token->type= t_assignment;
					return token;
				}
				break;
			case LA_EXCL_MARK:
				if (c == 61) { // !=
					buffer[i] = c;
					i++;
					ungetc(c, fp);
					token = updateToken(token, buffer);
					token->type= t_comparasion_ne;
					return token;
				} else {
					buffer[i] = c;
					i++;
					ungetc(c, fp);
					token = updateToken(token, buffer);
					token->type= t_excl_mark;
					return token;
				}
				break;
			// komentare
			case LA_DIV:
				if (c == 47) {
					buffer[i] = c;
					i++;
					ungetc(c, fp);
					token = updateToken(token, buffer);
					token->type= t_simple_comment;
					return token;
				} else if (c == 42) {
					buffer[i] = c;
					i++;
					ungetc(c, fp);
					token = updateToken(token, buffer);
					token->type= t_block_comment_start;
					return token;
				} else {
					buffer[i] = c;
					i++;
					ungetc(c, fp);
					token = updateToken(token, buffer);
					token->type= t_div;
					return token;
				}

			case LA_MULTI:
				if (c == 47) {
					buffer[i] = c;
					i++;
					ungetc(c, fp);
					token = updateToken(token, buffer);
					token->type= t_block_comment_end;
					return token;
				} else {
					buffer[i] = c;
					i++;
					ungetc(c, fp);
					token = updateToken(token, buffer);
					token->type= t_multi;
					return token;
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
} //end of function

/*
 * TODO:
 * prevod oktalovych cisel na decimalni a nasledny prevod na ASCII
 * vyresit alokaci
 */
