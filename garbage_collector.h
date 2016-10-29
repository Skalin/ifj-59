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

#include "error_handler.c"

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
 * Funkce alokuje potřebnou paměť a zařadí nově alokovanou položku do listu.
 * @param length    místo potřebné k alokaci
 * @return          pointer na alokované místo
 */
void * plusMalloc(int length);

/*
 * Funkce realokuje potřebnou paměť. Pokud není paměť alokovaná, volá funkci plusMalloc nad danou velikosti a vrací
 * pointer na alokovanou paměť.
 * @param length    místo potřebné k alokace
 * @param *destPtr  ukazatel koncovou adresu
 */
void * plusRealloc(void * destPtr, int length);

/*
 * Funkce uvolní veškerou paměť. Dochází k uvolnění dat a nakonec si uvolní i samotný list.
 */
void plusFree();

/*
 * Funkce alokuje paměť pro další položky seznamu.
 * @param length    místo potřebné pro alokaci
 * @param *target   ukazatel na položku v seznamu
 * @param *tmpVar   ukazatel
 */
void plusAddReallocMem(void * tmpVar, int length, void * target);

/*
 * Funkce prochází seznam a danou položku nastaví na NULL.
 * @param *target    ukazatel na položku v seznamu
 */
void nullData(void * target);
