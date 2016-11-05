/**
 * IFJ/IAL - Lexikální analyzátor
 * Varianta:    b/2/I
 * Soubor:      return.c
 * Tým:         59
 * Autoři:      Jan Hrbotický, xhrbot01@stud.fit.vutbr.cz
 *              Dominik Skála, xskala11@stud.fit.vutbr.cz
 *              Milan Hruban, xhruba08@stud.fit.vutbr.cz
 *              Martin Hons, xhonsm00@stud.fit.vutbr.cz
 *              David Hél, xhelda00@stud.fit.vutbr.cz
 */
 
#ifndef RETURN
#define RETURN

/**
 * Jestliže proběhne činnost interpretu bez chyb, vrací se návratová hodnota 0.
 * Pokud dojde k chybě, vrací se návratová hodnota podle zadání. 
 */
typedef enum {
  E_NO_ERROR;              //činnost proběhla bez chyb (0)
  E_SCANNER_ERROR;         //chyba lexykánlí analýzy (1)
  E_PARSER_ERROR;          //chyba syntaktické analýzy (2)
  E_SEM_NO_DEF_ERROR;      //sémantická chyba nedefinovaná třída/funkce/proměnná, pokus o redefinici třídy/funkce/proměnné, atd (3)
  E_SEM_TYPE_COMP_ERROR;   //sémantická chyba typové kompatibility (4)
  E_SEM_OTHER_ERROR;       //sémantická chyba - ostatní (6)
  E_INPUT_ERROR;           //chyba při načítání číselné hodnoty ze vstupu (7)
  E_VAR_NO_INIT_ERROR;     //chyba při práci s neinicializovanou proměnnou (8)
  E_DIV_BY_ZERO_ERROR;     //dělení nulou (9)
  E_OTHERS_ERROR;          //ostatní běhové chyby (10)
  E_INTERNAL_ERROR;        //interní chyba interpretu (99)
} retError;

#endif
