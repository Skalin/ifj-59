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

char precTable[][] = {

//         +    -    *    /    (    )    ID   <    >    <=   >=   ==  !=    !
/* + */  {'>', '>', '<', '<', '<', '>', '<', '>', '>', '>', '>', '>', '>', '>'},
/* - */  {'>', '>', '<', '<', '<', '>', '<', '>', '>', '>', '>', '>', '>', '>'},
/* * */  {'>', '>', '>', '>', '<', '>', '<', '>', '>', '>', '>', '>', '>', '>'},
/* / */  {'>', '>', '>', '>', '<', '>', '<', '>', '>', '>', '>', '>', '>', '>'},
/* ( */  {'<', '<', '<', '<', '<', '=', '<', '<', '<', '<', '<', '<', '<', '<'},
/* ) */  {'>', '>', '>', '>', 'F', '>', 'F', '>', '>', '>', '>', '>', '>', '>'},
/* ID */ {'>', '>', '>', '>', 'F', '>', 'F', '>', '>', '>', '>', '>', '>', 'F'},
/* < */  {'<', '<', '<', '<', '<', '>', '<', '>', '>', '>', '>', '>', '>', '>'},
/* > */  {'<', '<', '<', '<', '<', '>', '<', '>', '>', '>', '>', '>', '>', '>'},
/* <= */ {'<', '<', '<', '<', '<', '>', '<', '>', '>', '>', '>', '>', '>', '>'},
/* >= */ {'<', '<', '<', '<', '<', '>', '<', '>', '>', '>', '>', '>', '>', '>'},
/* == */ {'<', '<', '<', '<', '<', '>', '<', '>', '>', '>', '>', '>', '>', '>'},
/* != */ {'<', '<', '<', '<', '<', '>', '<', '>', '>', '>', '>', '>', '>', '>'},
/* ! */  {'>', '>', '>', '>', '=', '>', '<', '>', '>', '>', '>', '>', '>', '>'},
  
   };
 
void expression(tExpType expType) {   
    // Inicializujeme zásobník a vložíme na něj znak ';' 
    tStack *stack = NULL;
    stack = stackInit(stack);
    
    tToken *token = initToken();
    token = fillToken(token, t_semicolon);
    
    tStackIt *item = itemInit();
    item->dataIt = token;
    item->typeIt = TERM;
    stackPush(stack,item);
    
    token = getToken();
    while (1) {
        /* Vyskočí z cyklu, pokud topTerm je roven ';' a
         *   jedná se o podmínku a na vstupu je ')'
         *   nebo se jedná o argument a na vstupu je ',' nebo ')'
         *   nebo se jedná o přiřazení a na vstupu je ';'
         *   (v posledním případě před vyskočením ještě vygeneruje instrukci) 
         */
        if (topTerm()->dataIt->type == t_semicolon) {
            if (((tExpType == expCond) && (token->type == t_bracket_r)) ||
                ((tExpType == expArg) && ((token->type == t_comma) || (token->type == t_bracket_r))) ||
                ((tExpType == expAssign) && (token->type == t_semicolon)))
                break;
        }
        
        switch (getPrec()) { // TODO
            case '<':
                // Vloží znak '<' na zásobník
                tToken *lessToken = initToken();
                lessToken = fillToken(lessToken, t_less);
                item = itemInit();
                item->dataIt = lessToken;
                item->typeIt = NONTERM;
                stackPush(stack,item);
                
                // Vloží aktuální token na zásobník
                item = itemInit();
                item->dataIt = token;
                item->typeIt = TERM;
                stackPush(stack,item);
                
                //Načte nový token
                token = getToken();
                break;
            case '=':
                // Vloží aktuální token na zásobník
                item = itemInit();
                item->dataIt = token;
                item->typeIt = TERM;
                stackPush(stack,item);
                
                //Načte nový token
                token = getToken();
                break;
            case '>':
                tStackIt *handle[3] = chnToExp(stack);
                reduceExp(handle);
                break;
            default:
                // Syntaktická chyba
                throwException(2,0,0);
                break;
        }
    }
    // TODO uvolnit paměť
}

