/*
 * IFJ/IAL - Lexikální analyzátor
 * Varianta:    b/2/I
 * Subor:       garbage_collector.c
 * Tým:         59
 * Autoři:      Jan Hrbotický, xhrbot01@stud.fit.vutbr.cz
 *              Dominik Skála, xskala11@stud.fit.vutbr.cz
 *              Milan Hruban, xhruba08@stud.fit.vutbr.cz
 *              Martin Hons, xhonsm00@stud.fit.vutbr.cz
 *              David Hél, xhelda00@stud.fit.vutbr.cz
 */
#include "garbage_collector.h"

tGarbageListPtr listFirst = NULL;
tGarbageListPtr listLast = NULL;

void * plusMalloc(int length) {
    //Funkce alokuje paměť a zařadí nově alokovanou položku do listu

    tGarbageListPtr tmp = malloc(sizeof(struct GarbageList));

    if (tmp == NULL) {
        return NULL;
    }

    if (tmp != NULL) {
        tmp->data = NULL;
        tmp->nextPtr = NULL;
        tmp->length = NULL;
    }

    if (listFirst == NULL) {    //v pripade, ze je seznam prazdny, vkladame prvni prvek
        listFirst = tmp;
    }

    else {
        listFirst->nextPtr = tmp;
        listFirst = tmp;
    }

    if (listLast == NULL) {
        listLast = tmp;
    }

    else {
        listLast->nextPtr = tmp;
        listLast = tmp;
    }

    void *allocated = (void*)malloc(length);

    if (allocated != NULL) {
        tmp->data = allocated;
        return allocated;
    }

    else {
        return NULL;
    }



}

void * plusRealloc(void * destPtr, int length) {
    // Pomocí realloc() rozšíří danou paměť, pokud není alokovaná, zavolá plusMalloc() nad danou velikostí a navrátí pointer na alokovanou paměť
}

void plusAddReallocMem(void * tmpVar, int length, void * toNULL) {
    // Funkce slouží k alokaci další položky seznamu
    // po mallocu se položky struktury inicializují, data na tmpVar, nextPtr na NULL a lenght na parametr lenght
    // Provede e práce se seznamem (pokud nemá první prvek, pak je tohle první prvek, pokud nemá poslední a bla bla. viz 1. úkol IAL)

    nullData(toNULL);

    tGarbageListPtr tmp;
    tmp = malloc(sizeof(struct tGarbageListPtr));

    if (tmp != NULL) {
        tmp->nextPtr = NULL;
        tmp->data = tmpVar;
        tmp->length = length;
    }

    if (listFirst == NULL) {
        listFirst = tmp;
    }

    else {
        listFirst->nextPtr = tmp;
        listFirst = tmp;
    }

    if (listLast == NULL) {
        listLast = tmp;
    }

    else {
        listLast->nextPtr = tmp;
        listLast = tmp;
    }
}

void plusFree() {
    // Funkce uvolní data programu, která jsou na sebe navázaná v listu, nakonec uvolní i samotný list
}

void nullData(void * target){
    // Funkce projde celej seznam, najde daný target v seznamu a vynuluje mu položku data

}

// Zkuste se inspirovat zde http://matejmarecek.blogspot.cz/2012/01/ifj-projekt-formalni-jazyky-prekladace.html
// Případně https://github.com/nechutny/IFJ/blob/master/src/garbage.c