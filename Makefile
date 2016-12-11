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
CFLAGS=-std=c99 -g -lm
OBJFILES=$(patsubst %.c, %.c.o, $(shell ls *.c))
TESTFILES=$(patsubst tests/%.pas, tests/%, $(shell ls tests/*.pas));
SHELL=bash

# build
all: ifj
	rm -rf *.c.o

ifj: $(OBJFILES)
	$(CC) $(CFLAGS) *.o -o ifj

%.c.o: %.c
	$(CC) $(CFLAGS) -c $< -o $(subst , , $<.o)

clean: 
	rm -rf *.c.o
	rm -rf ./ifj