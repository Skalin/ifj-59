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
#include "stack.h"
#include "typedef.h"
#include "garbage_collector.h"
#include "expressions.h"

tStack * stackInit ( tStack *stack ) {
    //Inicializace polozek stacku
    tStack *stack = plusMalloc(sizeof(tStack));
    stack->data = plusMalloc(sizeof(void) * 30);
    stack->allocated = 30;
    stack->counter = 0;

    return stack;
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

tStackIt *anotherToken (tToken *token) {
	
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
	
}

void moveToAnotherStack(tStack *stc1, tStack *stc2)
{
    tStackIt * tmp;
    tmp = stackPop(stc1);
	
    while (!stackEmpty(stc1))
    {
		if (tmp != NULL) {
            stackPush(stc2, tmp);  //pushnutí na druhý zásobník
			}
        
        else {   
            throwException(2,0,0); //sytaktická chyba
		}
	}
}

int isTerm (int typeIt) {
    return (typeIt < /**/); ///TODO - DOPLNIT TERMINÁL
}

int topTerm (tStack *stc) {
	
    tStackIt *item; 
    item = stc->data;

    while (item != NULL) {
	    
        if (isTerm(item->typeIt)) {
            return item->typeIt;
        }
	    
        item = item->typeIt;
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

