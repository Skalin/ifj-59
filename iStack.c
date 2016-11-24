/**
 * IFJ/IAL - Stack pro instrukce
 * Varianta:    b/2/I
 * Soubor:      iStack.c
 * Tým:         59
 * Autoři:      Jan Hrbotický, xhrbot01@stud.fit.vutbr.cz
 *              Dominik Skála, xskala11@stud.fit.vutbr.cz
 *              Milan Hruban, xhruba08@stud.fit.vutbr.cz
 *              Martin Hons, xhonsm00@stud.fit.vutbr.cz
 *              David Hél, xhelda00@stud.fit.vutbr.cz
 */


#include "garbage_collector.h"
#include "error_handler.h"
#include "typedef.h"
#include "iStack.h"
#include "stack.h"
#include "ial.h"

instrStack * instrStackInit (instrStack *stc ) {

    //Inicializace polozek stacku
    stc = plusMalloc(sizeof(instrStack));
    stc->dataInstr = plusMalloc(sizeof(void) * 30);
    stc->alloc = 30;
    stc->count = 0;

    return stc;
}

Instr *instrItemInit (Instr *stc) {

	stc->Id1 = NULL;
	stc->Id2 = NULL;
	stc->Id3 = NULL;
	
	Instr * itemNew;
	itemNew = plusMalloc(sizeof(tStackIt));

	if (itemNew != NULL) {
		return;
	} 
	
	else {
        	throwException(99,0,0); //chyba alokace paměti
    	}

	InstrType * instrNew;
	instrNew = plusMalloc(sizeof(tToken));

	if (instrNew != NULL) {
        	return;
	} 
	
	else {
		throwException(99,0,0); //chyba alokace paměti
	}

	inintString(&instrNew);
	itemNew->type = instrNew;
	return itemNew;
}

int instrStackEmpty (const instrStack* stc) {

    return(stc->count == 0 ? 1 : 0); // Pokud je vrchol zasobniku mensi jak nula
}

int instrStackFull (const instrStack* stc) {

    return(stc->alloc < (s->count+1) ? 1 : 0); // Pokud se stav zasobniku rovna max kapacite, vrati se 1
}


void instrStackPush (instrStack *stc, void *data) {

    // Pokud uz neni dostatek alokovane pameti, provede se realloc
    if(instrStackFull(stc)) {
        stc->data = plusRealloc(stc->data, (sizeof(void *) * (stc->alloc+30)));
        stc->alloc += 30;
    }
    //Na vrchol zasobniku vlozime data
    stc->count++;
    stc->data[stc->count] = data;
}

Instr * instrStackTop (instrStack *stc) {

    //Pokud jsou v zasobniku data, vrat data na vrcholu
    if (!instrStackEmpty(stc)) {
	stc->dataInstr[stc->count + 1];
	stc->count--;
        //Jinak vrat null
    } else {
        return NULL;
    }
}



void instrStackPop (instrStack *stc) {

	if (!instrStackEmpty(stc))
	stc->count--;
}

int instrStackSize (instrStack *stc) {
	return stc->count;
}

void instrStackDestroy (instrStack *stc) {

    while (instrStackSize(stc) > 0) {
		instrStack *tmp = stc;
		stc = tmp->type;
		plusFree(tmp);
    }

}

void instrItemDestroy (Instr *data) {

    plusFree(data->type);
    plusFree(data);
}