// Načte handle a najde pravidla E -> i a E -> (E)
tStackIt *chnToExp(tStack *stack) {
    int i = 0;
    tStackIt *handle[3];
    
    // Čteme ze zásobníku dokud nenarazíme na NONTERM
    while (topItemType() != NONTERM) {
        i++;
        // Pokud je handle větší než 3, vyvoláme syntaktickou chybu
        if (i > 3) throwException(2,0,0);
        handle[i] = stackTop(stack);
        stackPop(stack);
    }
    
    // Odstraníme ze zásobníku začátek handle '<'
    stackPop(stack);
      
    // Pravidlo E -> id
    if ((i == 1) && (handle[0]->typeIt == TERM) && (handle[0]->data->type >= t_simple_ident) && (handle[0]->typeIt <= t_string)) {
        handle[0]->typeIt = EXPR;
        
        /*TOMUHLE NEROZUMÍM ALE MOŽNÁ TO TU MÁ BÝT (zřejmě je to uložení identifikátoru)
        copyString(&item->dataIt->attribute,&handle[0]->dataIt->attribute); */
    }
    // Pravidlo E -> (E)
    else if ((i == 3) && (handle[0]->data->type == t_bracket_l) && (handle[1]->data->type >= t_simple_ident) && (handle[1]->typeIt <= t_string) && (handle[2]->data->type == t_bracket_r)) {
        handle[0]->typeIt = EXPR;    
    }
    /* TOMUHLE TAKY NEROZUMÍM ALE MOŽNÁ TO TU MǍ BÝT   
    else {
        addCharacter(&item->dataIt->attribute, 'E');
    }*/
    
    stackPush(stack,handle[0]);
    return handle;
}

void reduceExp(tStackIt *handle[3]) {
    Instr *instr = instrItemInit();
        
    // Jedná se o aritmetickou nebo porovnávací instrukci
    if ((handle[0]->typeIt == EXPR) && (handle[2]->typeIt == EXPR)) {
        switch (handle[1]->dataIt->type) {
            case t_plus: // E -> E+E
                instr->type = insPlus;
                break;
            case t_minus: // E -> E-E
                instr->type = insMinus;
                break;
            case t_mul: // E -> E*E
                instr->type = insMux;
                break;
            case t_div: // E -> E/E
                instr->type = insDiv;
                break;
            case t_comparasion: // E -> E==E
                instr->type = insEqual;
                break;
            case t_comparasion_ne: // E -> E!=E
                instr->type = insNotEqual;
                break;
            case t_less: // E -> E<E
                instr->type = insLess;
                break;    
            case t_less_eq: // E -> E<=E
                instr->type = insLessOrEqual;
                break;
            case t_greater: // E -> E>E
                instr->type = insGreater;
                break;
            case t_greater_eq: // E -> E>=E
                instr->type = insGreaterOrEqual;
                break;     
            default: // Syntaktická chyba
                throwException(2,0,0); 
                break;
        }
    } 
    // E -> (E)
    else if () {
        
    } 
    // Syntaktická chyba
    else {
        throwException(2,0,0); 
    }
    instrStackPush(iStack,instr);
}

int initString(SString *str) {
    
    if (plusMalloc(sizeof(SString) + sizeof(char)*STR_ALLOCATION_SIZE) != NULL) {
		str->data[0] = '\0';
		str->length = 0;
		str->allocatedSize = STR_ALLOCATION_SIZE;
		return 1;
	} else {
		throwException(99,0,0); //chyba alokace paměti
 	}
}

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

	SString *str = initString(SString *str);
	while((c[j] != '\0' || c[j] != EOF || c[j] != '\n') && j < size) {
		addCharacter(str, c[j]);
		j++;
	}

}

SString readString() {

	char *c;
	int size = 30;

	while (fgets(c, size, stdin) != NULL) {
		size += size;
	}
	int j = 0;

	SString *str = initString(SString *str);

	while((c[j] != '\0' || c[j] != EOF || c[j] != '\n') && j < size) {
		addCharacter(str, c[j]);
		j++;
	}


	return *str;


}

void print(/* term nebo konkatenace */) {
	// nejaka podminka kvuli typu vstupu..
	printf("%s", helpPtr->data);

}

SString substr(SString *str, int i, int n) {

    SString helpStr = initString(SString *helpStr);

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
