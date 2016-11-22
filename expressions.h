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
#include "lexical_analyzer.h"
#include "garbage_collector.h"
#include "stack.h"
#include <stdlib.h>



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

void print(char *string);

/*
 *
 */

SString substr(SString *str, int i, int n);

/*
 *
 */

int initString(SString *str);

/*
 *
 */

int addCharacter(SString *str, char c);

/*
 *
 */

SString copyString(SString *str1, SString *str2);

/*
 *
 */

int compareString(SString *str1, SString *str2);

/*
 *
 */

int strLength(SString *str);

/*
 *
 */
void strClear(SString *str);

/*
 *
 */
void destroyString(SString *str);

#endif
