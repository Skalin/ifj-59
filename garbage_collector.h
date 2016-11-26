/**
 * IFJ/IAL - Lexikální analyzátor
 * Varianta:    b/2/I
 * Soubor:       garbage_collector.c
 * Tým:         59
 * Autoři:      Jan Hrbotický, xhrbot01@stud.fit.vutbr.cz
 *              Dominik Skála, xskala11@stud.fit.vutbr.cz
 *              Milan Hruban, xhruba08@stud.fit.vutbr.cz
 *              Martin Hons, xhonsm00@stud.fit.vutbr.cz
 *              David Hél, xhelda00@stud.fit.vutbr.cz
 */



#ifndef GARBAGE_COLLECTOR
#define GARBAGE_COLLECTOR

#include <stdio.h>
#include <stdbool.h>

int GlobalRow = 0;
int GlobalColumn = 0;

struct GarbageList
{
    void* dataPointer;
    struct GarbageList * nextPtr; // Pointer on a new item
} GarbageL;


/*
 * Struktura globálních proměnných
 */

struct tGlobal{

	// Listový seznam obsahující alokované položky
	struct GarbageList* wholeList;
	struct GarbageList* listLast;

	// Globální práce se vstupním souborem
	FILE *file; // FILE
	char *fileName; // globalni nazev souboru

	//promene pro parsing - kontrola zda program ma class Main a method run
	bool hasMain;
	bool hasRun;
	
	struct instrStack;
};

extern struct tGlobal global;


/*
 * Funkce alokuje potřebnou paměť a zařadí nově alokovanou položku do listu.
 * @param length    místo potřebné k alokaci
 * @return          pointer na alokované místo
 */
void * plusMalloc(unsigned int length);

/*
 * Funkce realokuje potřebnou paměť. Pokud není paměť alokovaná, volá funkci plusMalloc nad danou velikosti a vrací
 * pointer na alokovanou paměť.
 * @param *destPtr  ukazatel koncovou adresu
 * @param length    místo potřebné k alokace
 */
void * plusRealloc(void * destPtr, unsigned int length);

/*
 * Funkce inicializuje global proměnnou
 */
void globalInit();

/*
 * Funkce uvolní paměť jednoho prvku seznamu
 * @param memoryPtr ukazatel na paměť prvku, kterou chceme uvolnit
 */
void plusFree(void * memoryPtr);

/*
 * * Funkce uvolní veškerou paměť a uzavře načítaný soubor
 */
void finalFree();


#endif //IFJ_59_GARBAGE_COLLECTOR_H
