#include <string.h>
#include <malloc.h>
#include "error_handler.h"
#include "garbage_collector.h"
#include "parser.h"
#include "interpret.h"

mainTree mTree;


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
			} else if (strcmp(argv[2], "DEBUG") == 0) {
			// Inicializace globalni promenne v pripade debug verze aplikace
				globalInit();
				global.DEBUG = 1;
			} else {
				// navrat chyby ve stavu kdy jako treti parameter dorazi blbost
				throwException(99, 0, 0);
			}
		} else {
			globalInit();
			// nic
		}

		//printf("dostal jsem se az k podmince mezi testem a normalnim prekladacem");

		if (global.DEBUG == 0) { // normalni funkce programu

			printf("Jsem pred initem\n");
			initTree(&mTree);

			mTree.root = plusMalloc(sizeof(BTSNode));
			mTree.root = NULL;
			mTree.actFunction = plusMalloc(sizeof(BTSNode));
			mTree.actFunction = NULL;
			mTree.actClass = plusMalloc(sizeof(BTSNode));
			mTree.actClass = NULL;
	//kde to pada?
			createNewNode("main", class, var_null, 1, 0);
			printf("Jsem po prvni node\n");
			createNewNode("blbost", var, var_string, 1, 0);
			printf("Jsem po druhe node\n");
			createNewNode("blbost2", var, var_int, 1, 1);
			printf("Jsem po treti node\n");
			createNewNode("blbost3", var, var_int, 1, 1);
			createNewNode("asdf", var, var_double, 1, 1);

			searchForNode("asdf", var, mTree.root);

            printf("\x1B[35mROOT: %p\n",mTree.root);
            printf("ROOT->lprt: %p\n",mTree.root->lptr);
            printf("ROOT->rprt: %p\n\x1B[0m",mTree.root->rptr);

			printf("dostal jsem se za globalinit");
			// Otevreni souboru
			//printf("%s", argv[1]);
			global.file = fopen(global.fileName = argv[1], "r");
			if (global.file == NULL) {
				throwException(99, 0, 0);
			}

			// Parser
			pParse();
            

            //DELETE THIS
                // Vytiskne obsah globálního stacku
                char *instrukce[] ={"insIfj16readInt","insIfj16readDouble","insIfj16readString","insIfj16lenght","insIfj16substr","insIfj16compare","insIfj16find","insIfj16sort","insIfj16print","insPlus","insMinus","insMux","insDiv"," insEqual","insNotEqual"," insLess"," insLessOrEqual","insGreater","insGreaterOrEqual","insAssignment","insFunctionCall","insCond","insIf","insIfEnd","insElse","insCondEnd","insWhile","insEndWhile"};
                printf("\nObsah globálního iStacku:\n");
                for (int i = 0; i<=global.iStack->count; i++) {
                    Instr *instr = instrStackDataAt (global.iStack,i);
                    printf("  id3=%4s  id1=%4s  id2=%4s  typ=%s\n",nodePrint(instr->Id3),nodePrint(instr->Id1),nodePrint(instr->Id2),instrukce[instr->type]);
                }
            //END DELETE

            
            // TISK STROMU
            Print_tree(mTree);

			// Interpret
			semCheck(global.iStack);
			interpretMainCore(global.iStack);


			// Uvolneni pameti a ukonceni programu
			finalFree();
		} else {
			// DEBUG aplikace s testy vestavenych funkci
/*
			// test stringu a jejich sortovani
			char testString[] = "ultrasupermegasupersonicstring";
			char testString2[] = "vysortovat";
			char testString3[] = "posun";
			char testString4[] = "boyle-moore";
			char testString5[] = "Barbora";
			// test vyhledavani
			char hledej[] = "onic";
			char hledej1[] = "bor";
			char hledej2[] = "vat";
			char hledej3[] = "n";
			char hledej4[] = "\0";
			char hledej5[] = "ajfkaojfkaljflkaafafaafa";

			int where = 0;

			where = find(testString5, hledej1);
			printf("Substring \"%s\" byl nalezen ve slove \"%s\" na pozici: %d\n", hledej1, testString5, where);
			where = find(testString, hledej);
			printf("Substring \"%s\" byl nalezen ve slove \"%s\" na pozici: %d\n", hledej, testString, where);
			where = find(testString2, hledej2);
			printf("Substring \"%s\" byl nalezen ve slove \"%s\" na pozici: %d\n", hledej2, testString2, where);
			where = find(testString3, hledej3);
			printf("Substring \"%s\" byl nalezen ve slove \"%s\" na pozici: %d\n", hledej3, testString3, where);
			where = find(testString4, hledej4);
			printf("Substring \"%s\" byl nalezen ve slove \"%s\" na pozici: %d\n", hledej4, testString4, where);
			where = find(testString, hledej5);
			printf("Substring \"%s\" byl nalezen ve slove \"%s\" na pozici: %d\n", hledej5, testString, where);


			char *printedString = testString;
			printf("Originalni string \"%s\" ", testString);
			printedString = sort(printedString);
			printf("Vysortovany string \"%s\"\n", printedString);
			printedString = testString2;
			printf("Originalni string \"%s\" ", testString2);
			printedString = sort(printedString);
			printf("Vysortovany string \"%s\"\n", printedString);
			printedString = testString3;
			printf("Originalni string \"%s\" ", testString3);
			printedString = sort(printedString);
			printf("Vysortovany string \"%s\"\n", printedString);
			printedString = testString4;
			printf("Originalni string \"%s\" ", testString4);
			printedString = sort(printedString);
			printf("Vysortovany string \"%s\"\n", printedString);
			printedString = testString5;
			printf("Originalni string \"%s\" ", testString5);
			printedString = sort(printedString);
			printf("Vysortovany string \"%s\"\n", printedString);


			where = find(testString5, hledej1);
			printf("Substring \"%s\" byl nalezen ve slove \"%s\" na pozici: %d\n", hledej1, testString5, where);
			where = find(testString, hledej);
			printf("Substring \"%s\" byl nalezen ve slove \"%s\" na pozici: %d\n", hledej, testString, where);
			where = find(testString2, hledej2);
			printf("Substring \"%s\" byl nalezen ve slove \"%s\" na pozici: %d\n", hledej2, testString2, where);
			where = find(testString3, hledej3);
			printf("Substring \"%s\" byl nalezen ve slove \"%s\" na pozici: %d\n", hledej3, testString3, where);
			where = find(testString4, hledej4);
			printf("Substring \"%s\" byl nalezen ve slove \"%s\" na pozici: %d\n", hledej4, testString4, where);
			where = find(testString, hledej5);
			printf("Substring \"%s\" byl nalezen ve slove \"%s\" na pozici: %d\n", hledej5, testString, where);


			printedString = testString;
			printf("Originalni string \"%s\" ", testString);
			printedString = sort(printedString);
			printf("Vysortovany string \"%s\"\n", printedString);
			printedString = testString2;
			printf("Originalni string \"%s\" ", testString2);
			printedString = sort(printedString);
			printf("Vysortovany string \"%s\"\n", printedString);
			printedString = testString3;
			printf("Originalni string \"%s\" ", testString3);
			printedString = sort(printedString);
			printf("Vysortovany string \"%s\"\n", printedString);
			printedString = testString4;
			printf("Originalni string \"%s\" ", testString4);
			printedString = sort(printedString);
			printf("Vysortovany string \"%s\"\n", printedString);
			printedString = testString5;
			printf("Originalni string \"%s\" ", testString5);
			printedString = sort(printedString);
			printf("Vysortovany string \"%s\"\n", printedString);*/
			fprintf(stderr, "==========================================================================\n" );
			fprintf(stderr, "========================== PROBEHNE HLAVNI TEST ==========================\n" );
			fprintf(stderr, "======================= TEST JEDNOTLIVYCH SOUBORU! =======================\n\n" );


			globalInit();
			//printf("dostal jsem se za globalinit");
			// Otevreni souboru
			//printf("%s", argv[1]);
			global.file = fopen(global.fileName = argv[1], "r");
			if (global.file == NULL) {
				throwException(99, 0, 0);
			}


			// Parser
			pParse();
            
        
			// Interpret
			semCheck(global.iStack);
			interpretMainCore(global.iStack);


			// Uvolneni pameti a ukonceni programu
			finalFree();

			return 0;
		}
	}
}



/* TESTOVÁNÍ EXPRESSIONS - prosím nemazat jen zakomentovat */
/*
int main(int argc, char* argv[]) {

    // Inicializace globalni promenne
    globalInit();
    global.fileName = "tests/fac_rec.ifj";

	// Otevreni souboru
	global.file = fopen(global.fileName, "r");
	if (global.file == NULL) {
	    throwException(99, 0, 0);
	}


	// Inicializace hlavnich struktur prekladace
	
	initTree(&mTree);
	instrStack iStack;
	instrStackInit(&iStack);


		// Parser
	pParse();
		//

		// Interpret
	semCheck(&iStack);
	interpretMainCore(&iStack);
		//

		// Uvolneni pameti a ukonceni programu
	finalFree();
		//
	
}

*/
