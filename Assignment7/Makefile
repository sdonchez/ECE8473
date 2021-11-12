################################################################################
## S.Donchez
## ECE8473-DL1
## Makefile - builds the targets required for Assignment 7
################################################################################

CC = gcc -std=c11 -pedantic -Wall

all: bin/p1 bin/p2 

bin/p1: src/p1.c | bin
	$(CC) src/p1.c -o bin/p1

bin/p2: src/p2.c | bin
	$(CC) src/p2.c -o bin/p2

## Utility Recipies

clean:
	rm -rf ./bin/p1 ./bin/p2

bin:
	mkdir -p $@

test: all
	cd ./sh; ./test1.sh ../bin/p1
	cd ./sh; ./test2.sh ../bin/p2