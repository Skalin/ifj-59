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
#include "instrstack.h"
//přesunuto do iStacku

//Prototypy


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
int compareInstruction(BTSNode *Id1, BTSNode *Id2, InstrType operation);

/*
 * Hlavni jadro interpretu, interpret samotny
 * @param interpretStack Stack instrukci
 */
void interpretMainCore(instrStack *interpretStack);

/*
 * Funkce zkontroluje semantiku prikazu
 * @param interpretStack Stack instrukci
 */
void semCheck(instrStack *interpretStack);
#endif //IFJ_59_INTERPRET_H
