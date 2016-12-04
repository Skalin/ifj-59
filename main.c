#include "main.h"
#include <stdlib.h>

extern mainTree mTree;

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
			// Inicializace globalni promenne v pripade nedebug verze aplikace
			globalInit();
		};
		if (global.DEBUG == 0) { // normalni funkce programu
			// Otevreni souboru
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
		} else {

			// test stringu a jejich sortovani
			String testString = "kokot";
			String testString2 = "vysortovat";
			String testString3 = "posun";
			String testString4 = "boyle-moore";
			String printedString;
			// test vyhledavani
			String hledej = "kot";
			String hledej2 = "vat";
			String hledej3 = "n";
			String hledej4 = "";
			String hledej5 = "ajfkaojfkaljflka";

			int where = 0;

			where = find(testString, hledej);
			printf("%d", where);
			where = find(testString2, hledej2);
			printf("%d", where);
			where = find(testString3, hledej3);
			printf("%d", where);
			where = find(testString4, hledej4);
			printf("%d", where);
			where = find(testString, hledej5);
			printf("%d", where);


			printedString = sort(testString);
			printf(printedString);

			printedString = sort(testString2);
			printf(printedString);

			printedString = sort(testString3);
			printf(printedString);

			printedString = sort(testString4);
			printf(printedString);
/*
			globalInit();
			// IAL testy
			String lex = "./testing/lex";
			String syntax = "./testing/synt";
			String sem = "./testing/sem";
			String help;


			// lex test
			int i = 1;
			String id;
			help = lex;
			strcat(help, "01.ifj16");
			global.file = fopen(global.fileName = lex, "r");
			if (global.file == NULL) {
				throwException(99, 0, 0);
			} // jasna chyba programu, soubor "lex" neexistuje, mel by program skoncit


			globalInit();
			global.file = fopen(global.fileName = help, "r");
			if (global.file == NULL) {
				throwException(99, 0, 0);
			}
			// chyba by nemela nastat, soubor existuje

			pParse(); // chyba by mela nastat zde, dojde k lex chybe

			// syntax testy
			globalInit();
			help = syntax;
			while (i < 8) {
				if (i != 1) {
					globalInit;
				}
				help = syntax;
				sprintf(id, "%d", i);
				strcat(help, id);
				strcat(help, ".ifj16");
				global.file = fopen(global.fileName = help, "r");
				printf("FILE: %s", global.fileName);
				pParse(); //melo by navratit chybu 2, vzdy
				i++;
			}

			// semantika testy

			globalInit();
			help = sem;
			i = 1;
			while (i < 47) {

				i++;
			}


			finalFree();
			*/
		}
	}
}



/* TESTOVÁNÍ EXPRESSIONS - prosím nemazat jen zakomentovat */
/*
int main(int argc, char* argv[]) {

    // Inicializace globalni promenne
    globalInit();
    global.fileName = "testing/fac_rec.ifj";

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
