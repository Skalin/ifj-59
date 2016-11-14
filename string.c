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
#include "garbage_collector.h"

#define STR_ERROR   1
#define STR_SUCCESS 0
#define STR_ALLOCATION_SIZE 8  // Udává, kolik bude alokováno na začátku paměti. Pokud načítáme po jednom znaku, dojde k alokaci na násobky tohoto čísla


int inintString (SStr *str) {
    
    if ((str->data = (char*) malloc(STR_ALLOCATION_SIZE)) != NULL) {
      str->data[0] = '\0';
      str->length = 0;
      str->allocatedSize = STR_ALLOCATION_SIZE;
    }
  
    else {
      throwException(99,0,0); //chyba alokace paměti
     } 
  
}

int addCharacter (SStr *str, char c) {
  
    if ((str->allocatedSize) <= (str->length + 1))
        {
            if (plusRealloc(string, sizeof(SString) + (sizeof(char)*(str->allocatedSize))) != NULL) {
                   str->allocatedSize = str->length + STR_ALLOCATION_SIZE;
                }
            
            else {
                    throwException(99,0,0); //chyba alokace paměti 
                }
         }
    
    else {
             str->data[str->length] = c;
             str->length++;
             str->data[str->length] = '\0';
         }
}

int compareString(SStr *str1, SStr *str2) {
  
  
}


int addStr(SStr *str1, SStr *str2) {
  
  
}

void strClear(SStr *str)
// funkce sloužící k vymazání řetězce
{
   str->length = 0;
   str->data[0] = '\0';
}

void destroyString (SString *str) {
// funkce k uvolnění z paměti   
    if (str != NULL){
      free(str->data);
    }
}
