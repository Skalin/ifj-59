/**
 * IFJ/IAL - Lexikální analyzátor
 * Varianta:    b/2/I
 * Subor:       lexical_analyzer.c
 * Tým:         59
 * Autoři:      Jan Hrbotický, xhrbot01@stud.fit.vutbr.cz
 *              Dominik Skála, xskala11@stud.fit.vutbr.cz
 *              Milan Hruban, xhruba08@stud.fit.vutbr.cz
 *              Martin Hons, xhonsm00@stud.fit.vutbr.cz
 *              David Hél, xhelda00@stud.fit.vutbr.cz
 */

#include "lexical_analyzer.h"
// some coding

void keywordCheckToken(tToken *token) {
    //Tabulky
    char *keyWordTable[NUMBER_OF_KEY_WORDS] = {
        "boolean","break","class","continue","do",
        "double","else","false","for","if","int",
        "return","String","static","true","void","while"
    };

    tStatus keyWordTokenTable[NUMBER_OF_KEY_WORDS] = {
            "LA_BOOLEAN","LA_BREAK","LA_CLASS","LA_CONTINUE","LA_DO",
            "LA_DOUBLE","LA_ELSE","LA_FALSE","LA_FOR","LA_IF","LA_INT",
            "LA_RETURN","LA_STRING","LA_STATIC","LA_TRUE","LA_VOID","LA_WHILE"
    };

    // For cyklus prohledá první tabulku a pokud v ní nalezne shodu v tokenu (strcmp()), přiřadí do tToken type příslušnou hodnotu z druhé tabulky
    // DONE Jan Hrbotický
    for (int i=0; i<(NUMBER_OF_KEY_WORDS-1); i++) {
        if (strcmp(keyWordTable[i], token->data) == 0)
            token->status = keyWordTokenTable[i];
    }
}


// Pomocne objekty
tToken * t_buffer;

// Body

tToken * initToken() {
    // Inicializace tokenu, prvni malloc, pak inicializace jednotlivych slozek
    // POZOR, ZDE SE MUSÍ IMPLEMENTOVAT CELÝ NOVÝ SOUBOR, KTERÝ BUDE OBSHAOVAT FUNKCE MALLOC, FREE, REALLOC, A ZRUŠENÍ
    // Jedná se o to, že všechny data budou v listovém seznamu (viz 1. úkol IAL)
}

tToken updateToken( tToken * token, char *string ) {
   // Alokace mista pokud je potreba, zvyseni delky ve strukture (lenght), kontrola jestli alokace probehla uspesne
    // Pomoci strncat() pridat novy retezec nakonec
    // POZOR, ZDE SE MUSÍ IMPLEMENTOVAT CELÝ NOVÝ SOUBOR, KTERÝ BUDE OBSHAOVAT FUNKCE MALLOC, FREE, REALLOC, A ZRUŠENÍ
    // Jedná se o to, že všechny data budou v listovém seznamu (viz 1. úkol IAL)
}

void tokenReturnToken( Token * token ) {
    // Do tokenu přiřadí načtené hodnoty z pomocného tokenu t_buffer
    t_buffer = token;
}

void destroyToken( tToken * token) {
    // Zruší daný token
    // POZOR, ZDE SE MUSÍ IMPLEMENTOVAT CELÝ NOVÝ SOUBOR, KTERÝ BUDE OBSHAOVAT FUNKCE MALLOC, FREE, REALLOC, A ZRUŠENÍ
    // Jedná se o to, že všechny data budou v listovém seznamu (viz 1. úkol IAL)
}

