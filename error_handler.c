/**
 * IFJ/IAL - Error handler
 * Varianta:    b/2/I
 * Soubor:       error_handler.c
 * Tým:         59
 * Autoři:      Jan Hrbotický, xhrbot01@stud.fit.vutbr.cz
 *              Dominik Skála, xskala11@stud.fit.vutbr.cz
 *              Milan Hruban, xhruba08@stud.fit.vutbr.cz
 *              Martin Hons, xhonsm00@stud.fit.vutbr.cz
 *              David Hél, xhelda00@stud.fit.vutbr.cz
 */

#include "error_handler.h"
#include "garbage_collector.h"
#include "typedef.h"

void throwException(int errorNumber, int row, int column) {
    int exit_code;
    fprintf(stderr, "FILE: %s | Error on line %d, in column %d\n", global.fileName, row, column);

    switch(errorNumber) {
        case 1:
            fprintf(stderr, "Lex mistake (Invalid token)\n");
            exit_code = 1;
            break;
            
        case 2:
            fprintf(stderr, "Syntactic analyses error\n");
            exit_code = 2;
            break;  
            
        case 3:
            fprintf(stderr, "Semantic analyses error (Function, class or variable is not defined)\n");
            exit_code = 3;
            break;        
            
        case 99:
            fprintf(stderr, "Internal error ");
            exit_code = 99;
            break;
            
        case eAllocation:
            fprintf(stderr, "Allocation error\n");
            exit_code = 11;
            break;        
            
        case eEOF:
            fprintf(stderr, "End of file\n");
            exit_code = 12;
            break;       
            
            //Sem doplňujte případné další chyby
        default:
            fprintf(stderr, "Unknown error\n");
            exit_code = 10;
            break;
    }

    fprintf(stderr, "Problem occured. Previous log may show you where the mistake is.\n" );
    fprintf(stderr, "===================== EXITING PROGRAM with error %d =====================\n", exit_code);
    exit(exit_code);
}
