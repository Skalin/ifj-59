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

#include <stdio.h>
#include <stdlib.h>
#include "error_handler.h"
#include "garbage_collector.h"
void throwException(int errorNumber, int row, int column) {

    fprintf(stderr, "=========================================================================\n" );
    fprintf(stderr, "============================ PROBLEM OCCURED ============================\n" );
    fprintf(stderr, "================= Log may show you where the mistake is =================\n\n" );

    int exit_code;

    if (row == 0 && column == 0)
        fprintf(stderr, "FILE: %s >", global.fileName);
    else
        fprintf(stderr, "FILE: %s line %d, in column %d >", global.fileName, row, column);


    switch(errorNumber) {
        // 1 - chyba v programu v rámci lexikální analýzy (chybná struktura aktuálního lexé-mu).
        case 1:
            fprintf(stderr, "|Lex mistake| Invalid token\n");
            exit_code = 1;
            break;
        // 2 - chyba v programu v rámci syntaktické analýzy (chybná syntaxe programu).
        case 2:
            fprintf(stderr, "|Syntax error| Wrong program syntax\n");
            exit_code = 2;
            break;
        // 3 - sémantická chyba v programu – nedefinovaná třída/funkce/proměnná, pokus o re-definici třídy/funkce/proměnné, atd.
        case 3:
            fprintf(stderr, "|Semantic error| Class/function/variable is not defined or you are attempting to re-define class/function/variable\n");
            exit_code = 3;
            break;
        // 4 - sémantická chyba typové kompatibility v aritmetických,řetězcových a relačních výrazech, příp. špatný počet či typ parametrů u volání funkce.
        case 4:
            fprintf(stderr, "|Semantic error| Wrong type compability in expressions or wrong number/type of arguments while calling function\n");
            exit_code = 4;
            break;
        // 6 - ostatní sémantické chyby.
        case 6:
            fprintf(stderr, "|Semantic error| Unspecified semantic error\n");
            exit_code = 6;
            break;
        // 7 - běhová chyba při načítání číselné hodnoty ze vstupu
        case 7:
            fprintf(stderr, "|Running error| Problem occured while loading number value from STDin\n");
            exit_code = 7;
            break;
        // 8 - běhová chyba při práci s neinicializovanou proměnnou
        case 8:
            fprintf(stderr, "|Running error| Working with uninitialized variable\n");
            exit_code = 8;
            break;
        // 9 - běhová chyba dělení nulou
        case 9:
            fprintf(stderr, "|Running error| Dividing by a zero\n");
            exit_code = 9;
            break;
        // 10 - Ostatní běhové chyby
        case 10:
            fprintf(stderr, "|Running error| Unknown running error\n");
            exit_code = 10;
            break;
        //interní chyba interpretu tj. neovlivnená vstupním programem (napr. chyba a-lokace pameti, chyba při otvírání souboru s řídicím programem, špatné parametry příkazové řádky atd.).
        case 99:
            fprintf(stderr, "|Internal error|");
            exit_code = 99;
            break;
        default:
            fprintf(stderr, "|Uknown error|");
            exit_code = 99;
            break;
    }
    fprintf(stderr, "\n============================= END OF LOG ================================\n" );
    fprintf(stderr, "===================== EXITING PROGRAM with error %d =====================\n", exit_code);
    fprintf(stderr, "=========================================================================\n" );
    exit(exit_code);
}
