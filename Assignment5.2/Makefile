################################################################################
## S. Donchez
## Makefile - provides facilities for building and testing Assignment 5.2 Assets
################################################################################

CC = gcc -std=c11 -pedantic -Wall -I./include/ -L./lib/

all: library src/tester.c
	[ -d ./bin ] || mkdir -p ./bin
	$(CC) src/tester.c -lstrfxns -o bin/tester

library: src/strfxns.c
	[ -d ./lib ] || mkdir -p ./lib
	$(CC) src/strfxns.c -c -o lib/libstrfxns.a

test: all
	./bin/tester

clean:
	rm -f bin/tester
	rm -f lib/libstrfxns.a