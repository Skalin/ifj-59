#include <stdio.h>
#include <stdlib.h>
int fib(int x);

int main() {
    int i;

    for (i=1; i<20; i++) {
        printf("Fib %d = %d\n", i, fib(i));
    }
    return 0;
}

int fib(int x) {
    if (x == 1 || x == 2) {
        return 1;
    }
    else {
        int current=1;
        int prev=1;
        for(int i=2; i<x; i++) {
            current += prev;
            prev = current - prev;
        }
        return current;
    }
}