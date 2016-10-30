#
# IFJ 2014/2015 Makefie
#

CC=gcc
CFLAGS=-O2 -std=c99 -lm -Wall -pedantic -g -rdynamic
OBJFILES=$(patsubst src/%.c, build/%.c.o, $(shell ls src/*.c))
TESTFILES=$(patsubst tests/%.pas, tests/%, $(shell ls tests/*.pas));
SHELL=bash

# build
all: ifj

ifj: $(OBJFILES)
	$(CC) $(CFLAGS) build/*.o -o ifj

build/%.c.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $(subst src/, build/, $<.o)



# Test
tests: ifj $(TESTFILES)
	# Done

tests/%: tests/%.pas
	@echo -e "\n"
	-$(shell valgrind ./ifj $< < $@.stdin > /dev/null 2> $@.valgrind.real; if [ $$(grep "ERROR SUMMARY: 0 errors from 0 contexts" $@.valgrind.real | wc -l) = "1" ]; then rm $@.valgrind.real; else /bin/echo -e "#"; grep "ERROR SUMMARY:" $@.valgrind.real;  fi;  )
	-$(shell ./ifj $< > $@.stdout.real 2> $@.stderr.real < $@.stdin;echo "$$?" > $@.exit.real;diff $@.stdout.real $@.stdout.correct > /dev/null;if [ "$$?" = "0" ]; then diff $@.stderr.real $@.stderr.correct > /dev/null;if [ "$$?" = "0" ]; then diff $@.exit.real $@.exit.correct > /dev/null; if [ "$$?" = "0" ]; then echo "# OK ... $@"; rm $@.stdout.real $@.stderr.real $@.exit.real; else echo "# ERROR ... $@"; fi; else echo "# ERROR ... $@"; fi; else echo "# ERROR ... $@"; fi)

sandwich:
	-$(shell if [[ $$(whoami) == "root" ]] ; then echo "# Yes, my lord."; else echo "# You are not root!"; fi)
