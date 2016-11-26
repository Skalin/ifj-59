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
struct instrStack* instrStackInit (struct instrStack* stc );
Instr *instrItemInit (Instr* stc);
int instrStackEmpty (const struct instrStack* stc);
int instrStackFull (const struct instrStack* stc);
void instrStackPush (struct instrStack* stc, Instr* data);
Instr *instrStackTop (struct instrStack* stc);
void instrStackPop (struct instrStack* stc);
int instrStackSize (struct instrStack* stc);
void instrStackDestroy (struct instrStack* stc);
void instrItemDestroy (Instr* data);




#endif
