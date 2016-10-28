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

	buffer = plusMalloc(32);

	while (TRUE) { // TRUE je definována jako 1 v .h souboru

		if (buffer == 31) {
			buffer = plusRealloc(32);
		}

		fgetc(c);
		GlobalRow += 1;

		switch(state) {
			case LA_START:
				// TOHLE JE NA DODELANI PRO JOHNYHO, AZ VYRESI CO S TEMA OCTALOVYMA HODNOTAMA
				if ((isspace(c)) || (0 != 0) /* sem prijde whitespace pres octaly */) {
					continue;
				}
				// EOF
				if (c == EOF) {
					token->status = LA_EOF;
					break;
				}
				// oddelovac
				if (c == 59) { // LA_SEMICOLON
					token->status = LA_SEMICOLON;
					break;
				}
				// zavorky
				if (c == 91) { // LA_SQ_BRACKET_L
					token->status = LA_SQ_BRACKET_L;
					break;
				}

				if (c == 93) { // LA_SQ_BRACKET_R
					token->status = LA_SQ_BRACKET_R;
					break;
				}

				if (c == 40) { // LA_BRACKET_L
					token->status = LA_BRACKET_L;
					break;
				}

				if (c == 41) { // LA_BRACKET_R
					token->status = LA_BRACKET_R;
					break;
				}

				if (c == 123) { // LA_BRACE_L
					token->status = LA_BRACE_L;
					break;
				}

				if (c == 125) { // LA_BRACE_R
					token->status = LA_BRACE_R;
					break;
				}

				// porovnani
				if (c == 47) { // LA_DIV
					token->status = LA_DIV;
					continue;
				}

				if (c == 42) { // LA_MULTI
					token->status = LA_MULTI;
					continue;
				}

				if (c == 43) { // LA_PLUS
					token->status = LA_PLUS;
					break;
				}

				if (c == 45) { // LA_MINUS
					token->status = LA_MINUS;
					break;
				}

				if (c == 62) { // LA_GREATER
					token->status = LA_GREATER;
					continue;
				}

				if (c == 60) { // LA_LESS
					token->status = LA_LESS;
					continue;
				}

				if (c == 33) { // LA_EXCL_MARK
					token->status = LA_EXCL_MARK;
					continue;
				}

				if (c == 61) { // LA_ASSIGNMENT
					token->status = LA_ASSIGNMENT;
					continue;
				}
				// hodnoty
				if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122)) { // LA_SIMPLE_IDENT

				}

				if (c >= 48 && c <= 57) { // LA_INT

				}
			case LA_GREATER:
				if (c == 61) {
					token->status = LA_GREATER_EQ;
					break;
				}

			case LA_LESS:
				if (c == 61) {
					token->status = LA_LESS_EQ;
					break;
				}

			case LA_ASSIGNMENT:
				if (c == 61) {
					token->status = LA_COMPARASION;
					break;
				}

			case LA_EXCL_MARK:
				if (c == 61) {
					token->status = LA_COMPARASION_NE;
					break;
				}
		} // konec switche
	} //cyklus
	fclose(FILE);
}
