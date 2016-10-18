char *keyWordTable[17] = {"boolean","break","class","continue","do","double","else","false","for","if","int","return","String","static","true","void","while"};

void printKeyWordTable() {
    for (int i = 0; i < 17; i++) {
        printf("%3d. keyword table item: %s\n", i + 1, keyWordTable[i]);
    }
}
