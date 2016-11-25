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
#include "error_handler.h"
#include "garbage_collector.h"
#include "stack.h"


tStack * stackInit ( tStack *stack ) {

    //Inicializace polozek stacku
    stack = plusMalloc(sizeof(tStack));
    stack->data = plusMalloc(sizeof(void*) * 30);
    stack->allocated = 30;
    stack->counter = 0;
    return stack;
}

tStackTmp * stackInitTmp (tStackTmp *stack2) {

    //Inicializace polozek stacku
    stack2 = plusMalloc(sizeof(tStackTmp));
    stack2->data2 = plusMalloc(sizeof(void*) * 30);
    stack2->allocated2 = 30;
    stack2->counter2 = 0;
    return stack2;
}

tStackIt *itemInit () {

	tStackIt * itemNew;
	itemNew = plusMalloc(sizeof(tStackIt));

	if (itemNew != NULL) {
		return NULL;
	} else {
		throwException(99,0,0); //chyba alokace paměti
	}

	tToken * tokenNew;
	tokenNew = plusMalloc(sizeof(tToken));

	if (tokenNew != NULL) {
		return NULL;
	} else {
		throwException(99,0,0); //chyba alokace paměti
	}

	initString(&tokenNew->attribute);
	itemNew->dataIt = tokenNew;
	return itemNew;

}

void stackDestroy(tStack *stc) {

	plusFree(stc);

}

void itemDestroy (tStackIt *data) {
		
	plusFree(data->dataIt);
	plusFree(data);

}

void exprShift (tStack *stc1, tStack *stc2) {

	tStackIt * tmp;
	tmp = stackPop(stc1);

	while (!stackEmpty(stc1) || stc1->data[stc1->counter]->typeIt == EXPR || stc1->data[stc1->counter]->typeIt == NONTERM) {
		if (tmp != NULL) {
			stackPush(stc2, tmp);  //pushnutí na druhý zásobník
		} else {
			throwException(2,0,0); //sytaktická chyba
		}
	}
}


tokenType topTerm (tStack *stc) {

	while ((stc->data[stc->counter])->typeIt == EXPR || (stc->data[stc->counter])->typeIt == NONTERM)
		stc->counter--;
		return (stc->data[stc->counter]->dataIt->type);
}


int stackEmpty (const tStack* s) {

	// Pokud je vrchol zasobniku mensi jak nula
	return(s->counter == 0 ? 1 : 0);
}

int stackFull (const tStack* s) {

	// Pokud se stav zasobniku rovna max kapacite, vrati se 1
	return(s->allocated < (s->counter+1) ? 1 : 0);
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

tStackIt * stackTop (tStack *stack) {

	//Pokud jsou v zasobniku data, vrat data na vrcholu
	if(!stackEmpty(stack))
		return(stack->data[stack->counter+1]);
	//Jinak vrat null
	else
		return NULL;
}

tStackIt * stackPop (tStack *stack) {

	tStackIt *tmp = NULL;

	if (!stackEmpty(stack))
		tmp = stack->data[stack->counter];
		stack->counter--;
		return tmp;
}

int stackSize (tStack *stack) {

	return stack->counter;
}

