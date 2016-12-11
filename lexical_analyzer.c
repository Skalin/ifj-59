/**
 * IFJ/IAL - Lexik�ln� analyz�tor
 * Varianta:    b/2/I
 * Soubor:       lexical_analyzer.c
 * T�m:         59
 * Auto�i:      Jan Hrbotick�, xhrbot01@stud.fit.vutbr.cz
 *              Dominik Sk�la, xskala11@stud.fit.vutbr.cz
 *              Milan Hruban, xhruba08@stud.fit.vutbr.cz
 *              Martin Hons, xhonsm00@stud.fit.vutbr.cz
 *              David H�l, xhelda00@stud.fit.vutbr.cz
 */
/*
  *Include v�ech soubor�
  */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "typedef.h"
#include "lexical_analyzer.h"
#include "garbage_collector.h"
#include "error_handler.h"

// some coding

// pole stavu pro debug lexu
static const char *tokenTypeString[] = {
		"t_bracket_l","t_bracket_r","t_div","t_multi","t_plus","t_minus","t_comparasion","t_comparasion_ne","t_greater","t_less","t_less_eq","t_greater_eq","t_excl_mark","t_semicolon","t_simple_ident","t_complete_ident","t_int","t_double","t_double_e","t_string","t_error","t_assignment","t_brace_l","t_brace_r","t_sq_bracket_l","t_sq_bracket_r","t_simple_comment","t_block_comment_start","t_block_comment_end","t_eof","t_comma","t_kw_class","t_kw_static","t_kw_boolean","t_kw_double","t_kw_int","t_kw_string","t_kw_void","t_kw_while","t_kw_for","t_kw_break","t_kw_return","t_kw_continue","t_kw_do","t_kw_if","t_kw_else","t_kw_true","t_kw_false","t_find","t_sort","t_length","t_substring","t_compare","t_read_int","t_read_double","t_read_string","t_print"
};

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
		t_kw_return, t_kw_string, t_kw_static, t_kw_true, t_kw_void, t_kw_while
	};
	token->type = t_simple_ident; 

    // For cyklus prohlede prvni tabulku a pokud v ni nalezne shodu v tokenu (strcmp()), prida do tToken type prislusnou hodnotu z druhe tabulky
    // DONE Jan Hrboticky
    for (int i=0; i < NUMBER_OF_KEY_WORDS; i++) {
        if (strcmp(keyWordTable[i], token->data) == 0)
            token->type = keyWordTokenTable[i];
    }
}


// Pomocne objekty
tToken * t_buffer;

// Body

tToken * initToken() {
    // Inicializace tokenu, prvni malloc, pak inicializace jednotlivych slozek
    // POZOR, ZDE SE MUSi IMPLEMENTOVAT CELy NOVy SOUBOR, KTERy BUDE OBSHAOVAT FUNKCE MALLOC, FREE, REALLOC, A ZRUSENE
    // Jedna se o to, ze vsechny data budou v listovem seznamu (viz 1. ukol IAL)

	unsigned int mallocSize = 16;

	tToken * token = (tToken *) plusMalloc(sizeof(tToken) + sizeof(char)*mallocSize);
    

    token->type = t_error;   // nastavi token do pocatecniho stavu
    token->data[0] = '\0';      // inicializace vsech prvky na vychozi hodnoty
    token->length = 0;
    token->allocated = 0;

    return token;
}

tToken * updateToken(tToken * token, char *string) {
	// Alokace mista pokud je potreba, zvyseni delky ve strukture (lenght), kontrola jestli alokace probehla uspesne
	// Pomoci strncat() pridat novy retezec nakonec
	// POZOR, ZDE SE MUSi IMPLEMENTOVAT CELy NOVy SOUBOR, KTERy BUDE OBSHAOVAT FUNKCE MALLOC, FREE, REALLOC, A ZRUSENE
	//  Jedna se o to, ze vsechny data budou v listovem seznamu (viz 1. ukol IAL)

    int strLength = strlen(string);

    
    if (token->allocated < (strLength + token->length + 1) ) {     // pokud je alokovano mene nez je potreba

		token->allocated = strLength + token->length + 1;      // update hodnoty allocated v tokenu
		token = plusRealloc(token, sizeof(tToken) + (sizeof(char) * (token->allocated)));   //TODO
    }


    strncat(token->data, string, strLength);      // pripojeni stringu na konec tokenu
    token->length = token->length + strLength;   // update delky tokenu

    return token;
/*

	unsigned int len = strlen(string);
	unsigned int total_len = len + (token->length) + 1;
	if (total_len > token->allocated) {
		token->allocated = total_len;
		token = plusRealloc(token, sizeof(tToken) + (sizeof(char) * (token->allocated)));
		if (token == NULL) {
			throwException(1, 0, 0);
			return 0;
		}
	}
	return token;*/
 
}

