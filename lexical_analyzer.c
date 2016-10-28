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

// some coding

void keywordCheckToken(tToken *token) {
    //Tabulky
    char *keyWordTable[NUMBER_OF_KEY_WORDS] = {
        "boolean","break","class","continue","do",
        "double","else","false","for","if","int",
        "return","String","static","true","void","while"
    };

    tStatus keyWordTokenTable[NUMBER_OF_KEY_WORDS] = {
            "LA_BOOLEAN","LA_BREAK","LA_CLASS","LA_CONTINUE","LA_DO",
            "LA_DOUBLE","LA_ELSE","LA_FALSE","LA_FOR","LA_IF","LA_INT",
            "LA_RETURN","LA_STRING","LA_STATIC","LA_TRUE","LA_VOID","LA_WHILE"
    };

    // For cyklus prohledá první tabulku a pokud v ní nalezne shodu v tokenu (strcmp()), přiřadí do tToken type příslušnou hodnotu z druhé tabulky
    // DONE Jan Hrbotický
    for (int i=0; i<(NUMBER_OF_KEY_WORDS-1); i++) {
        if (strcmp(keyWordTable[i], token->data) == 0)
            token->status = keyWordTokenTable[i];
    }
}


// Pomocne objekty
tToken * t_buffer;

// Body

tToken * initToken() {
    // Inicializace tokenu, prvni malloc, pak inicializace jednotlivych slozek
    // POZOR, ZDE SE MUSÍ IMPLEMENTOVAT CELÝ NOVÝ SOUBOR, KTERÝ BUDE OBSHAOVAT FUNKCE MALLOC, FREE, REALLOC, A ZRUŠENÍ
    // Jedná se o to, že všechny data budou v listovém seznamu (viz 1. úkol IAL)
}

tToken updateToken( tToken * token, char *string ) {
   // Alokace mista pokud je potreba, zvyseni delky ve strukture (lenght), kontrola jestli alokace probehla uspesne
    // Pomoci strncat() pridat novy retezec nakonec
    // POZOR, ZDE SE MUSÍ IMPLEMENTOVAT CELÝ NOVÝ SOUBOR, KTERÝ BUDE OBSHAOVAT FUNKCE MALLOC, FREE, REALLOC, A ZRUŠENÍ
    // Jedná se o to, že všechny data budou v listovém seznamu (viz 1. úkol IAL)
}

void token_return_token(tToken * token) {
    // Do tokenu přiřadí načtené hodnoty z pomocného tokenu t_buffer
    t_buffer = token;
}

void destroytoken( tToken * token) {
    // Zruší daný token
    // POZOR, ZDE SE MUSÍ IMPLEMENTOVAT CELÝ NOVÝ SOUBOR, KTERÝ BUDE OBSHAOVAT FUNKCE MALLOC, FREE, REALLOC, A ZRUŠENÍ
    // Jedná se o to, že všechny data budou v listovém seznamu (viz 1. úkol IAL)
}

tToken * getToken( tToken * token){
    // Připojí se do souboru a postupně načte následující token (+ o něm přidá informace do struktury tToken)
}
