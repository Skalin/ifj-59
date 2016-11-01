#
# IFJ 2014/2015 Makefie
#

CC=gcc
CFLAGS=-O2 -std=c99 -lm -Wall -pedantic -g -rdynamic
OBJFILES=$(patsubst %.c, build/%.c.o, $(shell ls src/*.c))
TESTFILES=$(patsubst tests/%.pas, tests/%, $(shell ls tests/*.pas));
SHELL=bash

# build
all: ifj

ifj: $(OBJFILES)
	$(CC) $(CFLAGS) *.o -o ifj

build/%.c.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $(subst src/, build/, $<.o)

