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


#include "error_handler.h"
#include "instrstack.h"
#include "typedef.h"


instrStack * instrStackInit (instrStack *stc ) {

    //Inicializace polozek stacku
    stc = plusMalloc(sizeof(instrStack));
    stc->dataInstr = plusMalloc(sizeof(instrStack) * 30);
    stc->alloc = 30;
    stc->count = 0;

    return stc;
}

Instr *instrItemInit (Instr *stc) {

	stc->Id1 = NULL;
	stc->Id2 = NULL;
	stc->Id3 = NULL;
	
	Instr * itemNew;
	itemNew = plusMalloc(sizeof(Instr));

	if (itemNew != NULL) {
		return NULL;
	} 
	
	else {
        	throwException(99,0,0); //chyba alokace paměti
    	}

	InstrType * instrNew;
	instrNew = plusMalloc(sizeof(InstrType));

	if (instrNew != NULL) {
        	return NULL;
	} 
	
	else {
		throwException(99,0,0); //chyba alokace paměti
	}

	// Tohle si zkontroluj. Původně tu bylo itemNew->type = instrNew;
	itemNew->type = *instrNew;
	return itemNew;
}

int instrStackEmpty (const instrStack* stc) {

    return(stc->count == 0 ? 1 : 0); // Pokud je vrchol zasobniku mensi jak nula
}

int instrStackFull (const instrStack* stc) {

    return(stc->alloc < (stc->count+1) ? 1 : 0); // Pokud se stav zasobniku rovna max kapacite, vrati se 1
}


void instrStackPush (instrStack *stc, Instr *data) {

    // Pokud uz neni dostatek alokovane pameti, provede se realloc
    if(instrStackFull(stc)) {
        stc->dataInstr = plusRealloc(stc->dataInstr, (sizeof(void *) * (stc->alloc+30)));
        stc->alloc += 30;
    }
    //Na vrchol zasobniku vlozime data
    stc->count++;
    stc->dataInstr[stc->count] = data;
}

Instr * instrStackTop (instrStack *stc) {
    //Pokud jsou v zasobniku data, vrat data na vrcholu
    if (!instrStackEmpty(stc)) {
        int counter = stc->count+1;
        stc->count--;
		return stc->dataInstr[counter];
    //Jinak vrat null
    } else {
        return NULL;
    }
}
// PRO DEJVA, ZKONTROLOVAT, PRIPADNE OPRAVIT
// Funkce vrati instrukci na pozici n
Instr * instrStackDataAt (instrStack *stc, int n) {
	//Pokud jsou v zasobniku data, vrat data na vrcholu
	if (!instrStackEmpty(stc)) {
		return stc->dataInstr[n];
		//Jinak vrat null
	} else {
		return NULL;
	}
}
// PRO DEJVA, ZKONTROLOVAT, PRIPADNE OPRAVIT
// FUNKCE POSUNE VRCHOL ZASOBNIKU NA NTOU HODNOTU. Kterou nejprve dostanu pomoci instrStackSize a pak se tam na tu hodnotu potrebuju vratit
void getBackTo (instrStack *stc, int n) {
	stc->count = n;
}


void instrStackPop (instrStack *stc) {

	if (!instrStackEmpty(stc))
	stc->count--;
}

int instrStackSize (instrStack *stc) {
	return stc->count;
}


void instrItemDestroy (instrStack *data) {

    plusFree(data->dataInstr);
    plusFree(data);
}
