CC=gcc
CFLAGS=-Wall -Werror

makeFiles= main.c lexical_analyzer.c

make:
    $(CC) -o $(makeFiles)