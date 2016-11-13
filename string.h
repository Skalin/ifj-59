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

SString * initString ();

//FUNKCE VIZ ZADÁNÍ STR 9!!!!!!!!!!!!!!!!!!!!

int addCharacter (SStr *str, char c);
int writeString (SStr *str, char *str2);
int strCmpString(SSt *str1, SString *str2);
int strAddStr(string *str1, string *str2);
void destroyString (SString *str);

#endif
