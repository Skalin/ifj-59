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


/**
 * IFJ/IAL - Precedenční analýza
 * Varianta:    b/2/I
 * Soubor:      expressions.c
 * Tým:         59
 * Autoři:      Jan Hrbotický, xhrbot01@stud.fit.vutbr.cz
 *              Dominik Skála, xskala11@stud.fit.vutbr.cz
 *              Milan Hruban, xhruba08@stud.fit.vutbr.cz
 *              Martin Hons, xhonsm00@stud.fit.vutbr.cz
 *              David Hél, xhelda00@stud.fit.vutbr.cz
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "garbage_collector.h"
#include "expressions.h"
#include "error_handler.h"
#include "stack.h"
#include "ial.h"
#include "instrstack.h"
#include "lexical_analyzer.h"

#define STR_ERROR   0
#define STR_SUCCESS 1
#define STR_ALLOCATION_SIZE 8  // Udává, kolik bude alokováno na začátku paměti. Pokud načítáme po jednom znaku, dojde k alokaci na násobky tohoto čísla


bool isIdent(tToken *token);
bool isConst(tToken *token);
char getPrecChar(tToken *stackToken, tToken *inToken);
tStackIt **chnToExp(tStack *stack, tStackIt *handle[]);
void reduceExp(BTSNode *targetId, tStackIt *handle[3], instrStack *iStack);
void expression(BTSNode *targetId, tExpType expType);
void completeInstr();
int strEqual(String str1, String str2);



/*
 *
 */
String readString();


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
void print(String string);


/*
 *
 */
String substr(String str, int i, int n);


/*
 *
 */
int addCharacter(String str, char c);


/*
 *
 */
void copyString(String str1, String str2);


/*
 *
 */
int compareString(String str1, String str2);


/*
 *
 */
int strLength(String str);


/*
 *
 */
void strClear(String str);


/*
 *
 */
void destroyString(String str);

#endif
