/**
 * IFJ/IAL - Interpret
 * Varianta:    b/2/I
 * Soubor:       interpret.c
 * Tým:         59
 * Autoři:      Jan Hrbotický, xhrbot01@stud.fit.vutbr.cz
 *              Dominik Skála, xskala11@stud.fit.vutbr.cz
 *              Milan Hruban, xhruba08@stud.fit.vutbr.cz
 *              Martin Hons, xhonsm00@stud.fit.vutbr.cz
 *              David Hél, xhelda00@stud.fit.vutbr.cz
 */

#include <stdlib.h>
#include <string.h>
#include "error_handler.h"
#include "interpret.h"
#include "expressions.h"
#include "instrstack.h"

void semCheck(instrStack *interpretStack) {
    // Vytvoreni pomocneho stacku
	instrStack tmpStack;
	instrStackInit(&tmpStack);
	instrStackCopy(interpretStack, &tmpStack);

	struct Instr *instr;
	instr = plusMalloc(sizeof(Instr));
	if (instr == NULL) {
		throwException(99, 0, 0);
	}


    while((instr = instrStackTop(&tmpStack)) != NULL) {
        switch (instr->type) {
            case insIfj16readInt:
                // Pokud je spatny pocet parametru
                if(instr->Id1 != NULL || instr->Id2 != NULL || instr->Id3 == NULL)
                    throwException(4,0,0);
                if(instr->Id3->inc == 1) {
                    // Pokud neni typ int, jedna se o chybu 4
                    if (instr->Id3->data.type != var_int)
                        throwException(4,0,0);
                // Pokud neni promenna kam se ulozi vysledke inicializovan
                } else
                    throwException(8,0,0);
                break;
            case insIfj16readDouble:
                // Pokud je spatny pocet parametru
                if(instr->Id1 != NULL || instr->Id2 != NULL || instr->Id3 == NULL)
                    throwException(4,0,0);
                if(instr->Id3->inc == 1) {
                    // Pokud neni typ double, jedna se o chybu 4
                    if (instr->Id3->data.type != var_double)
                        throwException(4,0,0);
                // Pokud neni promenna kam se ulozi vysledke inicializovan
                } else
                    throwException(8,0,0);
                break;
            case insIfj16readString:
                // Pokud je spatny pocet parametru
                if(instr->Id1 != NULL || instr->Id2 != NULL || instr->Id3 == NULL)
                    throwException(4,0,0);
                if(instr->Id3->inc == 1) {
                    // Pokud neni typ int, jedna se o chybu 4
                    if (instr->Id3->data.type != var_string)
                        throwException(4,0,0);
                // Pokud neni promenna kam se ulozi vysledke inicializovan
                } else
                    throwException(8,0,0);
                break;
            case insIfj16lenght:
                // Pokud je spatny pocet parametru
                if(instr->Id2 == NULL || instr->Id3 == NULL || instr->Id1 != NULL)
                    throwException(4,0,0);
                if(instr->Id2->inc == 1 && instr->Id1->inc == 1) {
                    // Pokud neni narvatovy typ int a parametr 1 neni string, jedna se o chybu 4
                    if (instr->Id3->data.type != var_int && instr->Id2->data.type != var_string)
                        throwException(4,0,0);
                    // Pokud neni promenna kam se ulozi vysledke inicializovan
                } else
                    throwException(8,0,0);
                break;
            case insIfj16substr:
                // Pokud je spatny pocet parametru
                if(instr->Id2 == NULL || instr->Id3 == NULL || instr->Id1 == NULL || instr->Id2->variables == NULL)
                    throwException(4,0,0);
                // Pokud je nektery parametr neinicializovany
                if(instr->Id2->inc == 0 || instr->Id3->inc == 0 || instr->Id1->inc == 0 || instr->Id2->variables->inc == 0)
                    throwException(4,0,0);
                // Pokud je spatny typ parametru
                if(instr->Id2->data.type !=  var_int|| instr->Id2->variables->data.type !=  var_string || instr->Id1->data.type !=  var_int || instr->Id3->data.type !=  var_string)
                    throwException(4,0,0);
                break;
            case insIfj16compare:
                // Pokud je spatny pocet parametru
                if(instr->Id3 == NULL || instr->Id2 == NULL || instr->Id1 == NULL)
                    throwException(4,0,0);
                if(instr->Id3->inc == 1 && instr->Id1->inc == 1 && instr->Id2->inc == 1) {
                    // Pokud neni narvatovy typ int a parametr 1 neni string a parametr 2 neni take sring, jedna se o chybu 4
                    if (instr->Id3->data.type != var_int && instr->Id1->data.type != var_string && instr->Id2->data.type != var_string)
                        throwException(4,0,0);
                    // Pokud neni promenna kam se ulozi vysledke inicializovan
                } else
                    throwException(8,0,0);
                break;
            case insIfj16find:
                // Pokud je spatny pocet parametru
                if(instr->Id3 == NULL || instr->Id2 == NULL || instr->Id1 == NULL)
                    throwException(4,0,0);
                if(instr->Id3->inc == 1 && instr->Id1->inc == 1 && instr->Id2->inc == 1) {
                    // Pokud neni narvatovy typ int a parametr 1 neni string a parametr 2 neni take sring, jedna se o chybu 4
                    if (instr->Id3->data.type != var_int && instr->Id1->data.type != var_string && instr->Id2->data.type != var_string)
                        throwException(4,0,0);
                    // Pokud neni promenna kam se ulozi vysledke inicializovan
                } else
                    throwException(8,0,0);
                break;
            case insIfj16sort:
                // Pokud je spatny pocet parametru
                if(instr->Id2 == NULL || instr->Id3 == NULL || instr->Id1 != NULL)
                    throwException(4,0,0);
                if(instr->Id3->inc == 1 && instr->Id1->inc == 1) {
                    // Pokud neni narvatovy typ string a parametr 1 neni string, jedna se o chybu 4
                    if (instr->Id3->data.type != var_string && instr->Id2->data.type != var_string)
                        throwException(4,0,0);
                    // Pokud neni promenna kam se ulozi vysledke inicializovan
                } else
                    throwException(8,0,0);
                break;
            case insIfj16print:
                // Pokud je spatny pocet parametru
                if(instr->Id3 != NULL || instr->Id2 == NULL || instr->Id1 != NULL)
                    throwException(4,0,0);
                if(instr->Id1->inc == 1) {
                    // Pokud neni jediny parametr string, jedna se o chybu 4
                    if (instr->Id2->data.type != var_string)
                        throwException(4,0,0);
                    // Pokud neni promenna kam se ulozi vysledke inicializovan
                } else
                    throwException(8,0,0);
                break;
            case insPlus:
                // Pokud je spatny pocet parametru
                if(instr->Id3 == NULL || instr->Id2 == NULL || instr->Id1 == NULL)
                    throwException(3,0,0);
                if(instr->Id3->inc == 1 && instr->Id1->inc == 1 && instr->Id2->inc == 1) {
                    // Pokud je konecny operand int, musi se jedna o int = int + int
                    if(instr->Id3->data.type == var_int) {
                        if(instr->Id1->data.type != var_int && instr->Id2->data.type != var_int)
                            throwException(4,0,0);
                    // Pokud chceme do double ukladat soucet neceho a stringu, jedna se o chybu
                    } else if (instr->Id3->data.type == var_double) {
                        if(instr->Id1->data.type == var_string || instr->Id2->data.type == var_string)
                            throwException(4,0,0);
                    }
                // Pokud nejsou vsechny promenne inicializovane
                } else
                    throwException(8,0,0);
                break;
            case insMinus:
                // Pokud je spatny pocet parametru
                if(instr->Id3 == NULL || instr->Id2 == NULL || instr->Id1 == NULL)
                    throwException(3,0,0);
                if(instr->Id3->inc == 1 && instr->Id1->inc == 1 && instr->Id2->inc == 1) {
                    // Nelze odecitat stringy a ani do stringu ukladat
                    if(instr->Id1->data.type == var_string || instr->Id2->data.type == var_string || instr->Id3->data.type == var_string)
                        throwException(4,0,0);
                    else {
                        // Pokud je konecny vysledek ulozek do int, musi se jedna o int = int - int
                        if(instr->Id3->data.type == var_int) {
                            if(instr->Id1->data.type != var_int && instr->Id2->data.type != var_int)
                                throwException(4,0,0);
                        }
                    }
                    // Pokud nejsou vsechny promenne inicializovane
                } else
                    throwException(8,0,0);
                break;
            case insMux:
                // Pokud je spatny pocet parametru
                if(instr->Id3 == NULL || instr->Id2 == NULL || instr->Id1 == NULL)
                    throwException(3,0,0);
                if(instr->Id3->inc == 1 && instr->Id1->inc == 1 && instr->Id2->inc == 1) {
                    // Nelze operovat se stringy
                    if(instr->Id1->data.type == var_string || instr->Id2->data.type == var_string || instr->Id3->data.type == var_string)
                        throwException(4,0,0);
                    // Pokud ma byt vysledek int, musi se jednat o int = int * int
                    if(instr->Id3->data.type == var_int) {
                        if(instr->Id1->data.type != var_int && instr->Id2->data.type != var_int)
                            throwException(4,0,0);
                    }
                    // Pokud nejsou vsechny promenne inicializovane
                } else
                    throwException(8,0,0);
                break;
            case insDiv:
                // Pokud je spatny pocet parametru
                if(instr->Id3 == NULL || instr->Id2 == NULL || instr->Id1 == NULL)
                    throwException(3,0,0);
                if(instr->Id3->inc == 1 && instr->Id1->inc == 1 && instr->Id2->inc == 1) {
                    // Nelze operovat se stringy
                    if(instr->Id1->data.type == var_string || instr->Id2->data.type == var_string || instr->Id3->data.type == var_string)
                        throwException(4,0,0);
                    // Pokud ma byt vysledek int, musi se jednat o int = int * int
                    if(instr->Id3->data.type == var_int) {
                        if(instr->Id1->data.type != var_int && instr->Id2->data.type != var_int)
                            throwException(4,0,0);
                    }
                    // Pokud se jedna o int, proverim jeho hodnotu jestli neni nula pri deleni
                    if(instr->Id2->data.type == var_int) {
                        if (instr->Id2->data.value.intValue == 0)
                            throwException(9,0,0);
                        // Pokud se jedna o double, proverim jeho hodnotu jestli neni nula pri deleni
                    } else {
                        if (instr->Id2->data.value.doubleValue == 0)
                            throwException(9,0,0);
                    }
                    // Pokud nejsou vsechny promenne inicializovane
                } else
                    throwException(8,0,0);
                break;
            case insEqual:
                // Pokud je spatny pocet parametru
                if(instr->Id2 == NULL || instr->Id1 == NULL)
                    throwException(3,0,0);
                if(instr->Id1->inc == 1 && instr->Id2->inc == 1) {
                    // Lze porovnavat pouze int a double hodnoty viz zadani
                    if(instr->Id1->data.type == var_string || instr->Id2->data.type == var_string) {
                        throwException(4,0,0);
                    }
                } else
                    throwException(8,0,0);
                break;
            case insNotEqual:
                // Pokud je spatny pocet parametru
                if(instr->Id2 == NULL || instr->Id1 == NULL)
                    throwException(3,0,0);
                if(instr->Id1->inc == 1 && instr->Id2->inc == 1) {
                    // Lze porovnavat pouze int a double hodnoty viz zadani
                    if(instr->Id1->data.type == var_string || instr->Id2->data.type == var_string) {
                        throwException(4,0,0);
                    }
                } else
                    throwException(8,0,0);
                break;
            case insLess:
                // Pokud je spatny pocet parametru
                if(instr->Id2 == NULL || instr->Id1 == NULL)
                    throwException(3,0,0);
                if(instr->Id1->inc == 1 && instr->Id2->inc == 1) {
                    // Lze porovnavat pouze int a double hodnoty viz zadani
                    if(instr->Id1->data.type == var_string || instr->Id2->data.type == var_string) {
                        throwException(4,0,0);
                    }
                } else
                    throwException(8,0,0);
                break;
            case insLessOrEqual:
                // Pokud je spatny pocet parametru
                if(instr->Id2 == NULL || instr->Id1 == NULL)
                    throwException(3,0,0);
                if(instr->Id1->inc == 1 && instr->Id2->inc == 1) {
                    // Lze porovnavat pouze int a double hodnoty viz zadani
                    if(instr->Id1->data.type == var_string || instr->Id2->data.type == var_string) {
                        throwException(4,0,0);
                    }
                } else
                    throwException(8,0,0);
                break;
            case insGreater:
                // Pokud je spatny pocet parametru
                if(instr->Id2 == NULL || instr->Id1 == NULL)
                    throwException(3,0,0);
                if(instr->Id1->inc == 1 && instr->Id2->inc == 1) {
                    // Lze porovnavat pouze int a double hodnoty viz zadani
                    if(instr->Id1->data.type == var_string || instr->Id2->data.type == var_string) {
                        throwException(4,0,0);
                    }
                } else
                    throwException(8,0,0);
                break;
            case insGreaterOrEqual:
                // Pokud je spatny pocet parametru
                if(instr->Id2 == NULL || instr->Id1 == NULL)
                    throwException(3,0,0);
                if(instr->Id1->inc == 1 && instr->Id2->inc == 1) {
                    // Lze porovnavat pouze int a double hodnoty viz zadani
                    if(instr->Id1->data.type == var_string || instr->Id2->data.type == var_string) {
                        throwException(4,0,0);
                    }
                } else
                    throwException(8,0,0);
                break;
            case insAssignment:
                // Pokud je spatny pocet parametru
                if(instr->Id2 != NULL || instr->Id1 == NULL || instr->Id3 == NULL)
                    throwException(3,0,0);
                if(instr->Id1->inc == 1 && instr->Id3->inc == 1) {
                    // Pokud prirazujeme spatne typy
                    if(instr->Id1->data.type != instr->Id2->data.type) {
                        throwException(4,0,0);
                    }
                    if(instr->Id1->data.type == var_int)
                        instr->Id3->data.value.intValue = instr->Id1->data.value.intValue;
                    else if (instr->Id1->data.type == var_double)
                        instr->Id3->data.value.doubleValue = instr->Id1->data.value.doubleValue;
                    else
                        instr->Id3->data.value.stringValue = instr->Id1->data.value.stringValue;
                } else
                    throwException(8,0,0);
                break;
            default:
                break;
        }
    }

}


