################################################################################
## S.Donchez
## ECE8473-DL1
## Makefile - builds the targets required for Assignment 8
################################################################################

CC = gcc -std=c11 -pedantic -Wall

all: bin/b2 

bin/b2: src/b2.c | bin
	$(CC) src/b2.c -o bin/b2

## Utility Recipies

clean:
	rm -rf ./bin/b2

bin:
	mkdir -p $@