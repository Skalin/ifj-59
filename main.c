#include "main.h"

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


		// IAL testy
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

			finalFree();
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
