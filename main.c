#include "main.h"

static const char *tokenTypeString[] = {
	"t_error","t_int","t_double","t_double_e","t_string","t_simple_ident","t_complete_ident","t_div","t_multi","t_plus","t_minus","t_greater","t_greater_eq","t_less","t_less_eq","t_assignment","t_comparasion","t_excl_mark","t_comparasion_ne","t_sq_bracket_l","t_sq_bracket_r","t_bracket_l","t_bracket_r","t_brace_l","t_brace_r","t_simple_comment","t_block_comment_start","t_block_comment_end","t_semicolon","t_comma","t_eof","t_kw_class","t_kw_static","t_kw_boolean","t_kw_double","t_kw_int","t_kw_string","t_kw_void","t_kw_while","t_kw_for","t_kw_break","t_kw_return","t_kw_continue","t_kw_do","t_kw_if","t_kw_else","t_kw_true","t_kw_false"
};

void printToken(tToken *token) {
	printf("%20s %25s\n",token->data,tokenTypeString[token->type]);
}

int main(int argc, char* argv[]) {
	// Pokud se program spousti se spatnym poctem parametru, ukonci se
	if(argc != 2) {
		throwException(99, 0, 0);
	} else {
		/* Inicializace globalni promenne */
		globalInit();

		/* Otevreni souboru */
		global.file = fopen(global.fileName = argv[1], "r");
		if (global.file == NULL) {
		    throwException(99, 0, 0);
		}
		/* */

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
		//semCheck(iStack);
		//interpretMainCore(iStack);
		/* */

		/* Uvolneni pameti a ukonceni programu*/
		finalFree();
		/* */
	}


		/*****TESTOVÁNÍ LEXU*******************
		tToken *pToken = NULL;

		for (int j = 0; j <= 100; j++){

		pToken = getToken();
		printToken(pToken);
		}

		/*****TESTOVÁNÍ GARBAGE****************
		global.fileName = "testing/test1.ifj";
		global.file = fopen(global.fileName, "r");
		globalInit();

		int alloc[5] =   {16,1,0,6000,20};
		int realloc[5] = {2,1,5,4,0};
		tToken *pToken1 = NULL;
		tToken *pToken2 = NULL;
		tToken *pToken3 = NULL;
		tToken *pToken4 = NULL;
		tToken *pToken5 = NULL;

		pToken1 = plusMalloc(sizeof(tToken) + sizeof(char)*alloc[0]);
		pToken2 = plusMalloc(sizeof(tToken) + sizeof(char)*alloc[1]);
		pToken3 = plusMalloc(sizeof(tToken) + sizeof(char)*alloc[2]);
		pToken1 -> length = alloc[0];
		pToken2 -> length = alloc[1];
		pToken3 -> length = alloc[2];

		pToken3 = plusRealloc(pToken3, sizeof(tToken) + sizeof(char)*(realloc[2]+pToken3->length));
		pToken1 = plusRealloc(pToken1, sizeof(tToken) + sizeof(char)*(realloc[0]+pToken1->length));
		pToken2 = plusRealloc(pToken2, sizeof(tToken) + sizeof(char)*(realloc[1]+pToken2->length));

		plusFree(pToken2);

		pToken4 = plusMalloc(sizeof(tToken) + sizeof(char)*alloc[3]);
		pToken5 = plusMalloc(sizeof(tToken) + sizeof(char)*alloc[4]);
		pToken4 -> length = alloc[3];
		pToken5 -> length = alloc[4];

		pToken4 = plusRealloc(pToken4, sizeof(tToken) + sizeof(char)*(realloc[3]+pToken4->length));
		pToken5 = plusRealloc(pToken5, sizeof(tToken) + sizeof(char)*(realloc[4]+pToken5->length));


		/*************************************
		/*****TESTOVÁNÍ PRECEDENČNÍ ANALÝZY**
		#include "expressions.h"
		(void)argc;
		(void)argv;
		globalInit();
		global.file = fopen("testing/text_precedence.ifj", "r");
		initTree(global.mTree);
		createNewNode("a", var, var_int, 1);



		//struct instrStack dummyInstrStack;
		//global.iStack = instrStackInit(&dummyInstrStack);


		//interpretMainCore(global.iStack);



		************************************/
}



