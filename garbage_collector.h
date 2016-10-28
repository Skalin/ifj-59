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

#ifndef IFJ_59_GARBAGE_COLLECTOR_H
#define IFJ_59_GARBAGE_COLLECTOR_H

#endif //IFJ_59_GARBAGE_COLLECTOR_H


typedef struct GarbageList
{
    void * data;
    int length;
    void * nextPtr;
} tGarbageList, *tGarbageListPtr;


/*
 * Funkce alokuje potřebnou paměť
 * @param length
 * @return pointer na alokované místo
 */
void * plusMalloc(int length);

/*
 * Funkce realokuje potřebnou paměť
 * @param length
 */
void * plusRealloc(void * destPtr, int length);

/*
 * Funkce uvolní veškerou paměť
 */
void plusFree();
