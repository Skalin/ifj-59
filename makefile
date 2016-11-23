#
# IFJ 2014/2015 Makefie
#

CC=gcc
CFLAGS=-O2 -std=c99 -lm -Wall -pedantic -g -rdynamic
OBJFILES=$(patsubst %.c, %.c.o, $(shell ls *.c))
TESTFILES=$(patsubst tests/%.pas, tests/%, $(shell ls tests/*.pas));
SHELL=bash

# build
all: ifj

ifj: $(OBJFILES)
	$(CC) $(CFLAGS) *.o -o ifj

%.c.o: %.c
	$(CC) $(CFLAGS) -c $< -o $(subst , , $<.o)



#
#   IFJ/IAL - Makefile
#
#   Varianta:   b/2/I
#   Soubor:     makefile
#   Tým:        59
#
#   Autoři:     Jan Hrbotický, xhrbot01@stud.fit.vutbr.cz
#               Dominik Skála, xskala11@stud.fit.vutbr.cz
#               Milan Hruban, xhruba08@stud.fit.vutbr.cz
#               Martin Hons, xhonsm00@stud.fit.vutbr.cz
#               David Hél, xhelda00@stud.fit.vutbr.cz
#


CC=gcc
MAIN=main
CFLAGS=-g -o MAIN -std=c99 -Wall -Wextra -Werror -pedantic -lm
ALLFILES=(*).c

all:    MAIN

MAIN:


clean:
        rm -rf *.o *~ $(MAIN)


