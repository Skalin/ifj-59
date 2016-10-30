CC=gcc
CFLAGS=-std=c99 -Wall -Werror -pedantic
BIN=projekt

FILES= main.c garbage_collector.c lexical_analyzer.c error_handler.c typedef.c

all: main.c
	$(CC) $(CFLAGS) $(FILES) -o $(BIN)
