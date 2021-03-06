/**
 * IFJ/IAL - Precedenční analýza
 * Varianta:    b/2/I
 * Soubor:      expressions.h
 * Tým:         59
 * Autoři:      Jan Hrbotický, xhrbot01@stud.fit.vutbr.cz
 *              Dominik Skála, xskala11@stud.fit.vutbr.cz
 *              Milan Hruban, xhruba08@stud.fit.vutbr.cz
 *              Martin Hons, xhonsm00@stud.fit.vutbr.cz
 *              David Hél, xhelda00@stud.fit.vutbr.cz
 */


#ifndef EXPRESSIONS
#define EXPRESSIONS

#include "typedef.h"
#include "stack.h"
#include "garbage_collector.h"



#define STR_ERROR   0
#define STR_SUCCESS 1
#define STR_ALLOCATION_SIZE 8  // Udává, kolik bude alokováno na začátku paměti. Pokud načítáme po jednom znaku, dojde k alokaci na násobky tohoto čísla


bool isIdent(tToken *token);
bool isConst(tToken *token);
char getPrecChar(tToken *stackToken, tToken *inToken);
tStackIt **chnToExp(tStack *stack, tStackIt *handle[]);
void reduceExp(tStackIt *handle[3], instrStack *iStack, tStack *stack);
void expression(BTSNode *targetNode, int isArg);
void functionCall(BTSNode *targetNode, BTSNode *functionNode, char *functionName);
void completeInstr();
int strEqual(char str1[], char str2[]);
char* nodePrint(BTSNode *node);



/*
 *
 */
char *readString();


/*
 *
 */
int readInt();


/*
 *
 */
double readDouble();


/*
 *
 */
void print(char string[]);


/*
 *
 */
char *substr(char str[], int i, int n);


/*
 *
 */
int addCharacter(char str[], char c);


/*
 *
 */
void copyString(char *str1[], char *str2[]);

/*
 *
 */
void copyBuffer(char *str1[], char str2[]);

/*
 *
 */
int compareString(char str1[], char str2[]);


/*
 *
 */
int strLength(char str[]);


/*
 *
 */
void strClear(char str[]);


/*
 *
 */
void destroyString(char str[]);

#endif
