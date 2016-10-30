#include "lexical_analyzer.h"


int main() {
    
    char *file = "testing_test_files/fac_iter.ifj";  
    tToken *pToken = initToken();
    
    getToken(pToken,file);
    return 0;
}
