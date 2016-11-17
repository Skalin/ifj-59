/**
 * IFJ/IAL - Precedenční analýza
 * Varianta:    b/2/I
 * Soubor:      expressions.c
 * Tým:         59
 * Autoři:      Jan Hrbotický, xhrbot01@stud.fit.vutbr.cz
 *              Dominik Skála, xskala11@stud.fit.vutbr.cz
 *              Milan Hruban, xhruba08@stud.fit.vutbr.cz
 *              Martin Hons, xhonsm00@stud.fit.vutbr.cz
 *              David Hél, xhelda00@stud.fit.vutbr.cz
 */

#include <stdio.h>
#include <math.h>
#include "expressions.h"
#include "error_handler.h"
#include "garbage_collector.h"

#define STR_ERROR   1
#define STR_SUCCESS 0
#define STR_ALLOCATION_SIZE 8  // Udává, kolik bude alokováno na začátku paměti. Pokud načítáme po jednom znaku, dojde k alokaci na násobky tohoto čísla

int precTable[][] = {

  
   };

int getRule (tStack *stack, int next) {
  /*
  * FUNKCE KONTROLUJÍCÍ PRAVIDLA.
  * stack - zásobník terminálů a nonterminálů
  * dalším parametrem funkce by mělo by to, které pravidlo je teďka na řadě
   * Prepisuji teda arg.2 na "next", typ arg. je treba domyslet, ale int to asi nebude, i kdyz by teoreticky mohl byt (int next by rikal o kolik poli dal se posunout)
  */
  
  };


int precedAnalysis (FILE *filename) {
  /*
  * FUNKCE PROVÁDĚJÍCÍ SYTAKTICKOU ANALÝZU VÝRAZU
  */
  
  
  };

int readInt() {
	char *c;
	int size = 30;

	while (fgets(c, size, stdin) != NULL) {
		size += size;
	}

	int j = 0;
	while((c[j] != '\0' || c[j] != EOF || c[j] != '\n') && j < size) {
		if (isdigit(c[j])) {
			j++; // real size
		} else {
			throwException(7, GlobalRow, GlobalColumn);
		}
	}

	int number = 0;
	int i = j;
	while (j > 0) {
		number += (c[j]-48)*pow(10,(i-j));// pridat nasobeni mocnin desiti
		j--;
	}
	return number;
}

double readDouble() {
	char *c;
	int size = 30;

	while (fgets(c, size, stdin) != NULL) {
		size += size;
	}
	int j = 0;

	SStr *str = initString(SStr *str);
	while((c[j] != '\0' || c[j] != EOF || c[j] != '\n') && j < size) {
		addCharacter(*str, c[j]);
		j++;
	}

}

SStr readString() {

	char *c;
	int size = 30;

	while (fgets(c, size, stdin) != NULL) {
		size += size;
	}
	int j = 0;

	SStr *str = initString(SStr *str);

	while((c[j] != '\0' || c[j] != EOF || c[j] != '\n') && j < size) {
		addCharacter(*str, c[j]);
		j++;
	}


	return *str->data;


}

void print(/* term nebo konkatenace */) {
	// nejaka podminka kvuli typu vstupu..
	printf("%s", helpPtr->data);

}

SStr substr(SStr *str, int i, int n) {

    SStr helpStr = initString(SStr *helpStr);

    while (i <= (i + n)) {
		if (str->data[i] == EOF || isspace(str->data[i])) {
			throwException(10, GlobalRow, GlobalColumn);
		}
        addCharacter(helpStr, str->data[i]);
        i++;
    }

	return ((strLength(helpStr)) == n ? helpStr : throwException(10, GlobalRow, GlobalColumn));
}


int initString(SStr *str) {
    
	if ((plusMalloc(sizeof(SString) + sizeof(char)*STR_ALLOCATION_SIZE)) != NULL) {
		str->data[0] = '\0';
		str->length = 0;
		str->allocatedSize = STR_ALLOCATION_SIZE;
	} else {
		throwException(99,0,0); //chyba alokace paměti
	}
  
}

int addCharacter(SStr *str, char c) {
  
    if ((str->allocatedSize) <= (str->length + 1)) {
		if (plusRealloc(str, sizeof(SString) + (sizeof(char)*(str->allocatedSize))) != NULL) {
			str->allocatedSize = str->length + STR_ALLOCATION_SIZE;
		} else {
			throwException(99,0,0); //chyba alokace paměti
			return STR_ERROR;
		}
	} else {
			str->data[str->length] = c;
			str->length++;
			str->data[str->length] = '\0';
        
			return STR_SUCCESS;
	}
}

char *copyString(SStr *str1, SStr *str2) {

	if (str2->allocatedSize < strLength(str1)) {
		if (plusRealloc(str2, sizeof(SString) + (sizeof(char)*(str2->allocatedSize))) != NULL) {
			str2->allocatedSize = str2->length + STR_ALLOCATION_SIZE;
		} else {
			throwException(99,0,0); //chyba alokace paměti
			return STR_ERROR;
		}
	}
	strClear(str2);
	str2->length = str1->length;
	str2->data = str1->data;

	return str2;
}

int compareString(SStr *str1, SStr *str2) {
	//porovná dva zadané řetězce str1 a str2 a vrátí celočíselnou hodnotu dle toho, zda je str1 před, roven, nebo za str2
	int result;
	result = strcmp(str1->data, str2->data);
	return result;
    
}

int strLength(SStr *str) {
	//vrátí délku řetězce (počet znaků) zadaného jedním parametrem str
	int len = str->data;
	return len;

}

void strClear(SStr *str) {
	// funkce sloužící k vymazání řetězce
	str->length = 0;
	str->data[0] = '\0';
}

void destroyString (SString *str) {
	// funkce k uvolnění z paměti
	if (str != NULL) {
	  plusFree(str->data);
	}
}
