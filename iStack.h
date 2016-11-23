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

typedef enum {
    // MATH
    insPlus, // Sčítání
    insMinus, // Odečítání
    insMux, // Násobení
    insDiv, // Dělení
    insEqual, // Je rovno
    insNotEqual, // Neni rovno
    insLess, // Je mensi
    insLessOrEqual, // Je mensi nebo rovno
    insGreater, // Je vetsi
    insGreaterOrEqual, // Je vetsi nebo rovno
}InstrType;

typedef struct Instr {
     void *Id1; // Adresa prvního operandu
     void *Id2; // Adresa druhého operandu
     void *Id3; // Adresa, kam se uloží výsledek operace
     InstrType type;
}Instr; 

typedef struct {
    Instr *dataInstr;
    int count;
    int alloc;
}instrStack;


//FUNKCE


#endif
