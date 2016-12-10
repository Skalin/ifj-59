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
#include "typedef.h"
#include "error_handler.h"
#include "instrstack.h"


void instrStackInit(instrStack *stc) {

    //Inicializace polozek stacku
	stc->count = -1;
	stc->alloc = 30;
	stc->dataInstr = plusMalloc(sizeof(Instr) * 30);
	
	if(stc->dataInstr == NULL) {
		throwException(99,0,0); //chyba alokace paměti
	}
	
}

Instr *instrItemInit () {

	Instr * itemNew;
	itemNew = plusMalloc(sizeof(Instr));

	if (itemNew == NULL) {
		throwException(99,0,0); //chyba alokace paměti
	} 
	
	else {
		InstrType * instrNew;
		instrNew = plusMalloc(sizeof(InstrType));
		itemNew->type = *instrNew;
        itemNew->Id1 = NULL;
        itemNew->Id2 = NULL;
        itemNew->Id3 = NULL;
		return itemNew;
    }
	return NULL;
}

int instrStackEmpty(const instrStack* stc) {

    return(stc->count == -1 ? 1 : 0); // Pokud je vrchol zasobniku mensi jak nula
}

int instrStackFull(const instrStack* stc) {

    return(stc->alloc < (stc->count+1) ? 1 : 0); // Pokud se stav zasobniku rovna max kapacite, vrati se 1
}


void instrStackPush(instrStack *stc, Instr *data) {

    // Pokud uz neni dostatek alokovane pameti, provede se realloc
    if(instrStackFull(stc)) {
        stc->dataInstr = plusRealloc(stc->dataInstr, (sizeof(void *) * (stc->alloc+30)));
        stc->alloc += 30;
    }
    //Na vrchol zasobniku vlozime data
    stc->count++;
    stc->dataInstr[stc->count] = data;
}

Instr * instrStackTop(instrStack *stc) {
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
Instr * instrStackDataAt(instrStack *stc, int n) {
	//Pokud jsou v zasobniku data, vrat data na vrcholu
	if (!instrStackEmpty(stc)) {
		// pokud je pocet prvku mensi nez hledany prvek, vratim NULL, jinak vratime prvek
		if (stc->count < n) {
			return NULL;
		} else {
			return stc->dataInstr[n];
		}
		//Jinak vrat null
	} else {
		return NULL;
	}
}
// PRO DEJVA, ZKONTROLOVAT, PRIPADNE OPRAVIT
// FUNKCE POSUNE VRCHOL ZASOBNIKU NA NTOU HODNOTU. Kterou nejprve dostanu pomoci instrStackSize a pak se tam na tu hodnotu potrebuju vratit
void getBackTo(instrStack *stc, int n) {
	stc->count = n;
}

// Funcke zkopiruje obsah jednoho zasobniku do druheho, jednu položku po druhé
void instrStackCopy(instrStack *originalStc, instrStack *copiedStc) {

	int i = 0;
	while (i < originalStc->count) {
		instrStackPush(copiedStc, originalStc->dataInstr[i]);
		i++;
	}
}

void instrStackPop(instrStack *stc) {

	if (!instrStackEmpty(stc))
	stc->count--;
}

int instrStackSize(instrStack *stc) {
	return stc->count;
}

void instrItemDestroy(instrStack *data) {

    plusFree(data->dataInstr);
    plusFree(data);
}
