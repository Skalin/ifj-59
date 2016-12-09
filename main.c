#include <string.h>
#include "error_handler.h"
#include "garbage_collector.h"
#include "parser.h"
#include "interpret.h"
#include "instrstack.h"

mainTree mTree;


int main(int argc, char* argv[]) {
	// Pokud se program spousti se spatnym poctem parametru, ukonci se
	if(argc != 2) {
		throwException(99, 0, 0);
	} else {
		globalInit();


		// Otevreni souboru
		//printf("%s", argv[1]);
		/*global.file = fopen(global.fileName = argv[1], "r");
		if (global.file == NULL) {
			throwException(99, 0, 0);
		}
		printf("%s", argv[1]);*/

		printf("Jsem pred initem stromu\n");
		initTree(&mTree);
		printf("Jsem za initem stromu\n");

		mTree.root = plusMalloc(sizeof(BTSNode));
		mTree.root = NULL;
		mTree.actFunction = plusMalloc(sizeof(BTSNode));
		mTree.actFunction = NULL;
		mTree.actClass = plusMalloc(sizeof(BTSNode));
		mTree.actClass = NULL;
		// globalni init


        BTSNode *pokusnode = createNewNode("trida",class,var_null,1,1);
        BTSNode *pokusnode2 = createNewNode("promena",var,var_int,1,1);
        BTSNode *pokusnode6 = createNewNode("funkce",function,var_int,1,1);
        BTSNode *pokusnode7 = createNewNode("promenafunkce1",var,var_int,0,1);
        BTSNode *pokusnode8 = createNewNode("promenafunkce2",var,var_int,0,1);
        BTSNode *pokusnode9 = createNewNode("promenafunkce3",var,var_int,0,1);
        BTSNode *pokusnode10 = createNewNode("promenafunkce4",var,var_int,0,1);
        BTSNode *pokusnode11 = createNewNode("promenafunkce5",var,var_int,0,1);
        BTSNode *pokusnode4 = createNewNode("trida2",class,var_null,1,1);
        BTSNode *pokusnode3 = createNewNode("promena2",var,var_int,1,1);
        pokusnode =searchForNode("promennafunkce5", var, mTree.actFunction->variables);
            
            
            //printf("node=|%s|\n",nodePrint(pokusnode));
            
            printf("root %s\n",mTree.root->key);
        printf("root->rptr%s\n",mTree.root->rptr->key);
            printf("root->actClass %s\n",mTree.actClass->key);
    
		printf("Jsem pred parserem\n");

			
			// Parser
			pParse();
            

            //DELETE THIS
                // Vytiskne obsah globálního stacku
                char *instrukce[] ={"insIfj16readInt","insIfj16readDouble","insIfj16readString","insIfj16lenght","insIfj16substr","insIfj16compare","insIfj16find","insIfj16sort","insIfj16print","insPlus","insMinus","insMux","insDiv"," insEqual","insNotEqual"," insLess"," insLessOrEqual","insGreater","insGreaterOrEqual","insAssignment","insFunctionCall","insCond","insIf","insIfEnd","insElse","insCondEnd","insWhile","insEndWhile"};
                printf("\nObsah globálního iStacku:\n");
                for (int i = 0; i<=global.iStack->count; i++) {
                    Instr *instr = instrStackDataAt(global.iStack,i);
                    //printf("  id3=%4s  id1=%4s  id2=%4s  typ=%s\n",nodePrint(instr->Id3),nodePrint(instr->Id1),nodePrint(instr->Id2),instrukce[instr->type]);
                }
            //END DELETE

            
            // TISK STROMU
            //Print_tree(mTree);

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
