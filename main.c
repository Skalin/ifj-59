#include <string.h>
#include "error_handler.h"
#include "garbage_collector.h"
#include "parser.h"
#include "interpret.h"
#include <unistd.h>


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
			// nic
		}

		//printf("dostal jsem se az k podmince mezi testem a normalnim prekladacem");

		if (global.DEBUG == 0) { // normalni funkce programu
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
		} else {
			// DEBUG aplikace s testy

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
			printf("Vysortovany string \"%s\"\n", printedString);

			globalInit();
			global.DEBUG = 1;
			// IAL testy
			char lex[] = "./testing/lex";
			char syntax[] = "./testing/synt";
			char sem[] = "./testing/sem";
			char *help;

			sleep(3);


			// lex test
			int i = 1;
			char *id = '\0';
			help = lex;
			strcat(help, "01.ifj16");
			sleep(3);
			global.file = fopen(global.fileName = "lex", "r");
			if (global.file == NULL) {
				throwException(99, 0, 0);
			} // jasna chyba programu, soubor "lex" neexistuje, mel by program skoncit
			printf("vracim se z exceptionu c.1");

			sleep(3);

			globalInit();
			global.DEBUG = 1;
			global.file = fopen(global.fileName = help, "r");
			if (global.file == NULL) {
				throwException(99, 0, 0);
			}
			// chyba by nemela nastat, soubor existuje

			pParse(); // chyba by mela nastat zde, dojde k lex chybe

			sleep(3);
			// syntax testy
			globalInit();
			global.DEBUG = 1;
			help = syntax;
			while (i < 8) {
				if (i != 1) {
					globalInit();
					global.DEBUG = 1;
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
			global.DEBUG = 1;
			help = sem;
			i = 1;
			while (i < 47) {

				i++;
			}


			sleep(3);

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
