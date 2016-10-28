/*
 * IFJ/IAL - Error handler
 * Varianta:    b/2/I
 * Subor:       error_handler.c
 * Tým:         59
 * Autoři:      Jan Hrbotický, xhrbot01@stud.fit.vutbr.cz
 *              Dominik Skála, xskala11@stud.fit.vutbr.cz
 *              Milan Hruban, xhruba08@stud.fit.vutbr.cz
 *              Martin Hons, xhonsm00@stud.fit.vutbr.cz
 *              David Hél, xhelda00@stud.fit.vutbr.cz
 */

#include <stdlib.h>
#include "error_handler.h"
#include <stdio.h>

void throwException( int errorNumber, int row) {
    int exit_code= 1;
    fprintf(stderr, "FILE: %s | Error on line %d", "Doplnit globalni promennou na file", row);

    switch(errorNumber) {
        case 1:
            fprintf(stderr, "Lex mistake (Invalid token)");
            exit_code= 1;
            break;
        case 99:
            fprintf(stderr, "Internal error ");
            exit_code= 99;
            break;
            //Sem doplňujte případné další chyby
        default:
            fprintf(stderr, "Unknown error");
            exit_code= 10;
            break;
    }

    fprintf(stderr, "Problem occured. Previous log may show you where the mistake is." );
    fprintf(stderr, "===================== EXITING PROGRAM with error %d =====================", exit_code);
    exit(exit_code);
}