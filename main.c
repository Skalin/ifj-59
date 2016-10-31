#include "lexical_analyzer.h"
#include <stdbool.h>
#include "typedef.h"

static const char *tokenTypeString[] = {
    "t_error","t_int","t_double","t_double_e","t_string","t_simple_ident","t_complete_ident","t_div","t_multi","t_plus","t_minus","t_greater","t_greater_eq","t_less","t_less_eq","t_assignment","t_comparasion","t_excl_mark","t_comparasion_ne","t_sq_bracket_l","t_sq_bracket_r","t_bracket_l","t_bracket_r","t_brace_l","t_brace_r","t_simple_comment","t_block_comment_start","t_block_comment_end","t_semicolon","t_eof","t_kw_class","t_kw_static","t_kw_boolean","t_kw_double","t_kw_int","t_kw_string","t_kw_void","t_kw_while","t_kw_for","t_kw_break","t_kw_return","t_kw_continue","t_kw_do","t_kw_if","t_kw_else","t_kw_true","t_kw_false"
};

bool header = false;

int main(int argc, char* argv[]) {
    char *file = "testing/test_files/fac_iter.ifj";  
    tToken *pToken = NULL;
    global.fileName = argv[1];
    global.file = fopen(global.fileName, "r");
/*
    pToken = initToken();   // Inicializace tokenu
    printToken(pToken);
    
    pToken = updateToken(pToken,"vlozim_neco");  // 
    printToken(pToken);
    
    pToken = updateToken(pToken,"_pridam_neco");  // 
    printToken(pToken);
    

    destroyToken(pToken);   // Zrušení tokenu
    
    
    printToken(pToken);*/
    pToken = getToken(pToken,file);
    //printToken(pToken);
    return 0;
}


void printToken(tToken *token) {
    if (!header){
        printf("--length----status------type----------data-------\n");
        header = true;
    }
    
    printf("%8d    %6d    %10s   |%s|\n",token->length,token->allocated,tokenTypeString[token->type],token->data);
}
