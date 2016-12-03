#include "main.h"

static const char *tokenTypeString[] = {
	"t_error","t_int","t_double","t_double_e","t_string","t_simple_ident","t_complete_ident","t_div","t_multi","t_plus","t_minus","t_greater","t_greater_eq","t_less","t_less_eq","t_assignment","t_comparasion","t_excl_mark","t_comparasion_ne","t_sq_bracket_l","t_sq_bracket_r","t_bracket_l","t_bracket_r","t_brace_l","t_brace_r","t_simple_comment","t_block_comment_start","t_block_comment_end","t_semicolon","t_comma","t_eof","t_kw_class","t_kw_static","t_kw_boolean","t_kw_double","t_kw_int","t_kw_string","t_kw_void","t_kw_while","t_kw_for","t_kw_break","t_kw_return","t_kw_continue","t_kw_do","t_kw_if","t_kw_else","t_kw_true","t_kw_false"
};

void printToken(tToken *token) {
	printf("%20s %25s\n",token->data,tokenTypeString[token->type]);
}
/*
int main(int argc, char* argv[]) {
	// Pokud se program spousti se spatnym poctem parametru, ukonci se
	if(argc < 2) {
		throwException(99, 0, 0);
	} else {

 		if (argc > 3) {
 			throwException(99, 0, 0);
 		} else if (argc == 3) {
			if (strcmp(argv[2], "NONDEBUG") == 0) {
			// Inicializace globalni promenne v pripade nedebug verze aplikace
				globalInit();
				global.DEBUG = 0;
			} else if (strcmp(argv[2], "DEBUG") == 0) {
			// Inicializace globalni promenne v pripade debug verze aplikace
				globalInit();
				global.DEBUG = 1;
			} else {
				// navrat chyby ve stavu kdy jako treti parameter dorazi blbost
				throwException(99, 0, 0);
			}
		} else {
			// Inicializace globalni promenne v pripade nedebug verze aplikace
			globalInit();
			global.DEBUG = 0;
		};

		// Otevreni souboru 
		global.file = fopen(global.fileName = argv[1], "r");
		if (global.file == NULL) {
		    throwException(99, 0, 0);
		}
		

		// Inicializace hlavnich struktur prekladace 
		mainTree mTree;
		initTree(&mTree);
		instrStack iStack;
		instrStackInit(&iStack);
		

		// Parser 
		pParse();
		

		// Interpret 
		semCheck(&iStack);
		interpretMainCore(&iStack);
		

		// Uvolneni pameti a ukonceni programu
		finalFree();
	
	}
}
*/


/* TESTOVÁNÍ EXPRESSIONS - prosím nemazat jen zakomentovat */
int main(int argc, char* argv[]) {

    /* Inicializace globalni promenne */
    globalInit();
    global.fileName = "testing/fac_rec.ifj";

	/* Otevreni souboru */
	global.file = fopen(global.fileName, "r");
	if (global.file == NULL) {
	    throwException(99, 0, 0);
	}


	/* Inicializace hlavnich struktur prekladace */
	mainTree mTree;
	initTree(&mTree);
	instrStack iStack;
	instrStackInit(&iStack);
		/* */

		/* Parser */
	pParse();
		/* */

		/* Interpret */
	semCheck(&iStack);
	interpretMainCore(&iStack);
		/* */

		/* Uvolneni pameti a ukonceni programu*/
	finalFree();
		/* */
	
}


