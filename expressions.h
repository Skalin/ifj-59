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

void print(char *string);

/*
 *
 */

String substr(String *str, int i, int n);

/*
 *
 */

void initString(String *str);

/*
 *
 */

int addCharacter(String *str, char c);

/*
 *
 */

void copyString(String *str1, String *str2);

/*
 *
 */

int compareString(String *str1, String *str2);

/*
 *
 */

int strLength(String *str);

/*
 *
 */
void strClear(String *str);

/*
 *
 */
void destroyString(String *str);

#endif
