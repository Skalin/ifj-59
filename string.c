/**
 * IFJ/IAL - Nekonečné řetezce
 * Varianta:    b/2/I
 * Soubor:      string.c
 * Tým:         59
 * Autoři:      Jan Hrbotický, xhrbot01@stud.fit.vutbr.cz
 *              Dominik Skála, xskala11@stud.fit.vutbr.cz
 *              Milan Hruban, xhruba08@stud.fit.vutbr.cz
 *              Martin Hons, xhonsm00@stud.fit.vutbr.cz
 *              David Hél, xhelda00@stud.fit.vutbr.cz
 */


#include <string.h>
#include "string.h"
#include "error_handler.h"

#define STR_ERROR   1
#define STR_SUCCESS 0
#define STR_ALLOCATION_SIZE 8  // Udává, kolik bude alokováno na začátku paměti. Pokud načítáme po jednom znaku, dojde k alokaci na násobky tohoto čísla


int inintString (SStr *str) {
    
    if ((str->data = (char*) malloc(STR_ALLOCATION_SIZE)) == NULL) {
      throwException(11,0,0); //chyba alokace paměti
    }
  
    else {
      str->data[0] = '\0';
      str->length = 0;
      str->allocatedSize = ALLOC_SIZE;
     } 
  
}

int addCharacter (SStr *str, char c) {
  
  
}

int compareString(SSt *str1, SString *str2) {
  
  
}


int addStr(string *str1, string *str2) {
  
  
}


void destroyString (SString *str) {
    
    if (str != NULL){
      free(str->data);
    }
}
