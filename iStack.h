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
#include "typedef.h"
#include "garbage_collector.h"


typedef enum {
	// BUILT-IN FUNCTIONS
	insIfj16readInt,
	insIfj16readDouble,
	insIfj16readString,
	insIfj16lenght,
	insIfj16substr,
	insIfj16compare,
	insIfj16find,
	insIfj16sort,
	insIfj16print,
	//
	// MATH
	insPlus, // Sčítání
	insMinus, // Odečítání
	insMux, // Násobení
	insDiv, // Dělení
	//
	//COMPARE
	insEqual, // Je rovno
	insNotEqual, // Neni rovno
	insLess, // Je mensi
	insLessOrEqual, // Je mensi nebo rovno
	insGreater, // Je vetsi
	insGreaterOrEqual, // Je vetsi nebo rovno
	insAssignment,
    insFunctionCall
}InstrType;

typedef struct Instr {
	BTSNode *Id1; // Adresa prvního operandu
	BTSNode *Id2; // Adresa druhého operandu
	BTSNode *Id3; // Adresa, kam se uloží výsledek operace
	InstrType type;
}Instr;

typedef struct {
	Instr **dataInstr;
	int count;
	int alloc;
}instrStack;

//FUNKCE
instrStack* instrStackInit (instrStack* stc );
Instr *instrItemInit (Instr* stc);
int instrStackEmpty (const instrStack* stc);
int instrStackFull (const instrStack* stc);
void instrStackPush (instrStack* stc, Instr* data);
Instr *instrStackTop (instrStack* stc);
void instrStackPop (instrStack* stc);
int instrStackSize (instrStack* stc);
void instrStackDestroy (instrStack* stc);
void instrItemDestroy (Instr* data);




#endif
