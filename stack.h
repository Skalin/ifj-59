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

// Typy elementů
typedef enum {
	EXPR = 1,
	NONTERM, 
	TERM
} tItemType;

//Struktura položky
typedef struct {
	tToken * dataIt;
	tItemType typeIt;
} tStackIt;


//Struktura zásobníku
typedef struct {
    tStackIt **data;
    int counter;
    int allocated;
} tStack;


//Struktura pomocného zásobníku
typedef struct {
    tStackIt ** data2;
    int counter2;
    int allocated2;
} tStackTmp;


/*
 * Inicializuje zásobník
 * @param zásobník
 * @return inicializovaný zásobník
 */
tStack * stackInit ( tStack *stack );

/*
 * Inicializuje pomocný zásobník
 * @param zásobník
 * @return inicializovaný zásobník
 */
tStackTmp * stackInitTmp (tStackTmp *stack2);

/*
 * Vrací 1/0 hodnotu jestli je zásobník prázdný
 * @param zásobník
 * @return true/false
 */
int stackEmpty (const tStack *s );

/*
 * Vrací 1/0 hodnotu jestli je zásobník plný
 * @param zásobník
 * @return true/false
 */
int stackFull (const tStack *s );

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
tStackIt * stackTop (tStack *stack);

/*
 * Funkce popne data z vrcholu zásobníku
 * @param zásobník
 * @return
 */
tStackIt * stackPop (tStack *stack );

/*
 * Funkce navrátí hodnotu velikosti zásobníku
 * @param zásobník
 * @return velikost zásobníku
 */
int stackSize (tStack *stack);

/*
 * Inicializujeme prvek na zásobníku
 * @return inicializovaný prvek zásobníku
 */
tStackIt *itemInit ();

/*
 * Uvolnění paměti na zásobníku
 * @param zásobník
 */
void stackDestroy (tStack *stc);

/*
 * Zničí prvky na zásobníku
 * @param prvek zásobníku
 */
void itemDestroy (tStackIt *data);

/*
 * Funkce sloužící k přemístění prvků z jednoho zásobníku na zásobník druhý
 * @param První zásobník 
 * @param Druhý zásobník
 */
void exprShift (tStack *stc1, tStack *stc2);

/*
 * Zjištění zda je první prvek terminálem
 * @param zásobník
 * @return nejvyšší terminál na zásobníku
 */
tokenType topTerm (tStack *stc);

	


#endif
