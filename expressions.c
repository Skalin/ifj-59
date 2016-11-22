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

#include "typedef.h"
#include <math.h>
#include "garbage_collector.h"
#include "expressions.h"
#include "error_handler.h"
#include "stack.h"

#define STR_ERROR   0
#define STR_SUCCESS 1
#define STR_ALLOCATION_SIZE 8  // Udává, kolik bude alokováno na začátku paměti. Pokud načítáme po jednom znaku, dojde k alokaci na násobky tohoto čísla

int precTable[][] = {

//         +    -    *    /    (    )    ID   <    >    <=   >=   ==  !=    !
/* + */  {'G', 'G', 'L', 'L', 'L', 'G', 'L', 'G', 'G', 'G', 'G', 'G', 'G', 'G'},
/* - */  {'G', 'G', 'L', 'L', 'L', 'G', 'L', 'G', 'G', 'G', 'G', 'G', 'G', 'G'},
/* * */  {'G', 'G', 'G', 'G', 'L', 'G', 'L', 'G', 'G', 'G', 'G', 'G', 'G', 'G'},
/* / */  {'G', 'G', 'G', 'G', 'L', 'G', 'L', 'G', 'G', 'G', 'G', 'G', 'G', 'G'},
/* ( */  {'L', 'L', 'L', 'L', 'L', 'E', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L'},
/* ) */  {'G', 'G', 'G', 'G', 'F', 'G', 'F', 'G', 'G', 'G', 'G', 'G', 'G', 'G'},
/* ID */ {'G', 'G', 'G', 'G', 'F', 'G', 'F', 'G', 'G', 'G', 'G', 'G', 'G', 'F'},
/* < */  {'L', 'L', 'L', 'L', 'L', 'G', 'L', 'G', 'G', 'G', 'G', 'G', 'G', 'G'},
/* > */  {'L', 'L', 'L', 'L', 'L', 'G', 'L', 'G', 'G', 'G', 'G', 'G', 'G', 'G'},
/* <= */ {'L', 'L', 'L', 'L', 'L', 'G', 'L', 'G', 'G', 'G', 'G', 'G', 'G', 'G'},
/* >= */ {'L', 'L', 'L', 'L', 'L', 'G', 'L', 'G', 'G', 'G', 'G', 'G', 'G', 'G'},
/* == */ {'L', 'L', 'L', 'L', 'L', 'G', 'L', 'G', 'G', 'G', 'G', 'G', 'G', 'G'},
/* != */ {'L', 'L', 'L', 'L', 'L', 'G', 'L', 'G', 'G', 'G', 'G', 'G', 'G', 'G'},
/* ! */  {'G', 'G', 'G', 'G', 'E', 'G', 'L', 'G', 'G', 'G', 'G', 'G', 'G', 'G'},
  
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
  * FUNKCE PROVÁDĚJÍCÍ SYNTAKTICKOU ANALÝZU VÝRAZU
  */
  
  
}

SString readString(){


	int c = getchar();
	SString str;
	initString(&str);
	int i = 0;


	while (c != EOF || c != '\n') {
		addCharacter(&str, (char) c);
		i++;
		c = getchar();
	}
	addCharacter(&str, '\0');
	return str;
}

void print(char *string) {
	// nejaka podminka kvuli typu vstupu..
	printf("%s", string);

}


int readInt() {
	SString * str;
	initString(str);
	*str = readString();
	int number = 0;
	int i = 0;

	int length = str->length;

	while (str->data[i] != '\0') {
		if (!isdigit(str->data[i])) {
			throwException(7, GlobalRow, GlobalColumn);
		}
		number += (str->data[i]-48) * (int)pow(10,length-i-1);
		i++;
	}
	destroyString(str);
	return number;
}

double readDouble(){
	SString str;
	initString(&str);
	str = readString();
	double doubleNumber = 0.0;
	char *end;

	doubleNumber = strtod(str->data,*end);

	if (*end != NULL || doubleNumber < 0) {
		throwException(7, GlobalRow, GlobalColumn);
	}

	return doubleNumber;
}


SString substr(SString *str, int i, int n) {

	SString *helpStr;
    initString(helpStr);

    while (i <= (i + n)) {
		if (str->data[i] == EOF || isspace(str->data[i])) {
			throwException(10, GlobalRow, GlobalColumn);
		}
        addCharacter(helpStr, str->data[i]);
        i++;
    }

	return ((strLength(helpStr)) == n ? helpStr : throwException(10, GlobalRow, GlobalColumn));
}


int initString(SString *str) {

	if ((plusMalloc(sizeof(SString) + sizeof(char)*STR_ALLOCATION_SIZE)) != NULL) {
		str->data[0] = '\0';
		str->length = 0;
		str->allocatedSize = STR_ALLOCATION_SIZE;
	} else {
		throwException(99,0,0); //chyba alokace paměti
	}


}

int addCharacter(SString *str, char c) {
  
    if ((str->allocatedSize) <= (str->length + 1)) {
		if (plusRealloc(str, sizeof(SString) + (sizeof(char)*(str->allocatedSize))) != NULL) {
			str->allocatedSize = str->length + STR_ALLOCATION_SIZE;
		} else {
			throwException(99,0,0); //chyba alokace paměti
			return STR_ERROR;
		}
	str->data[str->length] = c;
	str->length++;
	str->data[str->length] = '\0';

	return STR_SUCCESS;
	}
}

char *copyString(SString *str1, SString *str2) {

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

int compareString(SString *str1, SString *str2) {
   //porovná dva zadané řetězce str1 a str2 a vrátí celočíselnou hodnotu dle toho, zda je str1 před, roven, nebo za str2
   int result = strcmp(str1->data, str2->data);
   if (result == 0) {
      return result;
   } else if (result < 0) {
      return (result = -1);
   } else {
      return (result = 1);
   }
    
}

int strLength(SString *str) {
	//vrátí délku řetězce (počet znaků) zadaného jedním parametrem str
	int len = str->data;
	return len;

}

bool strEqual(char *str1, char *str2) {
	int equal = !strcmp(str1, str2);
	return equal;
}

void strClear(SString *str) {
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