void mathInstruction(BTSNode *Id1, BTSNode *Id2, BTSNode *Id3, char operation) {
    // Pokud jsou oba operandy inicializované
    if(Id1->inc != 0 || Id2->inc != 0) {
        // Pokud se jedna o scitani/ konkateraci
        if(operation == '+') {
            // Pokud se jedna o 2 int, je vysledek int
            if(Id1->data.type == var_int && Id2->data.type == var_int) {
                Id3->data.type = var_int;
                Id3->data.value.intValue = Id1->data.value.intValue + Id3->data.value.intValue;
                Id3->inc = 1;
            // Pokud je alespon jeden operand double a druhy neni string, pak se provede secteni double a int
            } else if ((Id1->data.type == var_double || Id2->data.type == var_double) && (Id1->data.type != var_string || Id2->data.type != var_string)) {
                Id3->data.type = var_double;
                Id3->inc = 1;

                // Pokud jde o double = double + int
                if (Id1->data.type == var_double && Id2->data.type == var_int) {
                    Id3->data.value.doubleValue = Id1->data.value.doubleValue + Id2->data.value.intValue;
                // Pokud jde o double = int + double
                } else if ((Id1->data.type == var_int && Id2->data.type == var_double)){
                    Id3->data.value.doubleValue = Id1->data.value.intValue + Id2->data.value.doubleValue;
                // Pokud jde o double = double + double
                } else {
                    Id3->data.value.doubleValue = Id1->data.value.doubleValue + Id2->data.value.doubleValue;
                }
            // Pokud se jedna o konkateraci dvou stringu
            } else if (Id1->data.type == var_string && Id2->data.type == var_string) {
                Id3->data.type = var_string;
                strcpy(Id3->data.value.stringValue, Id1->data.value.stringValue);
                strncat(Id3->data.value.stringValue, Id2->data.value.stringValue, 512);
            // Pokud je prvni operand string
            } else if (Id1->data.type == var_string) {
                // Do Id3 nacteme prvni string
                Id3->data.type = var_string;
                strcpy(Id3->data.value.stringValue, Id1->data.value.stringValue);

                // Pokud konkaterujeme String + int
                if(Id2->data.type == var_int) {
                    char buffer[512];
                    sprintf(buffer, "%d", Id2->data.value.intValue);
                    strncat(Id3->data.value.stringValue, buffer, 512);
                // Pokud konkaterujeme String + double
                } else {
                    char buffer[512];
                    sprintf(buffer, "%g", Id2->data.value.doubleValue);
                    strncat(Id3->data.value.stringValue, buffer, 512);
                }
                Id3->inc = 1;
            // Pokud je druhy operand string
            } else if (Id2->data.type == var_string) {
                Id3->data.type = var_string;

                // Pokud konkaterujeme Int + String
                if(Id2->data.type == var_int) {
                    char buffer[512];
                    sprintf(buffer, "%d", Id1->data.value.intValue);
                    strncpy(Id3->data.value.stringValue, buffer, 512);
                // Pokud konkaterujeme Double + String
                } else {
                    char buffer[512];
                    sprintf(buffer, "%g", Id1->data.value.doubleValue);
                    strncpy(Id3->data.value.stringValue, buffer, 512);
                }
                // Nakonec pripojime string
                strncat(Id3->data.value.stringValue, Id2->data.value.stringValue, 512);
                Id3->inc = 1;
            // Pokud se vyskytne cokoli jineho, jedna se o chyba typove komp.
            } else
                throwException(4,0,0);
        // Pokud se jedna o odecitani
        } else if (operation == '-') {
            // Pokud se jedna o odecteni dvou int, vysledek bude int
            if (Id1->data.type == var_int && Id2->data.type == var_int) {
                Id3->data.type = var_int;
                Id3->inc = 1;
                Id3->data.value.intValue = Id1->data.value.intValue - Id2->data.value.intValue;
            // Pokud se jedna o povolenoe datove typy double - int nebo int - double
            } else if ((Id1->data.type == var_double || Id2->data.type == var_int) && (Id2->data.type == var_double || Id1->data.type == var_int)) {
                Id3->data.type = var_double;
                Id3->inc = 1;

                // Pokud jde o double = double - int
                if (Id1->data.type == var_double && Id2->data.type == var_int) {
                    Id3->data.value.doubleValue = Id1->data.value.doubleValue - Id2->data.value.intValue;
                    // Pokud jde o double = int - double
                } else if ((Id1->data.type == var_int && Id2->data.type == var_double)){
                    Id3->data.value.doubleValue = Id1->data.value.intValue - Id2->data.value.doubleValue;
                    // Pokud jde o double = double - double
                } else {
                    Id3->data.value.doubleValue = Id1->data.value.doubleValue - Id2->data.value.doubleValue;
                }
            // Pokud se nekdo pokusi odecist hodnoty ktere nejsou podporovany
            } else
                throwException(4,0,0);
        // Pokud se jedna o nasobeni
        } else if (operation == '*') {
            // Pokud se jedna o odecteni dvou int, vysledek bude int
            if (Id1->data.type == var_int && Id2->data.type == var_int) {
                Id3->data.type = var_int;
                Id3->inc = 1;
                Id3->data.value.intValue = Id1->data.value.intValue * Id2->data.value.intValue;
                // Pokud se jedna o povolenoe datove typy double - int nebo int - double
            } else if ((Id1->data.type == var_double || Id2->data.type == var_int) && (Id2->data.type == var_double || Id1->data.type == var_int)) {
                Id3->data.type = var_double;
                Id3->inc = 1;

                // Pokud jde o double = double * int
                if (Id1->data.type == var_double && Id2->data.type == var_int) {
                    Id3->data.value.doubleValue = Id1->data.value.doubleValue * Id2->data.value.intValue;
                    // Pokud jde o double = int * double
                } else if ((Id1->data.type == var_int && Id2->data.type == var_double)){
                    Id3->data.value.doubleValue = Id1->data.value.intValue * Id2->data.value.doubleValue;
                    // Pokud jde o double = double * double
                } else {
                    Id3->data.value.doubleValue = Id1->data.value.doubleValue * Id2->data.value.doubleValue;
                }
            // Pokud se nekdo pokusi nasobit hodnoty ktere nejsou podporovany
            } else
                throwException(4,0,0);
        // Pokud se jedna o deleni
        } else if (operation == '/') {
            if(Id2->data.value.intValue != 0 || Id2->data.value.doubleValue != 0) {
                // Pokud se jedna o deleni dvou int, vysledek bude int
                if (Id1->data.type == var_int && Id2->data.type == var_int) {
                    Id3->data.type = var_int;
                    Id3->inc = 1;
                    Id3->data.value.intValue = Id1->data.value.intValue / Id2->data.value.intValue;
                    // Pokud se jedna o povolenoe datove typy double - int nebo int - double
                } else if ((Id1->data.type == var_double || Id2->data.type == var_int) && (Id2->data.type == var_double || Id1->data.type == var_int)) {
                    Id3->data.type = var_double;
                    Id3->inc = 1;

                    // Pokud jde o double = double / int
                    if (Id1->data.type == var_double && Id2->data.type == var_int) {
                        Id3->data.value.doubleValue = Id1->data.value.doubleValue / Id2->data.value.intValue;
                        // Pokud jde o double = int / double
                    } else if ((Id1->data.type == var_int && Id2->data.type == var_double)){
                        Id3->data.value.doubleValue = Id1->data.value.intValue / Id2->data.value.doubleValue;
                        // Pokud jde o double = double / double
                    } else {
                        Id3->data.value.doubleValue = Id1->data.value.doubleValue / Id2->data.value.doubleValue;
                    }
                // Pokud se nekdo pokusi nasobit hodnoty ktere nejsou podporovany
                } else
                    throwException(4,0,0);
            // Pokud se nekdo pokousi delit nulou
            } else
                throwException(9,0,0);
        }
    // Pokud není některý z operandů inicializovaný, program skončí s chybou 8
    } else
        throwException(8,0,0);
}


