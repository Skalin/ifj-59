CC=gcc
CFLAGS=-std=c99 -Wall -Werror

makeFiles= main.c main.h garbage_collector.c garbage_collector.h error_handler.c error_handler.h

make:
    $(CC) -o $(makeFiles)