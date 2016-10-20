/**
 * IFJ/IAL - Lexikální analyzátor
 * Varianta:    b/2/I
 * Subor:       lexical_analyzer.c
 * Tým:         59
 * Autoři:      Jan Hrbotický, xhrbot01@stud.fit.vutbr.cz
 *              Dominik Skála, xskala11@stud.fit.vutbr.cz
 *              Milan Hruban, xhruba08@stud.fit.vutbr.cz
 *              Martin Hons, xhonsm00@stud.fit.vutbr.cz
 *              David Hél, xhelda00@stud.fit.vutbr.cz
 */

#include "lexical_analyzer.h"


char *keyWordTable[NUMBER_OF_KEY_WORDS] = {
    "boolean","break","class","continue","do",
    "double","else","false","for","if","int",
    "return","String","static","true","void","while"
};

char *keyWordTokenTable[NUMBER_OF_KEY_WORDS] = {
    "token_boolean","token_break","token_class","token_continue","token_do",
    "token_double","token_else","token_false","token_for","token_if","token_int",
    "token_return","token_String","token_static","token_true","token_void","token_while"
};

void printKeyWordTable() {
    for (int i = 0; i < 17; i++) {
        printf("%3d. keyword: %10s    token: %s\n", i + 1, keyWordTable[i], keyWordTokenTable[i]);
    }
}