int compareInstruction(BTSNode *Id1, BTSNode *Id2, InstrType operation) {
    if(Id1->inc != 0 || Id2->inc != 0) {
        if(operation == insEqual) {
            // Pokud se jedna o porovnani double double nebo int int
            if ((Id1->data.type == var_double && Id2->data.type == var_double) || (Id1->data.type == var_int && Id2->data.type == var_int)) {
                if (Id1->data.type == var_double) {
                    return (Id1->data.value.doubleValue == Id2->data.value.doubleValue ? 1 : 0);
                } else {
                    return (Id1->data.value.intValue == Id2->data.value.intValue ? 1 : 0);
                }
            // Pokud se jedna o porovnani double int nebo int double
            } else if ((Id1->data.type == var_double && Id2->data.type == var_int) || (Id1->data.type == var_int && Id2->data.type == var_double)) {
                if (Id1->data.type == var_double) {
                    return (Id1->data.value.doubleValue == (double)Id2->data.value.intValue ? 1 : 0);
                } else {
                    return ((double)Id1->data.value.intValue == Id2->data.value.doubleValue ? 1 : 0);
                }
            // Pokud je na vstupu jiny uzel nez povoleny, je to semanticka chyba
            } else
                throwException(4,0,0);
        // a != b
        } else if(operation == insNotEqual) {
            // Pokud se jedna o porovnani double double nebo int int
            if ((Id1->data.type == var_double && Id2->data.type == var_double) || (Id1->data.type == var_int && Id2->data.type == var_int)) {
                if (Id1->data.type == var_double) {
                    return (Id1->data.value.doubleValue != Id2->data.value.doubleValue ? 1 : 0);
                } else {
                    return(Id1->data.value.intValue != Id2->data.value.intValue ? 1 : 0);
                }
                // Pokud se jedna o porovnani double int nebo int double
            } else if ((Id1->data.type == var_double && Id2->data.type == var_int) || (Id1->data.type == var_int && Id2->data.type == var_double)) {
                if (Id1->data.type == var_double) {
                    return (Id1->data.value.doubleValue != (double)Id2->data.value.intValue ? 1 : 0);
                } else {
                    return ((double)Id1->data.value.intValue != Id2->data.value.doubleValue ? 1 : 0);
                }
                // Pokud je na vstupu jiny uzel nez povoleny, je to semanticka chyba
            } else
                throwException(4,0,0);
        // a < b
        } else if(operation == insLess) {
            // Pokud se jedna o porovnani double double nebo int int
            if ((Id1->data.type == var_double && Id2->data.type == var_double) || (Id1->data.type == var_int && Id2->data.type == var_int)) {
                if (Id1->data.type == var_double) {
                    return (Id1->data.value.doubleValue < Id2->data.value.doubleValue ? 1 : 0);
                } else {
                    return (Id1->data.value.intValue < Id2->data.value.intValue ? 1 : 0);
                }
                // Pokud se jedna o porovnani double int nebo int double
            } else if ((Id1->data.type == var_double && Id2->data.type == var_int) || (Id1->data.type == var_int && Id2->data.type == var_double)) {
                if (Id1->data.type == var_double) {
                    return (Id1->data.value.doubleValue < (double)Id2->data.value.intValue ? 1 : 0);
                } else {
                    return ((double)Id1->data.value.intValue < Id2->data.value.doubleValue ? 1 : 0);
                }
                // Pokud je na vstupu jiny uzel nez povoleny, je to semanticka chyba
            } else
                throwException(4,0,0);
        // a <= b
        } else if(operation == insLessOrEqual) {
            // Pokud se jedna o porovnani double double nebo int int
            if ((Id1->data.type == var_double && Id2->data.type == var_double) || (Id1->data.type == var_int && Id2->data.type == var_int)) {
                if (Id1->data.type == var_double) {
                    return (Id1->data.value.doubleValue <= Id2->data.value.doubleValue ? 1 : 0);
                } else {
                    return (Id1->data.value.intValue <= Id2->data.value.intValue ? 1 : 0);
                }
                // Pokud se jedna o porovnani double int nebo int double
            } else if ((Id1->data.type == var_double && Id2->data.type == var_int) || (Id1->data.type == var_int && Id2->data.type == var_double)) {
                if (Id1->data.type == var_double) {
                    return (Id1->data.value.doubleValue <= (double)Id2->data.value.intValue ? 1 : 0);
                } else {
                    return ((double)Id1->data.value.intValue <= Id2->data.value.doubleValue ? 1 : 0);
                }
                // Pokud je na vstupu jiny uzel nez povoleny, je to semanticka chyba
            } else
                throwException(4,0,0);
        // a > b
        } else if(operation == insGreater) {
            // Pokud se jedna o porovnani double double nebo int int
            if ((Id1->data.type == var_double && Id2->data.type == var_double) || (Id1->data.type == var_int && Id2->data.type == var_int)) {
                if (Id1->data.type == var_double) {
                    return (Id1->data.value.doubleValue > Id2->data.value.doubleValue ? 1 : 0);
                } else {
                    return (Id1->data.value.intValue > Id2->data.value.intValue ? 1 : 0);
                }
                // Pokud se jedna o porovnani double int nebo int double
            } else if ((Id1->data.type == var_double && Id2->data.type == var_int) || (Id1->data.type == var_int && Id2->data.type == var_double)) {
                if (Id1->data.type == var_double) {
                    return (Id1->data.value.doubleValue > (double)Id2->data.value.intValue ? 1 : 0);
                } else {
                    return ((double)Id1->data.value.intValue > Id2->data.value.doubleValue ? 1 : 0);
                }
                // Pokud je na vstupu jiny uzel nez povoleny, je to semanticka chyba
            } else
                throwException(4,0,0);
        // a >=
        } else if(operation == insGreaterOrEqual) {
            // Pokud se jedna o porovnani double double nebo int int
            if ((Id1->data.type == var_double && Id2->data.type == var_double) || (Id1->data.type == var_int && Id2->data.type == var_int)) {
                if (Id1->data.type == var_double) {
                    return (Id1->data.value.doubleValue >= Id2->data.value.doubleValue ? 1 : 0);
                } else {
                    return (Id1->data.value.intValue >= Id2->data.value.intValue ? 1 : 0);
                }
                // Pokud se jedna o porovnani double int nebo int double
            } else if ((Id1->data.type == var_double && Id2->data.type == var_int) || (Id1->data.type == var_int && Id2->data.type == var_double)) {
                if (Id1->data.type == var_double) {
                    return (Id1->data.value.doubleValue >= (double)Id2->data.value.intValue ? 1 : 0);
                } else {
                    return ((double)Id1->data.value.intValue >= Id2->data.value.doubleValue ? 1 : 0);
                }
                // Pokud je na vstupu jiny uzel nez povoleny, je to semanticka chyba
            } else
                throwException(4,0,0);
        // Pokud se jedna
        } else
            throwException(4,0,0);
    // Pokud není některý z operandů inicializovaný, program skončí s chybou 8
    } else
        throwException(8,0,0);
    return 0;
}

