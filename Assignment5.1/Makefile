################################################################################
## S. Donchez
## Makefile - provides facilities for building and testing Assignment 5.1 Assets
################################################################################

CC = gcc -std=c11 -pedantic -Wall -g

all: tester system

tester: tester.o string.o
	$(CC) -o bin/tester bin/tester.o bin/string.o

tester.o: src/tester.c
	$(CC) -c src/tester.c -o bin/tester.o

string.o: src/string.c
	$(CC) -c src/string.c -o bin/string.o

system: src/tester.c # using system string library, ignore warnings
	$(CC) -w -o bin/system -DSYSTEM src/tester.c

clean:
	rm -f bin/tester bin/tester.o bin/string.o bin/system