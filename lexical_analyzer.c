char *keyWordTable[17] = {"boolean","break","class","continue","do","double","else","false","for","if","int","return","String","static","true","void","while"};
char *keyWordTokenTable[17] = {"token_boolean","token_break","token_class","token_continue","token_do","token_double","token_else","token_false","token_for","token_if","token_int","token_return","token_String","token_static","token_true","token_void","token_while"};

void printKeyWordTable() {
    for (int i = 0; i < 17; i++) {
        printf("%3d. keyword: %10s    token: %s\n", i + 1, keyWordTable[i], keyWordTokenTable[i]);
    }
}
