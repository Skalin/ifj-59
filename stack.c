/**
 * IFJ/IAL - Stack
 * Varianta:    b/2/I
 * Soubor:      stack.c
 * Tým:         59
 * Autoři:      Jan Hrbotický, xhrbot01@stud.fit.vutbr.cz
 *              Dominik Skála, xskala11@stud.fit.vutbr.cz
 *              Milan Hruban, xhruba08@stud.fit.vutbr.cz
 *              Martin Hons, xhonsm00@stud.fit.vutbr.cz
 *              David Hél, xhelda00@stud.fit.vutbr.cz
 */

#include "typedef.h"
#include "garbage_collector.h"
#include "stack.h"
#include "expressions.h"

typedef enum {
	EXPRESSION,
	NONTERMINAL, 
	TERMINAL,
} ExprType;

tStack * stackInit ( tStack *stack ) {
    //Inicializace polozek stacku
    tStack *stack = plusMalloc(sizeof(tStack));
    stack->data = plusMalloc(sizeof(void) * 30);
    stack->allocated = 30;
    stack->counter = 0;

    return stack;
}

tStackTmp * stackInit (tStackTmp *stack ) {
    //Inicializace polozek stacku
    tStackTmp *stack = plusMalloc(sizeof(tStack));
    stack->data2 = plusMalloc(sizeof(void) * 30);
    stack->allocated2 = 30;
    stack->counter2 = 0;

    return stack2;
}

tStackIt *itemInit () {
    
    tStackIt * itemNew;
    itemNew = plusMalloc(sizeof(tStackIt));
    
    if (itemNew != NULL) {
        return;
    }
    
    else {
        throwException(99,0,0); //chyba alokace paměti
        }
    
    tToken * tokenNew; 
    tokenNew = plusMalloc(sizeof(tToken));
    
    if (tokenNew != NULL) {
        return;
    }
    
    else {
        throwException(99,0,0); //chyba alokace paměti
        }
    
    inintString(&tokenNew->attribute);
    itemNew->dataIt = tokenNew;
    return itemNew;
    
}

void stackDestroy (tStack *stc) {
		
	while (stackSize(stc) > 0) {
		tStack *tmp = stc;
		stc = tmp->dataIt;
		plusFree(tmp);
	}	
	
}

void itemDestroy (tItem *data) {
		
	plusFree(data->dataIt);	
	plusFree(data);	
	
}

void exprShift (tStack *stc1, tStackTmp *stc2) {
   	 
	tToken * tmp;
	tToken *item;
	tmp = stackPop(stc1);
	item = stc1->data->counter->typeIt;
		
   	while (!stackEmpty(stc1) || item == EXPRESSION || item == NONTERMINAL)
    	{
		if (tmp != NULL) {
            		stackPush(stc2, tmp);  //pushnutí na druhý zásobník
		}
        
        	else {   
            		throwException(2,0,0); //sytaktická chyba
		}
	}
}

/*
tStackIt *anotherToken (tToken *token) {
	
	tStackIt *tmp = NULL;
	tmp = itemInit();
	
	if (tmp == NULL) {
		throwException(99,0,0); //chyba alokace paměti	
	}
	
	else if (tmp != NULL) {
		
		getToken(token);
		copyString();
		
		tmp->typeIt = TERMINAL;
		return tmp;
	}		
}*/



int isTerm (int typeIt) {
    return (typeIt < EXPRESSION);
}

int topTerm (tStack *stc) {
	
    tStackIt *item; 
    item = stc->data->typeIt;

    while (item == EXPRESSION || item == NONTERMINAL) {
	    
        if (isTerm(item->typeIt)) {
            return item->type;
        }
	    
        item = item->type;
        }
    }
}

int stackEmpty (const tStack* s) {
    return(s->counter == 0 ? 1 : 0); // Pokud je vrchol zasobniku mensi jak nula
}

int stackFull (const tStack* s) {
    return(s->allocated < (s->counter+1) ? 1 : 0); // Pokud se stav zasobniku rovna max kapacite, vrati se 1
}

void stackPush (tStack *stack, void *data) {
    // Pokud uz neni dostatek alokovane pameti, provede se realloc
    if(stackFull(stack)) {
        stack->data = plusRealloc(stack->data, (sizeof(void *) * (stack->allocated+30)));
        stack->allocated += 30;
    }
    //Na vrchol zasobniku vlozime data
    stack->counter++;
    stack->data[stack->counter] = data;
}

void * stackTop (tStack *stack) {
    //Pokud jsou v zasobniku data, vrat data na vrcholu
    if(!stackEmpty(stack))
        return(stack->data[stack->counter+1]);
    //Jinak vrat null
    else
        return NULL;
}

void stackPop (tStack *stack) {
    if (!stackEmpty(stack))
        stack->counter--;
}

int stackSize (tStack *stack) {
    return stack->counter;
}