void tokenReturnToken(tToken * token) {
    // Do tokenu priradi nactene hodnoty z pomocneho tokenu t_buffer
    t_buffer = token;
}

void destroyToken(tToken * token) {
    // Zrusi dany token
    //  POZOR, ZDE SE MUSi IMPLEMENTOVAT CELy NOVy SOUBOR, KTERy BUDE OBSHAOVAT FUNKCE MALLOC, FREE, REALLOC, A ZRUSENE
    //  Jedna se o to, ze vsechny data budou v listovem seznamu (viz 1. ukol IAL)

    plusFree(token);
}

void fillToken(tToken * token, tokenType type) {
    // Nastav� typ tokenu
    token->type = type;
}


tToken * getToken(){
    // Pripoji se do souboru a postupne nacte nasledujici token (+ o nem prida informace do struktury tToken)



    char c = '\0'; // inicializovana promenna c s vychozi hodnotou \0

	 

	tToken * token = initToken(); //pomocny token

	tStatus status = LA_START;

	char buffer[32];
	char octalBuffer[3];
	memset(&buffer, 0, 32);
	int i = 0;


	while (TRUE) { // TRUE je definovana jako 1 v .h souboru
		c = fgetc(global.file);
		
		switch(status) {
			case LA_START:	// pocatecni stav automatu
				while(isspace(c)) { 
					c = fgetc(global.file);
				}
				if (c == EOF) {	// EOF	
					token->type = t_eof;
					return token;
				// oddelovac
				} else if (c == 59) { // ;
					token->type = t_semicolon;
                    buffer[i] = c;
					i++;
                    token = updateToken(token, buffer);
					return token;
				// konec oddelovacu
                } else if (c == 44) { // ,
					token->type = t_comma;
                    buffer[i] = c;
					i++;
                    token = updateToken(token, buffer);
					return token;
				// konec oddelovacu
				// zavorky
				} else if (c == 91) { // [
					token->type = t_sq_bracket_l;
                    buffer[i] = c;
					i++;
                    token = updateToken(token, buffer);
					return token;
				} else if (c == 93) { // ]
					token->type = t_sq_bracket_r;
                    buffer[i] = c;
					i++;
                    token = updateToken(token, buffer);
					return token;
				} else if (c == 40) { // (
					token->type = t_bracket_l;
                    buffer[i] = c;
					i++;
                    token = updateToken(token, buffer);
					return token;
				} else if (c == 41) { // )
					token->type = t_bracket_r;
                    buffer[i] = c;
					i++;
                    token = updateToken(token, buffer);
					return token;
				} else if (c == 123) { // {
					token->type = t_brace_l;
                    buffer[i] = c;
					i++;
                    token = updateToken(token, buffer);                    
					return token;
				} else if (c == 125) { // }
					token->type = t_brace_r;
                    buffer[i] = c;
					i++;
                    token = updateToken(token, buffer);
					return token;
				// konec zavorek
				// matematicke operace
				} else if (c == 47) { // /
					status = LA_DIV;
					break;
				} else if (c == 42) { // *
					status = LA_MULTI;
                    buffer[i] = c;
					i++;
					break;
				} else if (c == 43) { // +
					token->type = t_plus;
                    buffer[i] = c;
					i++;
                    token = updateToken(token, buffer);
                    return token;
					break;
				} else if (c == 45) { // -
					token->type = t_minus;
                    buffer[i] = c;
					i++;
                    token = updateToken(token, buffer);
                    return token;
					break;
				} else if (c == 62) { // >
					status = LA_GREATER;
                    buffer[i] = c;
					i++;
					break;
				} else if (c == 60) { // <
					status = LA_LESS;
                    buffer[i] = c;
					i++;
					break;
				} else if (c == 33) { // !
					status = LA_EXCL_MARK;
                    buffer[i] = c;
					i++;
					break;
				} else if (c == 61) { // =
					status = LA_ASSIGNMENT;
                    buffer[i] = c;
					i++;
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
					throwException(1, 0, 0); 
				}
				break;

			// identifikatory
			case LA_SIMPLE_IDENT:
				if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == 95 || c == 36) { // a..z,A..Z,_,$
					buffer[i] = c;
					i++;
				} else if (c == 46) { // something.
					status = LA_COMPLETE_IDENT;
					buffer[i] = c;
					i++;
				} else {
					ungetc(c, global.file);
					token = updateToken(token, buffer);
					keywordCheckToken(token);
					return token;
				}
				break;

			case LA_COMPLETE_IDENT:
				if (buffer[i-1] == 46) {
					if (((!isalpha(c)) && (c != 95) && (c != 36)) || isdigit(c)) {
						throwException(1, 0, 0);
					}
				}
				if (((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c == 95) || (c == 36))) { // a..z,A..Z,_,$
					buffer[i] = c;
					i++;
				} else {
					ungetc(c, global.file);
					token = updateToken(token, buffer);
					token->type = t_complete_ident;
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
					ungetc(c, global.file);
					token = updateToken(token, buffer);
					token->type = t_int;
					return token;	
				}
				break;

			case LA_DOT_DOUBLE:
				if (c >= 48 && c <= 57) { // 0..9
					buffer[i] = c;
					i++;
					status = LA_DOUBLE;
				} else {
					throwException(1, 0, 0); 
                    
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
					ungetc(c, global.file);
					token = updateToken(token, buffer);
					token->type = t_double;
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
					throwException(1, 0, 0); 
				}
				break;

			case LA_DOUBLE_E_SIGN:
				if (c >= 48 && c <= 57) { // 0..9
					buffer[i] = c;
					i++;
					status = LA_DOUBLE_E;
				} else {
					throwException(1, 0, 0); 
				}
				break;

			case LA_DOUBLE_E:
				if (c >= 48 && c <= 57) { // 0..9
					buffer[i] = c;
					i++;
				} else {
					ungetc(c, global.file);
					token = updateToken(token, buffer);
					token->type = t_double_e;
					return token;
				}
				break;

			// string
			case LA_STRING_PREP:
				if (c == 92) { // "\"
					status = LA_BACKSLASH;
				} else if (c == 34) { // ""
					
					token = updateToken(token, buffer);
					token->type = t_string;
					return token;
				} else if (c == EOF) {
					throwException(1, 0, 0);
				} else if (c <= 31) {
					throwException(1, 0, 0);					
				} else { // "xxxxxx
					buffer[i] = c;
					i++;
				}
				break;
			case LA_BACKSLASH:
				if (c == 34) { // "\"
					buffer[i] = '\"';
					i++;
					status = LA_STRING_PREP;
				} else if (c == 92) {
					buffer[i] = '\\';
					i++;
					status = LA_STRING_PREP;
				} else if (c == 110) { // "\n
					buffer[i] = '\n';
					i++;
					status = LA_STRING_PREP;
				} else if (c == 116) { // "\t
					buffer[i] = '\t';
					i++;
					status = LA_STRING_PREP;
				} else if (c >= 48 && c <= 51) { // octalovy cisla -> \0 .. \3
					octalBuffer[0] = c;
					status = LA_OCT1;
				} else {
					throwException(1, 0, 0);
				}
				break;
			case LA_OCT1:
                if (c == 48) {  // 0
					octalBuffer[1] = c;
					status = LA_OCT2_Z;
				} else if (c >= 49 && c <= 55) {   // 1..7
					octalBuffer[1] = c;
					status = LA_OCT2_NZ;
				} else {
					throwException(1, 0, 0);
				}
				break;
			case LA_OCT2_Z:
				if (c >= 49 && c <= 55) {   // 1..7
					octalBuffer[2] = c;
					buffer[i] = c = octToAscii(octalBuffer);
					i++;
					for (int j = 0; j <= 2; j++) {
						octalBuffer[j] = '\0';
					}
					status = LA_STRING_PREP;
				} else {
					throwException(1, 0, 0);
				}
				break;
            case LA_OCT2_NZ:
				if (c >= 48 && c <= 55) {   // 0..7
					octalBuffer[2] = c;
					buffer[i] = c = octToAscii(octalBuffer);
					i++;
					for (int j = 0; j <= 2; j++) {
						octalBuffer[j] = '\0';
					}
					status = LA_STRING_PREP;
				} else {
					throwException(1, 0, 0);
				}
				break;    
			// dalsi porovnani KA
			case LA_GREATER:
				if (c == 61) { // >=
					buffer[i] = c;
					i++;
					token = updateToken(token, buffer);
					token->type = t_greater_eq;
					return token;
				} else {
					ungetc(c, global.file);
					token = updateToken(token, buffer);
					token->type = t_greater;
					return token;
				}
				break;
			case LA_LESS:
				if (c == 61) { // <=
                    buffer[i] = c;
					i++;
					token = updateToken(token, buffer);
					token->type = t_less_eq;
					return token;
				} else {
					ungetc(c, global.file); 
					token = updateToken(token, buffer);
					token->type = t_less;
					return token;
				}
				break;
			case LA_ASSIGNMENT:
				if (c == 61) { // ==
					buffer[i] = c;
					i++;
					token = updateToken(token, buffer);
					token->type = t_comparasion;
					return token;
				} else {
					ungetc(c, global.file);
					token = updateToken(token, buffer);
					token->type = t_assignment;
					return token;
				}
				break;
			case LA_EXCL_MARK:
				if (c == 61) { // !=
					buffer[i] = c;
					i++;
					token = updateToken(token, buffer);
					token->type = t_comparasion_ne;
					return token;
				} else {
					ungetc(c, global.file);
					token = updateToken(token, buffer);
					token->type = t_excl_mark;
					return token;
				}
				break;
			// komentare
			case LA_DIV:
				if (c == 47) { // komentare
					while (TRUE) {
						c = fgetc(global.file);
						if (c == EOF) {
							throwException(1, 0, 0);
						} else if (c == '\n') {
							break;
						}
					}
					
					status = LA_START;
				} else if (c == 42) { /* komentare tohoto typu */
					while (TRUE) {
						c = fgetc(global.file);
						if (c == '\n') {
							
						} else if (c == EOF){
							throwException(1, 0, 0);
						} else if (c == 47) {
							while (TRUE) {
								c = fgetc(global.file);
								if (c == 42) {
									throwException(1, 0, 0);
								} else {
									break;
								}
							}
						} else if (c == 42) {
							while (TRUE) {
								c = fgetc(global.file);
								if (c == 47) {
									status = LA_START;
									break;
								} else if (c == EOF) {
									throwException(1, 0, 0);
								} else {
									if (c == '\n')
										
									continue;
								}
							}
							break;
						} else {
							continue;
						}
					}
				} else {
					buffer[i] = 47;
					ungetc(c, global.file);
					token = updateToken(token, buffer);
					token->type = t_div;
					return token;
				}
				break;
			case LA_MULTI:
				if (c == 47) {
					throwException(1, 0, 0);
				} else {
					ungetc(c, global.file);
					token = updateToken(token, buffer);
					token->type = t_multi;
					return token;
				}
				break;
			default:
				break;
		} // konec switche



		if (i == 31) { // pokud zaplnim buffer, nahraju data do tokenu, prictu delku bufferu a vynuluju buffer
			updateToken(token, buffer);
			for (int j = 0; j < i; j++) {
				buffer[j] = '\0';
			}
			i = 0;
		}

		if (c == EOF) {
			throwException(1, 0, 0);
		}
	} //cyklus

	keywordCheckToken(token);
	updateToken(token, buffer);

	return token;
} //end of function

char octToAscii(char *octalArray) {
	return (octalArray[0]-48)*8*8 + (octalArray[1]-48)*8 + (octalArray[2]-48);
}

void printToken(tToken *token) {
	printf("%20s %25s\n",token->data,tokenTypeString[token->type]);
}
