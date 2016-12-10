#include <string.h>
#include "error_handler.h"
#include "garbage_collector.h"
#include "parser.h"
#include "interpret.h"
#include "instrstack.h"
#include "expressions.h"

mainTree mTree;


int main(int argc, char* argv[]) {
	// Pokud se program spousti se spatnym poctem parametru, ukonci se
	if(argc != 2) {
		throwException(99, 0, 0);
	} else {
		globalInit();


		// Otevreni souboru
		global.file = fopen(global.fileName = argv[1], "r");
		if (global.file == NULL) {
			throwException(99, 0, 0);
		}

		initTree(&mTree);

		mTree.root = plusMalloc(sizeof(BTSNode));
		mTree.root = NULL;
		mTree.actFunction = plusMalloc(sizeof(BTSNode));
		mTree.actFunction = NULL;
		mTree.actClass = plusMalloc(sizeof(BTSNode));
		mTree.actClass = NULL;
		// globalni init

        // Parser
        pParse();
            

            //DELETE THIS
                // Vytiskne obsah globálního stacku
                char *instrukce[] ={"insIfj16readInt","insIfj16readDouble","insIfj16readString","insIfj16lenght","insIfj16substr","insIfj16compare","insIfj16find","insIfj16sort","insIfj16print","insPlus","insMinus","insMux","insDiv","insPlusTmp","insMinusTmp","insMuxTmp","insDivTmp","insEqual","insNotEqual"," insLess"," insLessOrEqual","insGreater","insGreaterOrEqual","insAssignment","insFunctionCall","insCond","insIf","insIfEnd","insElse","insCondEnd","insWhile","insEndWhile"};
                printf("\nObsah globálního iStacku:\n");
                for (int i = 0; i<=global.iStack->count; i++) {
                    Instr *instr = instrStackDataAt(global.iStack,i);
                    printf("  id3=%8s  id1=%8s  id2=%8s  typ=%s\n",nodePrint(instr->Id3),nodePrint(instr->Id1),nodePrint(instr->Id2),instrukce[instr->type]);
                }
            //END DELETE

			// Interpret
			semCheck(global.iStack);
			interpretMainCore(global.iStack);

			// Uvolneni pameti a ukonceni programu
			finalFree();
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
