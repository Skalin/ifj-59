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

tStack * stackInit ( tStack *stack ) {
    //Inicializace polozek stacku
    tStack *stack = plusMalloc(sizeof(tStack));
    stack->data = plusMalloc(sizeof(void) * 30);
    stack->allocated = 30;
    stack->counter = 0;

    return stack;
}

int stackEmpty ( const tStack* s ) {
    return(s->counter == 0 ? 1 : 0); // Pokud je vrchol zasobniku mensi jak nula
}

int stackFull ( const tStack* s ) {
    return(s->allocated < (s->counter+1) ? 1 : 0); // Pokud se stav zasobniku rovna max kapacite, vrati se 1
}

void stackPush ( tStack *stack, void *data ) {
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

void stackPop ( tStack *stack ) {
    if (!stackEmpty(stack))
        stack->counter--;
}

int stackSize (tStack *stack) {
    return stack->counter;
}