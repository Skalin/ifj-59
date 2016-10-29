CC=gcc
CFLAGS=-std=c99 -Wall -Werror -pedantic
BIN=projekt

makeFiles= main.c garbage_collector.c error_handler.c

make:
    $(CC) $(CFLAGS) $(makeFiles) -o $(BIN)