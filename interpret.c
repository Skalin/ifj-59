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
#include <stdio.h>
#include <string.h>


#include "typedef.h"
#include "interpret.h"
#include "error_handler.h"
#include "ial.h"




// Definice flagů


BTSNode* getVariable(char* id) {
    //TODO
    return NULL;
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


void compareInstruction(BTSNode *Id1, BTSNode *Id2, BTSNode *Id3, InstrType operation) {
    if(Id1->inc != 0 || Id2->inc != 0) {
        if(operation == insEqual) {
            // Pokud se jedna o porovnani double double nebo int int
            if ((Id1->data.type == var_double && Id2->data.type == var_double) || (Id1->data.type == var_int && Id2->data.type == var_int)) {
                Id3->data.type = var_int;
                Id3->inc = 1;

                if (Id1->data.type == var_double) {
                    Id3->data.value.intValue = (Id1->data.value.doubleValue == Id2->data.value.doubleValue ? 1 : 0);
                } else {
                    Id3->data.value.intValue = (Id1->data.value.intValue == Id2->data.value.intValue ? 1 : 0);
                }
            // Pokud se jedna o porovnani double int nebo int double
            } else if ((Id1->data.type == var_double && Id2->data.type == var_int) || (Id1->data.type == var_int && Id2->data.type == var_double)) {
                Id3->data.type = var_double;
                Id3->inc = 1;

                if (Id1->data.type == var_double) {
                    Id3->data.value.intValue = (Id1->data.value.doubleValue == (double)Id2->data.value.intValue ? 1 : 0);
                } else {
                    Id3->data.value.intValue = ((double)Id1->data.value.intValue == Id2->data.value.doubleValue ? 1 : 0);
                }
            // Pokud je na vstupu jiny uzel nez povoleny, je to semanticka chyba
            } else
                throwException(4,0,0);
        // a != b
        } else if(operation == insNotEqual) {
            // Pokud se jedna o porovnani double double nebo int int
            if ((Id1->data.type == var_double && Id2->data.type == var_double) || (Id1->data.type == var_int && Id2->data.type == var_int)) {
                Id3->data.type = var_int;
                Id3->inc = 1;

                if (Id1->data.type == var_double) {
                    Id3->data.value.intValue = (Id1->data.value.doubleValue != Id2->data.value.doubleValue ? 1 : 0);
                } else {
                    Id3->data.value.intValue = (Id1->data.value.intValue != Id2->data.value.intValue ? 1 : 0);
                }
                // Pokud se jedna o porovnani double int nebo int double
            } else if ((Id1->data.type == var_double && Id2->data.type == var_int) || (Id1->data.type == var_int && Id2->data.type == var_double)) {
                Id3->data.type = var_double;
                Id3->inc = 1;

                if (Id1->data.type == var_double) {
                    Id3->data.value.intValue = (Id1->data.value.doubleValue != (double)Id2->data.value.intValue ? 1 : 0);
                } else {
                    Id3->data.value.intValue = ((double)Id1->data.value.intValue != Id2->data.value.doubleValue ? 1 : 0);
                }
                // Pokud je na vstupu jiny uzel nez povoleny, je to semanticka chyba
            } else
                throwException(4,0,0);
        // a < b
        } else if(operation == insLess) {
            // Pokud se jedna o porovnani double double nebo int int
            if ((Id1->data.type == var_double && Id2->data.type == var_double) || (Id1->data.type == var_int && Id2->data.type == var_int)) {
                Id3->data.type = var_int;
                Id3->inc = 1;

                if (Id1->data.type == var_double) {
                    Id3->data.value.intValue = (Id1->data.value.doubleValue < Id2->data.value.doubleValue ? 1 : 0);
                } else {
                    Id3->data.value.intValue = (Id1->data.value.intValue < Id2->data.value.intValue ? 1 : 0);
                }
                // Pokud se jedna o porovnani double int nebo int double
            } else if ((Id1->data.type == var_double && Id2->data.type == var_int) || (Id1->data.type == var_int && Id2->data.type == var_double)) {
                Id3->data.type = var_double;
                Id3->inc = 1;

                if (Id1->data.type == var_double) {
                    Id3->data.value.intValue = (Id1->data.value.doubleValue < (double)Id2->data.value.intValue ? 1 : 0);
                } else {
                    Id3->data.value.intValue = ((double)Id1->data.value.intValue < Id2->data.value.doubleValue ? 1 : 0);
                }
                // Pokud je na vstupu jiny uzel nez povoleny, je to semanticka chyba
            } else
                throwException(4,0,0);
        // a <= b
        } else if(operation == insLessOrEqual) {
            // Pokud se jedna o porovnani double double nebo int int
            if ((Id1->data.type == var_double && Id2->data.type == var_double) || (Id1->data.type == var_int && Id2->data.type == var_int)) {
                Id3->data.type = var_int;
                Id3->inc = 1;

                if (Id1->data.type == var_double) {
                    Id3->data.value.intValue = (Id1->data.value.doubleValue <= Id2->data.value.doubleValue ? 1 : 0);
                } else {
                    Id3->data.value.intValue = (Id1->data.value.intValue <= Id2->data.value.intValue ? 1 : 0);
                }
                // Pokud se jedna o porovnani double int nebo int double
            } else if ((Id1->data.type == var_double && Id2->data.type == var_int) || (Id1->data.type == var_int && Id2->data.type == var_double)) {
                Id3->data.type = var_double;
                Id3->inc = 1;

                if (Id1->data.type == var_double) {
                    Id3->data.value.intValue = (Id1->data.value.doubleValue <= (double)Id2->data.value.intValue ? 1 : 0);
                } else {
                    Id3->data.value.intValue = ((double)Id1->data.value.intValue <= Id2->data.value.doubleValue ? 1 : 0);
                }
                // Pokud je na vstupu jiny uzel nez povoleny, je to semanticka chyba
            } else
                throwException(4,0,0);
        // a > b
        } else if(operation == insGreater) {
            // Pokud se jedna o porovnani double double nebo int int
            if ((Id1->data.type == var_double && Id2->data.type == var_double) || (Id1->data.type == var_int && Id2->data.type == var_int)) {
                Id3->data.type = var_int;
                Id3->inc = 1;

                if (Id1->data.type == var_double) {
                    Id3->data.value.intValue = (Id1->data.value.doubleValue > Id2->data.value.doubleValue ? 1 : 0);
                } else {
                    Id3->data.value.intValue = (Id1->data.value.intValue > Id2->data.value.intValue ? 1 : 0);
                }
                // Pokud se jedna o porovnani double int nebo int double
            } else if ((Id1->data.type == var_double && Id2->data.type == var_int) || (Id1->data.type == var_int && Id2->data.type == var_double)) {
                Id3->data.type = var_double;
                Id3->inc = 1;

                if (Id1->data.type == var_double) {
                    Id3->data.value.intValue = (Id1->data.value.doubleValue > (double)Id2->data.value.intValue ? 1 : 0);
                } else {
                    Id3->data.value.intValue = ((double)Id1->data.value.intValue > Id2->data.value.doubleValue ? 1 : 0);
                }
                // Pokud je na vstupu jiny uzel nez povoleny, je to semanticka chyba
            } else
                throwException(4,0,0);
        // a >=
        } else if(operation == insGreaterOrEqual) {
            // Pokud se jedna o porovnani double double nebo int int
            if ((Id1->data.type == var_double && Id2->data.type == var_double) || (Id1->data.type == var_int && Id2->data.type == var_int)) {
                Id3->data.type = var_int;
                Id3->inc = 1;

                if (Id1->data.type == var_double) {
                    Id3->data.value.intValue = (Id1->data.value.doubleValue >= Id2->data.value.doubleValue ? 1 : 0);
                } else {
                    Id3->data.value.intValue = (Id1->data.value.intValue >= Id2->data.value.intValue ? 1 : 0);
                }
                // Pokud se jedna o porovnani double int nebo int double
            } else if ((Id1->data.type == var_double && Id2->data.type == var_int) || (Id1->data.type == var_int && Id2->data.type == var_double)) {
                Id3->data.type = var_double;
                Id3->inc = 1;

                if (Id1->data.type == var_double) {
                    Id3->data.value.intValue = (Id1->data.value.doubleValue >= (double)Id2->data.value.intValue ? 1 : 0);
                } else {
                    Id3->data.value.intValue = ((double)Id1->data.value.intValue >= Id2->data.value.doubleValue ? 1 : 0);
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
}

void interpretMainCore() {
    // Uzel stromu instrukci
    BTSNode *node = NULL; // TODO, vola se funkce, ktera ze stacku vybere prvni polozku
    // Promenna, do ktere se ukladaji informace o instrukci
    Instr *instruction = NULL;

    while( /*node != NULL*/ ) {
        instruction = NULL; // TODO, priradi se hodnota node-> data obsahujici adresy trojadresneho kodu a info o jakou instrukci se jedna


        // Switch pro jednotlive typy instrukci
        switch (instruction->type) {
            // BUILT-IN FUNCTIONS
            case  insIfj16print:

            // END BUILT-IN FUNCTIONS
            // MATH
            case insPlus:
                mathInstruction(getVariable(instruction->Id1),getVariable(instruction->Id2),getVariable(instruction->Id3),'+');
                break;
            case insMinus:
                mathInstruction(getVariable(instruction->Id1),getVariable(instruction->Id2),getVariable(instruction->Id3),'-');
                break;
            case insMux:
                mathInstruction(getVariable(instruction->Id1),getVariable(instruction->Id2),getVariable(instruction->Id3),'*');
                break;
            case insDiv:
                mathInstruction(getVariable(instruction->Id1),getVariable(instruction->Id2),getVariable(instruction->Id3),'/');
                break;
            //END MATH
            //COMPARE
            case insEqual:
                compareInstruction(getVariable(instruction->Id1),getVariable(instruction->Id2),getVariable(instruction->Id3),insEqual);
                break;
            case insNotEqual:
                compareInstruction(getVariable(instruction->Id1),getVariable(instruction->Id2),getVariable(instruction->Id3),insNotEqual);
                break;
            case insLess:
                compareInstruction(getVariable(instruction->Id1),getVariable(instruction->Id2),getVariable(instruction->Id3),insLess);
                break;
            case insLessOrEqual:
                compareInstruction(getVariable(instruction->Id1),getVariable(instruction->Id2),getVariable(instruction->Id3),insLessOrEqual);
                break;
            case insGreater:
                compareInstruction(getVariable(instruction->Id1),getVariable(instruction->Id2),getVariable(instruction->Id3),insGreater);
                break;
            case insGreaterOrEqual:
                compareInstruction(getVariable(instruction->Id1),getVariable(instruction->Id2),getVariable(instruction->Id3),insGreaterOrEqual);
                break;
            //END COMPARE
        }
    //TODO ZBYTEK INTERPRETU
    }

}
