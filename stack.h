/**
 * IFJ/IAL - Stack
 * Varianta:    b/2/I
 * Soubor:      stack.h
 * Tým:         59
 * Autoři:      Jan Hrbotický, xhrbot01@stud.fit.vutbr.cz
 *              Dominik Skála, xskala11@stud.fit.vutbr.cz
 *              Milan Hruban, xhruba08@stud.fit.vutbr.cz
 *              Martin Hons, xhonsm00@stud.fit.vutbr.cz
 *              David Hél, xhelda00@stud.fit.vutbr.cz
 */

#ifndef IFJ_59_STACK_H
#define IFJ_59_STACK_H

//Struktura zásobníku
typedef struct {
    tStackIt ** data;
    int counter;
    int allocated;
} tStack;

//Struktura položky
typedef struct {
    tToken * dataIt;
    int typeIt;
} tStackIt;

/*
 * Inicializuje zásobník
 * @param zásobník
 * @return inicializovaný zásobník
 */
tStack * stackInit ( tStack *stack );
/*
 * Vrací 1/0 hodnotu jestli je zásobník prázdný
 * @param zásobník
 * @return true/false
 */
int stackEmpty (tStack *s );
/*
 * Vrací 1/0 hodnotu jestli je zásobník plný
 * @param zásobník
 * @return true/false
 */
int stackFull (tStack *s );
/*
 * Push dat na zásobník
 * @param zásobník
 * @param vkládaná data
 * @return
 */
void stackPush ( tStack *stack, void *data);
/*
 * Funkce navrátí ukazatel na vrchol zásobníku
 * @param zásobník
 * @return ukazatel na vrchol zasobniku
 */
void * stackTop (tStack *stack);
/*
 * Funkce popne data z vrcholu zásobníku
 * @param zásobník
 * @return
 */
void stackPop ( tStack *stack );
/*
 * Funkce navrátí hodnotu velikosti zásobníku
 * @param zásobník
 * @return velikost zásobníku
 */
int stackSize (tStack *stack);

#endif
