CC=gcc
CFLAGS=-Wall -Werror

makeFiles= main.c lexical_analyzer.c garbage_collector.c error_handler.c

make:
    $(CC) -o $(makeFiles)