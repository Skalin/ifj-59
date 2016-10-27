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

    if (tmp != NULL) {          //inicializace dat, další položky seznamu a velikosti seznamu
        tmp->data = NULL;
        tmp->nextPtr = NULL;
        tmp->length = NULL;
    }

    if (listFirst == NULL) {    //v případě, ze je seznam prazdný, vkládame první prvek
        listFirst = tmp;
    }

    else {
        listFirst->nextPtr = tmp;
        listFirst = tmp;
    }

    if (listLast == NULL) {     //v případě, ze je seznam prazdný, vkládame poslední (první) prvek
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

void plusAddReallocMem(void * tmpVar, int length, void * target) {
    // Funkce slouží k alokaci další položky seznamu
    // po mallocu se položky struktury inicializují, data na tmpVar, nextPtr na NULL a lenght na parametr lenght
    // Provede e práce se seznamem (pokud nemá první prvek, pak je tohle první prvek, pokud nemá poslední a bla bla. viz 1. úkol IAL)

    nullData(target);

    tGarbageListPtr tmp;
    tmp = malloc(sizeof(struct tGarbageListPtr));   //alokace pameti

    if (tmp != NULL) {
        tmp->nextPtr = NULL;        //inicializace další položky na null
        tmp->data = tmpVar;         //inicializace dat na tmpVar
        tmp->length = length;       //inicializace velikosti seznamu na velikost
    }

    if (listFirst == NULL) {    //pokud je seznam prázdný, vkládame první prvek
        listFirst = tmp;
    }

    else {
        listFirst->nextPtr = tmp;
        listFirst = tmp;
    }

    if (listLast == NULL) {     //seznam je prazdný, vkládame první prvek
        listLast = tmp;
    }

    else {
        listLast->nextPtr = tmp;    //uložíme si předposlední prvek
        listLast = tmp;             //posuneme poslední prvek
    }
}

void plusFree() {
    // Funkce uvolní data programu, která jsou na sebe navázaná v listu, nakonec uvolní i samotný list
}

void nullData(void * target){
    // Funkce projde celej seznam, najde daný target v seznamu a vynuluje mu položku data
    tGarbageListPtr = tmp;

    if (listFirst != NULL) {            //pokud není seznam prazdný, prochazíme seznam

        while (listFirst != NULL) {
            tmp = listFirst;
            if (tmp->data == target) {
                tmp->data = NULL;           //nastavení položky na null
                tmp = tmp->nextPtr;
            }
        }
    }

    if (listFirst == NULL) {    //seznam je prázdý, nic se nestane
        return;
    }
}

// Zkuste se inspirovat zde http://matejmarecek.blogspot.cz/2012/01/ifj-projekt-formalni-jazyky-prekladace.html
// Případně https://github.com/nechutny/IFJ/blob/master/src/garbage.c