/**
 * IFJ/IAL - Garbage collector
 * Varianta:    b/2/I
 * Soubor:       garbage_collector.c
 * Tým:         59
 * Autoři:      Jan Hrbotický, xhrbot01@stud.fit.vutbr.cz
 *              Dominik Skála, xskala11@stud.fit.vutbr.cz
 *              Milan Hruban, xhruba08@stud.fit.vutbr.cz
 *              Martin Hons, xhonsm00@stud.fit.vutbr.cz
 *              David Hél, xhelda00@stud.fit.vutbr.cz
 */
#include "garbage_collector.h"
#include "error_handler.h"

// Globální proměnná
struct tGlobal global;

//Funkce alokuje paměť a zařadí nově alokovanou položku do listu
void * plusMalloc(unsigned int length) {
    // Pokud existuje nějaký prvek
    if (global.wholeList->dataPointer != NULL || global.wholeList != global.listLast ) {
        global.listLast->nextPtr = malloc(sizeof(struct GarbageList));
        //Pokud došlo k chybě při alokaci, vyhoď vyjímku
        if(global.listLast->nextPtr == NULL)
            throwException(99,0,0);
        global.listLast = global.listLast->nextPtr;
    }
    void * newItem = (global.listLast->dataPointer = malloc(length));
    // Pokud došlo k chybě při alokaci, vyhoď vyjímku
    if(newItem == NULL)
        throwException(99,0,0);
    global.listLast->nextPtr = NULL;

    // Vrať ukazatel na nově alokovanou paměť
    return newItem;
}

void * plusRealloc(void * destPtr,unsigned int length) {

    // Pomocná proměnná
    struct GarbageList * tmp = global.wholeList;

    // Pokud je v listu ještě nějaký prvek
    while(tmp != NULL) {
        // Pokud se nejedná o daný prvek, vezmi následující prvek a opakuj cyklus
        if(tmp->dataPointer != destPtr) {
            tmp = tmp->nextPtr;
            continue;
        }
        // Pokud je prvek nalezen, reallocuj paměť a vrať pointer na novou paměť
        tmp->dataPointer = realloc(tmp->dataPointer, length);
        return tmp->dataPointer;
    }
    // Pokud prvek v listu není, vrať NULL
    return NULL;
}

void globalInit() {
    global.wholeList = malloc(sizeof(struct GarbageList));
    if(global.wholeList == NULL)
        throwException(99,0,0);

	global.wholeList->nextPtr = NULL;

    global.listLast = global.wholeList;
    global.wholeList->dataPointer = NULL;
}

void plusFree(void * memoryPtr) {
        // Pomocné proměnné
        struct GarbageList* tmp = global.wholeList;
        struct GarbageList* previous = tmp;

        // Dokud se nedostanu na konec seznamu
        while(tmp != NULL) {
            // Pokud naleznu daný prvek, vymažu ho
            if(tmp->dataPointer == memoryPtr) {
                // Pokud se nejedná o poslední prvek
                if(tmp->nextPtr != NULL) {
                    // Pokud se jedná o první prvek
                    if(previous == tmp) 
                        global.wholeList = tmp->nextPtr;
                    else
                        previous->nextPtr = tmp->nextPtr;
                }
                //Pokud se jedná o poslední prvek
                else {
                    global.listLast = previous;
                    previous->nextPtr = NULL;
                    /*
                    if(previous == tmp)
                        tmp->dataPointer = NULL;
                    else
                        free(tmp);
                    */
                }
                    free(tmp);
                    break;
            }
            // Jinak pokračuju
            previous = tmp;
            tmp = tmp->nextPtr;
        }

        if (memoryPtr != NULL) {
            memoryPtr = NULL;
            free(memoryPtr);
        }
}

void finalFree() {
    // Pomocné proměnné
    struct GarbageList * tmp;
    struct GarbageList * tmp2 = global.wholeList;

    // Dokud neprojdu celý seznam
    while(tmp2 != NULL) {
        // Pokud jsou navázána data, uvolni prvek
        if(tmp2->dataPointer != NULL)
            free(tmp2->dataPointer);
        // Posun na další prvek
        tmp = tmp2;
        tmp2 = tmp2->nextPtr;
        //A uvolnění prvku
        free(tmp);
    }
    //Zavření souboru
    if(global.file != NULL)
        fclose(global.file);

}

