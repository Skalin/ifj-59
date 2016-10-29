CC=gcc
CFLAGS=-std=c99 -Wall -Werror

makeFiles= main.c garbage_collector.c error_handler.c

make:
    $(CC) -o $(makeFiles)