void interpretMainCore(instrStack *interpretStack) {
    // Pomocne promenne
    int cond=0;
    int whileCondPos=0;
    // Pointer na instrukci
    struct Instr *instruction;
    struct Instr *instructionWhile;

    while((instruction = instrStackTop(interpretStack)) != NULL) {
        // Switch pro jednotlive typy instrukci
        switch (instruction->type) {
            // ASSIGNMENT
            case insAssignment:
                if(instruction->Id1->inc == 1 && instruction->Id3->inc == 1) {
                    // Pokud prirazujeme spatne typy
                    if(instruction->Id1->data.type != instruction->Id2->data.type) {
                        throwException(4,0,0);
                    }
                    if(instruction->Id1->data.type == var_int)
                        instruction->Id3->data.value.intValue = instruction->Id1->data.value.intValue;
                    else if (instruction->Id1->data.type == var_double)
                        instruction->Id3->data.value.doubleValue = instruction->Id1->data.value.doubleValue;
                    else
                        instruction->Id3->data.value.stringValue = instruction->Id1->data.value.stringValue;
                } else
                    throwException(8,0,0);
                break;
            // BUILT-IN FUNCTIONS
            // Pokud se jedna o volani funkce int readInt();
            case  insIfj16readInt:
                if(instruction->Id3->inc == 1) {
                    if (instruction->Id3->data.type == var_int) {
                        instruction->Id3->data.value.intValue = readInt();
                    // Pokud neni promenna prirazeni int, pak se jedna o chybu
                    } else {
                        throwException(4,0,0);
                    }
                // Pokud pracujeme s neinicializovanou promennou
                } else {
                    throwException(8, 0, 0);
                }
                break;
            case insIfj16readString:
                if(instruction->Id3->inc == 1) {
                    if(instruction->Id3->data.type == var_string) {
                        instruction->Id3->data.value.stringValue = readString();
                    } else {
                        throwException(4,0,0);
                    }
                } else {
                    throwException(8,0,0);
                }
                break;
            // Pokud se jedna o volani funkce int readDouble();
            case insIfj16readDouble:
                if(instruction->Id3->inc == 1) {
                    if(instruction->Id3->data.type == var_double) {
                        instruction->Id3->data.value.doubleValue = readDouble();
                    } else {
                        throwException(4,0,0);
                    }
                } else {
                    throwException(8,0,0);
                }
                break;
            // Pokud se jedna o volani fce void print(char *string);
            case insIfj16print:
                if(instruction->Id1->inc == 1) {
                    if(instruction->Id3->data.type == var_string) {
                        print(instruction->Id2->data.value.stringValue);
                    } else {
                        throwException(4,0,0);
                    }
                } else {
                    throwException(8,0,0);
                }
                break;
            case insIfj16lenght:
                if(instruction->Id2->inc == 1 && instruction->Id3->inc == 1) {
                    if(instruction->Id3->data.type == var_int && instruction->Id2->data.type == var_string) {
                        instruction->Id3->data.value.intValue = strLength(instruction->Id2->data.value.stringValue);
                    } else {
                        throwException(4,0,0);
                    }
                } else {
                    throwException(8,0,0);
                }
                break;
            case insIfj16substr:
                instruction->Id3->data.value.stringValue = substr(instruction->Id2->variables->data.value.stringValue,instruction->Id2->data.value.intValue, instruction->Id1->data.value.intValue);
                break;
            case insIfj16compare:
                if(instruction->Id1->inc == 1 && instruction->Id3->inc == 1 && instruction->Id2->inc == 1) {
                    if(instruction->Id3->data.type == var_int && instruction->Id2->data.type == var_string && instruction->Id1->data.type == var_string) {
                        instruction->Id3->data.value.intValue = strcmp(instruction->Id2->data.value.stringValue,instruction->Id1->data.value.stringValue);
                    } else {
                        throwException(4,0,0);
                    }
                } else {
                    throwException(8,0,0);
                }
                break;
            case insIfj16find:
                if(instruction->Id1->inc == 1 && instruction->Id3->inc == 1 && instruction->Id2->inc == 1) {
                    if(instruction->Id3->data.type == var_int && instruction->Id2->data.type == var_string && instruction->Id1->data.type == var_string) {
                        instruction->Id3->data.value.intValue = find(instruction->Id2->data.value.stringValue, instruction->Id1->data.value.stringValue);
                    } else {
                        throwException(4,0,0);
                    }
                } else {
                    throwException(8,0,0);
                }
                break;
            case insIfj16sort:
                if(instruction->Id1->inc == 1 && instruction->Id3->inc == 1) {
                    if(instruction->Id3->data.type == var_string && instruction->Id1->data.type == var_string) {
                        instruction->Id3->data.value.stringValue = sort(instruction->Id2->data.value.stringValue);
                    } else {
                        throwException(4,0,0);
                    }
                } else {
                    throwException(8,0,0);
                }
                break;
            // END BUILT-IN FUNCTIONS
            // MATH
            case insPlusTmp:
                mathInstruction(instruction->Id1,instruction->Id2,instruction->Id3,'+');
                break;
            case insPlus:
                mathInstruction(instruction->Id1,instruction->Id2,instruction->Id3,'+');
                break;
            case insMinusTmp:
                mathInstruction(instruction->Id1,instruction->Id2,instruction->Id3,'-');
                break;
            case insMinus:
                mathInstruction(instruction->Id1,instruction->Id2,instruction->Id3,'-');
                break;
            case insMuxTmp:
                mathInstruction(instruction->Id1,instruction->Id2,instruction->Id3,'*');
                break;
            case insMux:
                mathInstruction(instruction->Id1,instruction->Id2,instruction->Id3,'*');
                break;
            case insDivTmp:
                mathInstruction(instruction->Id1,instruction->Id2,instruction->Id3,'/');
                break;
            case insDiv:
                mathInstruction(instruction->Id1,instruction->Id2,instruction->Id3,'/');
                break;
            //END MATH
            //CONDITION
            case insCond:
                instruction = instrStackTop(interpretStack);
                if(instruction->type != insIf)
                    throwException(2,0,0);
                // Nactu podminku ifu
                instruction = instrStackTop(interpretStack);

                cond = compareInstruction(instruction->Id1,instruction->Id2,instruction->type);
                // Pokud plati vyraz z podminky
                if(cond == 1) {
                    instruction = instrStackTop(interpretStack);
                    while (instruction->type != insIfEnd) {
                        switch (instruction->type) {
                            case  insIfj16readInt:
                                if(instruction->Id3->inc == 1) {
                                    if (instruction->Id3->data.type == var_int) {
                                        instruction->Id3->data.value.intValue = readInt();
                                        // Pokud neni promenna prirazeni int, pak se jedna o chybu
                                    } else {
                                        throwException(4,0,0);
                                    }
                                    // Pokud pracujeme s neinicializovanou promennou
                                } else {
                                    throwException(8, 0, 0);
                                }
                                break;
                            case insIfj16readString:
                                if(instruction->Id3->inc == 1) {
                                    if(instruction->Id3->data.type == var_string) {
                                        instruction->Id3->data.value.stringValue = readString();
                                    } else {
                                        throwException(4,0,0);
                                    }
                                } else {
                                    throwException(8,0,0);
                                }
                                break;
                                // Pokud se jedna o volani funkce int readDouble();
                            case insIfj16readDouble:
                                if(instruction->Id3->inc == 1) {
                                    if(instruction->Id3->data.type == var_double) {
                                        instruction->Id3->data.value.doubleValue = readDouble();
                                    } else {
                                        throwException(4,0,0);
                                    }
                                } else {
                                    throwException(8,0,0);
                                }
                                break;
                                // Pokud se jedna o volani fce void print(char *string);
                            case insIfj16print:
                                if(instruction->Id1->inc == 1) {
                                    if(instruction->Id3->data.type == var_string) {
                                        print(instruction->Id1->data.value.stringValue);
                                    } else {
                                        throwException(4,0,0);
                                    }
                                } else {
                                    throwException(8,0,0);
                                }
                                break;
                            case insIfj16lenght:
                                if(instruction->Id1->inc == 1 && instruction->Id3->inc == 1) {
                                    if(instruction->Id3->data.type == var_int && instruction->Id1->data.type == var_string) {
                                        instruction->Id3->data.value.intValue = strLength(instruction->Id1->data.value.stringValue);
                                    } else {
                                        throwException(4,0,0);
                                    }
                                } else {
                                    throwException(8,0,0);
                                }
                                break;
                            case insIfj16substr:
                                instruction->Id3->data.value.stringValue = substr(instruction->Id2->variables->data.value.stringValue,instruction->Id2->data.value.intValue, instruction->Id1->data.value.intValue);
                                break;
                            case insIfj16compare:
                                if(instruction->Id1->inc == 1 && instruction->Id3->inc == 1 && instruction->Id2->inc == 1) {
                                    if(instruction->Id3->data.type == var_int && instruction->Id2->data.type == var_string && instruction->Id1->data.type == var_string) {
                                        instruction->Id3->data.value.intValue = strcmp(instruction->Id2->data.value.stringValue,instruction->Id1->data.value.stringValue);
                                    } else {
                                        throwException(4,0,0);
                                    }
                                } else {
                                    throwException(8,0,0);
                                }
                                break;
                            case insIfj16find:
                                if(instruction->Id1->inc == 1 && instruction->Id3->inc == 1 && instruction->Id2->inc == 1) {
                                    if(instruction->Id3->data.type == var_int && instruction->Id2->data.type == var_string && instruction->Id1->data.type == var_string) {
                                        instruction->Id3->data.value.intValue = find(instruction->Id2->data.value.stringValue, instruction->Id1->data.value.stringValue);
                                    } else {
                                        throwException(4,0,0);
                                    }
                                } else {
                                    throwException(8,0,0);
                                }
                                break;
                            case insIfj16sort:
                                if(instruction->Id1->inc == 1 && instruction->Id3->inc == 1) {
                                    if(instruction->Id3->data.type == var_string && instruction->Id1->data.type == var_string) {
                                        instruction->Id3->data.value.stringValue = sort(instruction->Id2->data.value.stringValue);
                                    } else {
                                        throwException(4,0,0);
                                    }
                                } else {
                                    throwException(8,0,0);
                                }
                                break;
                                // END BUILT-IN FUNCTIONS
                                // MATH
                            case insPlusTmp:
                                mathInstruction(instruction->Id1,instruction->Id2,instruction->Id3,'+');
                                break;
                            case insPlus:
                                mathInstruction(instruction->Id1,instruction->Id2,instruction->Id3,'+');
                                break;
                            case insMinusTmp:
                                mathInstruction(instruction->Id1,instruction->Id2,instruction->Id3,'-');
                                break;
                            case insMinus:
                                mathInstruction(instruction->Id1,instruction->Id2,instruction->Id3,'-');
                                break;
                            case insMuxTmp:
                                mathInstruction(instruction->Id1,instruction->Id2,instruction->Id3,'*');
                                break;
                            case insMux:
                                mathInstruction(instruction->Id1,instruction->Id2,instruction->Id3,'*');
                                break;
                            case insDivTmp:
                                mathInstruction(instruction->Id1,instruction->Id2,instruction->Id3,'/');
                                break;
                            case insDiv:
                                mathInstruction(instruction->Id1,instruction->Id2,instruction->Id3,'/');
                                break;
                                //END MATH
                            default:
                                break;
                        }
                        instruction = instrStackTop(interpretStack);
                    }
                // Pokud podminka v ifu neplati, preskoci se telo ifu a vykona se else vetev
                } else {
                    instruction = instrStackTop(interpretStack);
                    while(instruction->type != insIfEnd) {
                        instruction = instrStackTop(interpretStack);
                    }
                    instruction = instrStackTop(interpretStack);
                    // Pokud ya ifem nenasleduje bezpodminecne else
                    if(instruction->type != insElse)
                        throwException(2,0,0);
                    // Nactu si dalsi instrukci
                    instruction = instrStackTop(interpretStack);

                    // Dokud nenarazim na konec podminkz
                    while (instruction->type != insCondEnd) {
                        switch (instruction->type) {
                            case  insIfj16readInt:
                                if(instruction->Id3->inc == 1) {
                                    if (instruction->Id3->data.type == var_int) {
                                        instruction->Id3->data.value.intValue = readInt();
                                        // Pokud neni promenna prirazeni int, pak se jedna o chybu
                                    } else {
                                        throwException(4,0,0);
                                    }
                                    // Pokud pracujeme s neinicializovanou promennou
                                } else {
                                    throwException(8, 0, 0);
                                }
                                break;
                            case insIfj16readString:
                                if(instruction->Id3->inc == 1) {
                                    if(instruction->Id3->data.type == var_string) {
                                        instruction->Id3->data.value.stringValue = readString();
                                    } else {
                                        throwException(4,0,0);
                                    }
                                } else {
                                    throwException(8,0,0);
                                }
                                break;
                                // Pokud se jedna o volani funkce int readDouble();
                            case insIfj16readDouble:
                                if(instruction->Id3->inc == 1) {
                                    if(instruction->Id3->data.type == var_double) {
                                        instruction->Id3->data.value.doubleValue = readDouble();
                                    } else {
                                        throwException(4,0,0);
                                    }
                                } else {
                                    throwException(8,0,0);
                                }
                                break;
                                // Pokud se jedna o volani fce void print(char *string);
                            case insIfj16print:
                                if(instruction->Id1->inc == 1) {
                                    if(instruction->Id3->data.type == var_string) {
                                        print(instruction->Id1->data.value.stringValue);
                                    } else {
                                        throwException(4,0,0);
                                    }
                                } else {
                                    throwException(8,0,0);
                                }
                                break;
                            case insIfj16lenght:
                                if(instruction->Id1->inc == 1 && instruction->Id3->inc == 1) {
                                    if(instruction->Id3->data.type == var_int && instruction->Id1->data.type == var_string) {
                                        instruction->Id3->data.value.intValue = strLength(instruction->Id1->data.value.stringValue);
                                    } else {
                                        throwException(4,0,0);
                                    }
                                } else {
                                    throwException(8,0,0);
                                }
                                break;
                            case insIfj16substr:
                                instruction->Id3->data.value.stringValue = substr(instruction->Id2->variables->data.value.stringValue,instruction->Id2->data.value.intValue, instruction->Id1->data.value.intValue);
                                break;
                            case insIfj16compare:
                                if(instruction->Id1->inc == 1 && instruction->Id3->inc == 1 && instruction->Id2->inc == 1) {
                                    if(instruction->Id3->data.type == var_int && instruction->Id2->data.type == var_string && instruction->Id1->data.type == var_string) {
                                        instruction->Id3->data.value.intValue = strcmp(instruction->Id2->data.value.stringValue,instruction->Id1->data.value.stringValue);
                                    } else {
                                        throwException(4,0,0);
                                    }
                                } else {
                                    throwException(8,0,0);
                                }
                                break;
                            case insIfj16find:
                                if(instruction->Id1->inc == 1 && instruction->Id3->inc == 1 && instruction->Id2->inc == 1) {
                                    if(instruction->Id3->data.type == var_int && instruction->Id2->data.type == var_string && instruction->Id1->data.type == var_string) {
                                        instruction->Id3->data.value.intValue = find(instruction->Id2->data.value.stringValue, instruction->Id1->data.value.stringValue);
                                    } else {
                                        throwException(4,0,0);
                                    }
                                } else {
                                    throwException(8,0,0);
                                }
                                break;
                            case insIfj16sort:
                                if(instruction->Id1->inc == 1 && instruction->Id3->inc == 1) {
                                    if(instruction->Id3->data.type == var_string && instruction->Id1->data.type == var_string) {
                                        instruction->Id3->data.value.stringValue = sort(instruction->Id2->data.value.stringValue);
                                    } else {
                                        throwException(4,0,0);
                                    }
                                } else {
                                    throwException(8,0,0);
                                }
                                break;
                                // END BUILT-IN FUNCTIONS
                                // MATH
                            case insPlusTmp:
                                mathInstruction(instruction->Id1,instruction->Id2,instruction->Id3,'+');
                                break;
                            case insPlus:
                                mathInstruction(instruction->Id1,instruction->Id2,instruction->Id3,'+');
                                break;
                            case insMinusTmp:
                                mathInstruction(instruction->Id1,instruction->Id2,instruction->Id3,'-');
                                break;
                            case insMinus:
                                mathInstruction(instruction->Id1,instruction->Id2,instruction->Id3,'-');
                                break;
                            case insMuxTmp:
                                mathInstruction(instruction->Id1,instruction->Id2,instruction->Id3,'*');
                                break;
                            case insMux:
                                mathInstruction(instruction->Id1,instruction->Id2,instruction->Id3,'*');
                                break;
                            case insDivTmp:
                                mathInstruction(instruction->Id1,instruction->Id2,instruction->Id3,'/');
                                break;
                            case insDiv:
                                mathInstruction(instruction->Id1,instruction->Id2,instruction->Id3,'/');
                                break;
                                //END MATH
                            default:
                                break;
                        }
                        instruction = instrStackTop(interpretStack);
                    }
                }
                break;
            // END CONDITION
            // WHILE
            case insWhile :
                instruction = instrStackTop(interpretStack);
                cond = compareInstruction(instruction->Id1, instruction->Id2, instruction->type);
                whileCondPos = instrStackSize(interpretStack);

                // Nactu instrukci po podmince
                instruction = instrStackTop(interpretStack);
                // Pokud plati podminka while
                if (cond == 1) {
                    // Provadim instrukce do konce cyklu
                    while(instruction->type != insEndWhile) {
                        switch (instruction->type) {
                            case  insIfj16readInt:
                                if(instruction->Id3->inc == 1) {
                                    if (instruction->Id3->data.type == var_int) {
                                        instruction->Id3->data.value.intValue = readInt();
                                        // Pokud neni promenna prirazeni int, pak se jedna o chybu
                                    } else {
                                        throwException(4,0,0);
                                    }
                                    // Pokud pracujeme s neinicializovanou promennou
                                } else {
                                    throwException(8, 0, 0);
                                }
                                break;
                            case insIfj16readString:
                                if(instruction->Id3->inc == 1) {
                                    if(instruction->Id3->data.type == var_string) {
                                        instruction->Id3->data.value.stringValue = readString();
                                    } else {
                                        throwException(4,0,0);
                                    }
                                } else {
                                    throwException(8,0,0);
                                }
                                break;
                                // Pokud se jedna o volani funkce int readDouble();
                            case insIfj16readDouble:
                                if(instruction->Id3->inc == 1) {
                                    if(instruction->Id3->data.type == var_double) {
                                        instruction->Id3->data.value.doubleValue = readDouble();
                                    } else {
                                        throwException(4,0,0);
                                    }
                                } else {
                                    throwException(8,0,0);
                                }
                                break;
                                // Pokud se jedna o volani fce void print(char *string);
                            case insIfj16print:
                                if(instruction->Id1->inc == 1) {
                                    if(instruction->Id3->data.type == var_string) {
                                        print(instruction->Id1->data.value.stringValue);
                                    } else {
                                        throwException(4,0,0);
                                    }
                                } else {
                                    throwException(8,0,0);
                                }
                                break;
                            case insIfj16lenght:
                                if(instruction->Id1->inc == 1 && instruction->Id3->inc == 1) {
                                    if(instruction->Id3->data.type == var_int && instruction->Id1->data.type == var_string) {
                                        instruction->Id3->data.value.intValue = strLength(instruction->Id1->data.value.stringValue);
                                    } else {
                                        throwException(4,0,0);
                                    }
                                } else {
                                    throwException(8,0,0);
                                }
                                break;
                            case insIfj16substr:
                                instruction->Id3->data.value.stringValue = substr(instruction->Id2->variables->data.value.stringValue,instruction->Id2->data.value.intValue, instruction->Id1->data.value.intValue);
                                break;
                            case insIfj16compare:
                                if(instruction->Id1->inc == 1 && instruction->Id3->inc == 1 && instruction->Id2->inc == 1) {
                                    if(instruction->Id3->data.type == var_int && instruction->Id2->data.type == var_string && instruction->Id1->data.type == var_string) {
                                        instruction->Id3->data.value.intValue = strcmp(instruction->Id2->data.value.stringValue,instruction->Id1->data.value.stringValue);
                                    } else {
                                        throwException(4,0,0);
                                    }
                                } else {
                                    throwException(8,0,0);
                                }
                                break;
                            case insIfj16find:
                                if(instruction->Id1->inc == 1 && instruction->Id3->inc == 1 && instruction->Id2->inc == 1) {
                                    if(instruction->Id3->data.type == var_int && instruction->Id2->data.type == var_string && instruction->Id1->data.type == var_string) {
                                        instruction->Id3->data.value.intValue = find(instruction->Id2->data.value.stringValue, instruction->Id1->data.value.stringValue);
                                    } else {
                                        throwException(4,0,0);
                                    }
                                } else {
                                    throwException(8,0,0);
                                }
                                break;
                            case insIfj16sort:
                                if(instruction->Id1->inc == 1 && instruction->Id3->inc == 1) {
                                    if(instruction->Id3->data.type == var_string && instruction->Id1->data.type == var_string) {
                                        instruction->Id3->data.value.stringValue = sort(instruction->Id1->data.value.stringValue);
                                    } else {
                                        throwException(4,0,0);
                                    }
                                } else {
                                    throwException(8,0,0);
                                }
                                break;
                                // END BUILT-IN FUNCTIONS
                                // MATH
                            case insPlusTmp:
                                mathInstruction(instruction->Id1,instruction->Id2,instruction->Id3,'+');
                                break;
                            case insPlus:
                                mathInstruction(instruction->Id1,instruction->Id2,instruction->Id3,'+');
                                break;
                            case insMinusTmp:
                                mathInstruction(instruction->Id1,instruction->Id2,instruction->Id3,'-');
                                break;
                            case insMinus:
                                mathInstruction(instruction->Id1,instruction->Id2,instruction->Id3,'-');
                                break;
                            case insMuxTmp:
                                mathInstruction(instruction->Id1,instruction->Id2,instruction->Id3,'*');
                                break;
                            case insMux:
                                mathInstruction(instruction->Id1,instruction->Id2,instruction->Id3,'*');
                                break;
                            case insDivTmp:
                                mathInstruction(instruction->Id1,instruction->Id2,instruction->Id3,'/');
                                break;
                            case insDiv:
                                mathInstruction(instruction->Id1,instruction->Id2,instruction->Id3,'/');
                                break;
                                //END MATH
                            default:
                                break;
                        }
                        instruction = instrStackTop(interpretStack);
                    }
                //Pokud neplati podminka
                } else {
                    // Dokud se nedostanu na konec while, preskakuju instrukce
                    while(instruction->type != insEndWhile) {
                        instruction = instrStackTop(interpretStack);
                    }
                }
                // Nacteme instrukci reprezentujici pozici vyrazu while(vyraz)
                instructionWhile = instrStackDataAt(interpretStack, whileCondPos);

                // Po dokonceni jednoho cyklu overime jeslti podminka stale plati.
                if(compareInstruction(instructionWhile->Id1, instructionWhile->Id2, instructionWhile->type) == 1) {
                    // Pokud ano, vratime ukazatel vrcholu zasobniku na pozici podminky cyklu-1 (tj prvni instrukce na stacku je insWhile a vse probehne znovu
                    getBackTo(interpretStack, whileCondPos-2);
                }
                // Pokud podminka neplati, pokracujeme ve zpracovani stacku
                break;
             // END WHILE
            // Default
            default:
                break;
        }
    // Konec while- zadne dalsi instrukce ve stacku
    }
}