tToken * getToken( tToken * token, char *file){
    // Připojí se do souboru a postupně načte následující token (+ o něm přidá informace do struktury tToken)

    char *c = '\0'; // inicializovaná proměnná c s výchozí hodnotou \0

	c = fopen(file, "r"); // stačí nám soubor pouze pro čtení

	initToken();
	token->status = LA_START;
	int i;

	char buffer[32];

	while (TRUE) { // TRUE je definována jako 1 v .h souboru
		fgetc(c);
		i++; // delka "retezce"
		GlobalRow++; // pozice na radku, resetuje se pri kazdem novem radku..

		buffer[i-1] = c; // pole je cislovano od 0

		switch(token->status) {
			case LA_START:	// pocatecni stav automatu
				if ((isspace(c))) {
					continue;
				}
				if (c == EOF) {	// EOF
					token->status = LA_EOF;
					break;
				}
				// oddelovac
				if (c == 59) { // ;
					token->status = LA_SEMICOLON;
					break;
				}
				// zavorky
				if (c == 91) { // [
					token->status = LA_SQ_BRACKET_L;
					break;
				}

				if (c == 93) { // ]
					token->status = LA_SQ_BRACKET_R;
					break;
				}

				if (c == 40) { // (
					token->status = LA_BRACKET_L;
					break;
				}

				if (c == 41) { // )
					token->status = LA_BRACKET_R;
					break;
				}

				if (c == 123) { // {
					token->status = LA_BRACE_L;
					break;
				}

				if (c == 125) { // }
					token->status = LA_BRACE_R;
					break;
				}
				// konec zavorek
				// matematicke operace
				if (c == 47) { // /
					token->status = LA_DIV;
					continue;
				}

				if (c == 42) { // *
					token->status = LA_MULTI;
					continue;
				}

				if (c == 43) { // +
					token->status = LA_PLUS;
					break;
				}

				if (c == 45) { // -
					token->status = LA_MINUS;
					break;
				}

				if (c == 62) { // >
					token->status = LA_GREATER;
					continue;
				}

				if (c == 60) { // <
					token->status = LA_LESS;
					continue;
				}

				if (c == 33) { // !
					token->status = LA_EXCL_MARK;
					continue;
				}

				if (c == 61) { // =
					token->status = LA_ASSIGNMENT;
					continue;
				}
				// konec mat. operaci
				// identifikatory
				if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122)) { // LA_SIMPLE_IDENT
					token->status = LA_SIMPLE_IDENT;
					continue;
				}
				// cislice
				if (c >= 48 && c <= 57) { // 0..9
					token->status = LA_INT;
					continue;
				}
				// zacatek stringu
				if (c == 34) { // "
					token->status = LA_STRING_PREP;
					continue;
				}

			// identifikatory
			case LA_SIMPLE_IDENT:
				if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122)) { // a..z,A..Z,_,$
					continue;
				} else if (c == 46) { // .
					token->status = LA_COMPLETE_IDENT;
					continue;
				}

			case LA_COMPLETE_IDENT:
				if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122)) { // a..z,A..Z,_,$
					continue;
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
				}

			case LA_DOT_DOUBLE:
				if (c >= 48 && c <= 57) { // 0..9
					token->status = LA_DOUBLE;
					continue;
				}

			case LA_DOUBLE:
				if (c >= 48 && c <= 57) { // 0..9
					continue;
				} else if (c == 101 || c == 69) { // e nebo E
					token->status = LA_DOUBLE_pE;
					continue;
				}

			case LA_DOUBLE_pE:
				if (c >= 48 && c <= 57) { // 0..9
					token->status = LA_DOUBLE_E;
					continue;
				} else if (c == 43 || c == 45) { // + nebo -
					token->status = LA_DOUBLE_E_SIGN;
					continue;
				}

			case LA_DOUBLE_E_SIGN:
				if (c >= 48 && c <= 57) { // 0..9
					token->status = LA_DOUBLE_E;
					continue;
				}

			case LA_DOUBLE_E:
				if (c >= 48 && c <= 57) { // 0..9
					continue;
				}

			// string
			case LA_STRING_PREP:
				if (c == 47) {
					token->status = LA_BA
				}



			// dalsi porovnani KA
			case LA_GREATER:
				if (c == 61) { // >=
					token->status = LA_GREATER_EQ;
					break;
				}

			case LA_LESS:
				if (c == 61) { // <=
					token->status = LA_LESS_EQ;
					break;
				}

			case LA_ASSIGNMENT:
				if (c == 61) { // ==
					token->status = LA_COMPARASION;
					break;
				}

			case LA_EXCL_MARK:
				if (c == 61) { // !=
					token->status = LA_COMPARASION_NE;
					break;
				}

			// komentare
			case LA_DIV:
				if (c == 47) {
					token->status = LA_SIMPLE_COMMENT;
					break;
				} else if (c == 42) {
					token->status = LA_BLOCK_COMMENT_START;
					break;
				}

			case LA_MULTI:
				if (c == 47) {
					token->status = LA_BLOCK_COMMENT_END;
					break;
				}
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
	token->length += i;
	updateToken(token, buffer);

	return token;
}

/*
 * TODO:
 * chybove stavy
 * zpracovani escape
 * zpracovani stringu
 * prevod oktalovych cisel na decimalni a nasledny prevod na ASCII
 * vyresit alokaci
 */
