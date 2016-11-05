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
  E_NO_ERROR;            
  E_SCANNER_ERROR;
  E_PARSER_ERROR;
  E_SEM_NO_DEF_ERROR;
  E_SEM_TYPE_COMP_ERROR;
  E_SEM_OTHER_ERROR;
  E_INPUT_ERROR;
  E_VAR_NO_INIT_ERROR;
  E_DIV_BY_ZERO_ERROR;
  E_OTHERS_ERROR;
  E_INTERNAL_ERROR;
} retError;

#endif
