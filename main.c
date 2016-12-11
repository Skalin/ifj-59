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
/*
		char *str = readString();
		print(str);
*/

            //DELETE THIS
        /*
				void printWhichNodeType(NodeType node) {
					printf("->nodeType: ");
					if (node == var) {
						printf("VAR");
					} else if (node == function) {
						printf("FUNCTION");
					} else if (node == class) {
						printf("CLASS");
					} else {
						printf("TEMP");
					}
					printf(";");

					return;
				}
				void printInstrType(varType type) {
					char *typ = '\0';
					if (type == 0) {
						typ = "int";
					} else if (type == 1) {
						typ = "double";
					} else if (type == 2) {
						typ = "string";
					} else if (type == 4) {
						typ = "void";
					} else {
						typ = "null";
					}
					printf("%s;", typ);
					return;
				}
                // Vytiskne obsah globálního stacku
                char *instrukce[] ={"insIfj16readInt","insIfj16readDouble","insIfj16readString","insIfj16lenght","insIfj16substr","insIfj16compare","insIfj16find","insIfj16sort","insIfj16print","insPlus","insMinus","insMux","insDiv","insPlusTmp","insMinusTmp","insMuxTmp","insDivTmp","insEqual","insNotEqual"," insLess"," insLessOrEqual","insGreater","insGreaterOrEqual","insAssignment","insFunctionCall","insCond","insIf","insIfEnd","insElse","insCondEnd","insWhile","insEndWhile"};
                printf("\nObsah globalniho iStacku:\n");
                for (int i = 0; i<=global.iStack->count; i++) {
					printf("\n\n");
					printf("======================================\n");
					printf("======================================\n");
					Instr *instr = instrStackDataAt(global.iStack,i);
                    printf("PRINT ALL NODES FROM THREEADDRESSED CODE:\n\tid3 = %s;\tid1 = %s;\tid2 = %s;\ttype = %s;\n",nodePrint(instr->Id3),nodePrint(instr->Id1),nodePrint(instr->Id2),instrukce[instr->type]);
					printf("\nPRINT SELECT NODES ON SEPARATE LINES:\n");

					printf("============ id3 ============\n");
					if (instr->Id3 != NULL) {
						printf("\n\tid3->key: %s;\t", instr->Id3->key);
						if (instr->Id3->nodeType == var) {
							printf("\n\tid3");
							printWhichNodeType(instr->Id3->nodeType);
							printf("\n\tid3->type: ");
							printInstrType(instr->Id3->data.type);
							printf("\n\tid3->val: ");
							if (instr->Id3->data.type == var_int) {
								printf("%d", instr->Id3->data.value.intValue);
							} else if (instr->Id3->data.type == var_double) {
								printf("%f", instr->Id3->data.value.doubleValue);
							} else if (instr->Id3->data.type == var_string) {
								printf("%s", instr->Id3->data.value.stringValue);
							}
							printf(";\n");
						} else if ( instr->Id3->nodeType == function) {
							printf("\n\tid3");
							printWhichNodeType(instr->Id3->nodeType);
							printf("\nid3->type: ");
							printInstrType(instr->Id3->data.type);
							printf("\n");
						} else if ( instr->Id3->nodeType == class) {
							printf("\n\tid3");
							printWhichNodeType(instr->Id3->nodeType);
							printf("\nid3->type: ");
							printInstrType(instr->Id3->data.type);
							printf("\n");
						} else {
							printf("\n\tid3");
							printWhichNodeType(instr->Id3->nodeType);
							printf("\n");
						}
					} else if (instr->Id3 == NULL) {
						printf("\tid3: NULL;\n");
					}

					printf("\n============ id1 a id2 ============\n");
					if (instr->Id1 != NULL) {
						printf("\n\tid1->key: %s;\t", instr->Id1->key);
						if (instr->Id1->nodeType == var) {
							printf("\n\tid1");
							printWhichNodeType(instr->Id1->nodeType);
							printf("\n\tid1->type: ");
							printInstrType(instr->Id1->data.type);
							printf("\n\tid1->val: ");
							if (instr->Id1->data.type == var_int) {
								printf("%d", instr->Id1->data.value.intValue);
							} else if (instr->Id1->data.type == var_double) {
								printf("%f", instr->Id1->data.value.doubleValue);
							} else if (instr->Id1->data.type == var_string) {
								printf("%s", instr->Id1->data.value.stringValue);
							}
							printf(";\n");
						} else if ( instr->Id1->nodeType == function) {
							printf("\n\tid1");
							printWhichNodeType(instr->Id1->nodeType);
							printf("\n\tid1->type: ");
							printInstrType(instr->Id1->data.type);
							printf("\n");
						} else if (instr->Id1->nodeType == class) {
							printf("\n\tid1");
							printWhichNodeType(instr->Id1->nodeType);
							printf("\n\tid1->type: ");
							printInstrType(instr->Id1->data.type);
							printf("\n");
						} else {
							printf("\n\tid1");
							printWhichNodeType(instr->Id1->nodeType);
							printf("\n");
							printf("\n\tid1->val: ");
							if (instr->Id1->data.type == var_int) {
								printf("%d", instr->Id1->data.value.intValue);
							} else if (instr->Id1->data.type == var_double) {
								printf("%f", instr->Id1->data.value.doubleValue);
							} else if (instr->Id1->data.type == var_string) {
								printf("%s", instr->Id1->data.value.stringValue);
							}
							printf(";\n");
						}
					} else if (instr->Id1 == NULL) {
						printf("\n\tid1: NULL;\n");
					}
					if (instr->Id2 != NULL) {
						printf("\n\tid2->key: %s;\t", instr->Id2->key);
						if (instr->Id2->nodeType == var) {
							printf("\n\tid2");
							printWhichNodeType(instr->Id2->nodeType);
							printf("\n\tid2->type: ");
							printInstrType(instr->Id2->data.type);
							printf("\n\tid2->val: ");
							if (instr->Id2->data.type == var_int) {
								printf("%d", instr->Id2->data.value.intValue);
							} else if (instr->Id2->data.type == var_double) {
								printf("%f", instr->Id2->data.value.doubleValue);
							} else if (instr->Id2->data.type == var_string) {
								printf("%s", instr->Id2->data.value.stringValue);
							}
							printf(";\n");
						} else if ( instr->Id2->nodeType == function) {
							printf("\n\tid2");
							printWhichNodeType(instr->Id2->nodeType);
							printf("\n\tid2->type: ");
							printInstrType(instr->Id2->data.type);
							printf("\n");
						} else if ( instr->Id2->nodeType == class) {
							printf("\n\tid2");
							printWhichNodeType(instr->Id2->nodeType);
							printf("\n\tid2->type: ");
							printInstrType(instr->Id2->data.type);
							printf("\n");
						} else {
							printf("\n\tid2");
							printWhichNodeType(instr->Id2->nodeType);
							printf("\n");
						}
					} else if (instr->Id2 == NULL) {
						printf("\n\tid2: NULL;\n");
					}
                }
            //END DELETE
			printStack(global.iStack);
			invertStack(global.iStack);
			printStack(global.iStack);
            */
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
