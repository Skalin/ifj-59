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

#include "expressions.h"
#include "error_handler.h"
#include "garbage_collector.h"

#define STR_ERROR   1
#define STR_SUCCESS 0
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

int getRule (tStack *stack, int something) {
  /*
  * FUNKCE KONTROLUJÍCÍ PRAVIDLA.
  * stack - zásobník terminálů a nonterminálů
  * dalším parametrem funkce by mělo by to, které pravidlo je teďka na řadě
  */
  
  };


int precedAnalysis (FILE *filename) {
  /*
  * FUNKCE PROVÁDĚJÍCÍ SYTAKTICKOU ANALÝZU VÝRAZU
  */
  
  
  };
  


int inintString (SStr *str) {
    
    if (plusMalloc(sizeof(SString) + sizeof(char)*STR_ALLOCATION_SIZE)) != NULL) {
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
                    return STR_ERROR;
                 }
         }
    
    else {
             str->data[str->length] = c;
             str->length++;
             str->data[str->length] = '\0';
        
             return STR_SUCCESS;
         }
}

int compareString(SStr *str1, SStr *str2) {
   //porovná dva zadané řetězce str1 a str2 a vrátí celočíselnou hodnotu dle toho, zda je str1 před, roven, nebo za str2
   int = strcmp(str1->data, str2->data);
   if (result == 0) {
      return result;
   } else if (result < 0) {
      return (result = -1);
   } else {
      return (result = 1);
   }
    
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
   if (str != NULL){
      plusFree(str->data);
   }
}
