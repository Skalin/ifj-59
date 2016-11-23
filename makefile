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
CFLAGS=-g -std=c99 -Wall -Wextra -Werror -pedantic -lm
ALLFILES=$(wildcard *.c)
OBJS=$(ALLFILES:.c=.o)

main:	$(OBJS)
		gcc -o main  $(CFLAGS) $(ALLFILES)

%.o : %.c


clean:
		rm -rf *.o *~ $(MAIN)


