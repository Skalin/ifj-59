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