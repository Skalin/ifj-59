/**
 * IFJ/IAL - Nekonečně dlouhé řetězce
 * Varianta:    b/2/I
 * Soubor:      string.h
 * Tým:         59
 * Autoři:      Jan Hrbotický, xhrbot01@stud.fit.vutbr.cz
 *              Dominik Skála, xskala11@stud.fit.vutbr.cz
 *              Milan Hruban, xhruba08@stud.fit.vutbr.cz
 *              Martin Hons, xhonsm00@stud.fit.vutbr.cz
 *              David Hél, xhelda00@stud.fit.vutbr.cz
 */


#ifndef STRING
#define STRING

#include <string.h>

typedef struct SStr{
  char *data;		   
  int length;		        // délka řetězce
  int allocatedSize;	  // alokovaná paměť
} SString;

//FUNKCE VIZ ZADÁNÍ STR 9!!!!!!!!!!!!!!!!!!!!

int inintString (SStr *str);
int addCharacter (SStr *str, char c);
int compareString (SStr *str1, SStr *str2);
int strLength(SStr *str);
void strClear(SStr *str)
void destroyString (SString *str);

#endif
