/**
 * IFJ/IAL - Stack pro instrukce
 * Varianta:    b/2/I
 * Soubor:      iStack.h
 * Tým:         59
 * Autoři:      Jan Hrbotický, xhrbot01@stud.fit.vutbr.cz
 *              Dominik Skála, xskala11@stud.fit.vutbr.cz
 *              Milan Hruban, xhruba08@stud.fit.vutbr.cz
 *              Martin Hons, xhonsm00@stud.fit.vutbr.cz
 *              David Hél, xhelda00@stud.fit.vutbr.cz
 */

#ifndef ISTACK_H
#define ISTACK_H
#include "garbage_collector.h"

//FUNKCE
instrStack *instrStackInit (instrStack *stc );
Instr *instrItemInit (Instr *stc);
int instrStackEmpty (const instrStack* stc);
int instrStackFull (const instrStack* stc);
void instrStackPush (instrStack *stc, Instr *data);
Instr *instrStackTop (instrStack *stc);
void instrStackPop (instrStack *stc);
int instrStackSize (instrStack *stc);
void instrStackDestroy (instrStack *stc);
void instrItemDestroy (Instr *data);




#endif
