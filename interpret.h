/**
 * IFJ/IAL - Interpret
 * Varianta:    b/2/I
 * Soubor:       interpret.h
 * Tým:         59
 * Autoři:      Jan Hrbotický, xhrbot01@stud.fit.vutbr.cz
 *              Dominik Skála, xskala11@stud.fit.vutbr.cz
 *              Milan Hruban, xhruba08@stud.fit.vutbr.cz
 *              Martin Hons, xhonsm00@stud.fit.vutbr.cz
 *              David Hél, xhelda00@stud.fit.vutbr.cz
 */


#ifndef IFJ_59_INTERPRET_H
#define IFJ_59_INTERPRET_H

#include "typedef.h"
#include "ial.h"

 // POUZE PROVIZORNÍ! Struktury prosím přesuňte někam dopryč
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
}InstrType;

 typedef struct Instr {
     BTSNode *Id1; // Adresa prvního operandu
     BTSNode *Id2; // Adresa druhého operandu
     BTSNode *Id3; // Adresa, kam se uloží výsledek operace
     InstrType type;
 }Instr;

// KONEC ČÁSTI, KTERÁ SE MÁ ZKOPÍROVAT

//Prototypy

/*
 * Funkce najde v hashovací tabulce proměnnou s názvem id
 * @param Název proměnné, kterou chceme najít
 * @return Ukazatel uzel hledane promenne
 */
BTSNode *getVariable(char* id);

/*
 * Funkce provede aritmetickou operaci/ konkateraci retezcu
 * @param Id1 Ukazatel na adresu prvni instrukce
 * @param Id2 Ukazatel na adresu druhe instrukce
 * @param Id3 Ukazatel na adresu treti instrukce
 * @param operation Char, ktery znaci pozadovanou operaci
 * @return
 */
void mathInstruction(BTSNode *Id1, BTSNode *Id2, BTSNode *Id3, char operation);

/*
 * Funkce provede compare ope
 * @param Id1 Ukazatel na adresu prvni instrukce
 * @param Id2 Ukazatel na adresu druhe instrukce
 * @param Id3 Ukazatel na adresu treti instrukce
 * @param operation Enum typedef, ktery znaci pozadovanou operaci
 * @return
 */
void compareInstruction(BTSNode *Id1, BTSNode *Id2, BTSNode *Id3, InstrType operation);

#endif //IFJ_59_INTERPRET_H
