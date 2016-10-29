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
#include "error_handler.c"
#include <stdlib.h>

tGarbageListPtr listFirst = NULL;
tGarbageListPtr listLast = NULL;

void * plusMalloc(int length) {
    //Funkce alokuje paměť a zařadí nově alokovanou položku do listu

    tGarbageListPtr tmp = malloc(sizeof(struct GarbageList));

    if (tmp == NULL) {
        throwException(99,0,0);
        return NULL;
    }

    if (tmp != NULL) {          //inicializace dat, další položky seznamu a velikosti seznamu
        tmp->data = NULL;
        tmp->nextPtr = NULL;
        tmp->length = 0;
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
        throwException(99,0,0);
        return NULL;
    }



}

void * plusRealloc(void * destPtr, int length) {

    void *tmp = NULL;

    if (destPtr != NULL) {                                      //paměť není alokována
        tmp = realloc(destPtr, length);                         //rozšíření paměti pomocí realloc

                if (tmp != destPtr) {
                    plusAddReallocMem(tmp, length, destPtr);    //alokace další položky v seznamu
                    return tmp;
                }

        
    }

    if (destPtr == NULL) {                                      //paměť není alokovánam, ukazatel je roven null
        destPtr = plusMalloc(length);                           //volání funkce plusMalloc nad danou velikostí
        return destPtr;                                         //vrací ukazatel na alokovanou paměť
    }
    
    return NULL;
}

void plusAddReallocMem(void * tmpVar, int length, void * target) {

    nullData(target);

    tGarbageListPtr tmp;
    tmp = NULL;
    tmp = malloc(sizeof(struct tGarbageListPtr *));   //alokace pameti

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

    tGarbageListPtr tmp;
    tmp = NULL;

    while (listFirst != NULL){      //procházíme list, kdokud není první položka nulová
        tmp = listFirst;
        listFirst = tmp->nextPtr;
        free(tmp->data);            //uvolění dat programu
        free(tmp);                  //uvolnění listu
    }
    
    listLast = NULL;                //vynulování posledního prvku

}

void nullData(void * target){

    tGarbageListPtr tmp;

    if (listFirst != NULL) {            //pokud není seznam prazdný, prochazíme seznam

        while (listFirst != NULL) {
            tmp = listFirst;
            if (tmp->data == target) {
                tmp->data = NULL;           //nastavení položky na null
                tmp = tmp->nextPtr;
            }
        }
    }

    listLast = NULL;
    
    if (listFirst == NULL) {    //seznam je prázdý, nic se nestane
        return;
    }
}

// Zkuste se inspirovat zde http://matejmarecek.blogspot.cz/2012/01/ifj-projekt-formalni-jazyky-prekladace.html
// Případně https://github.com/nechutny/IFJ/blob/master/src/garbage.c
