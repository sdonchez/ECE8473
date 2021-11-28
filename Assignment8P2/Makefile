################################################################################
## S.Donchez
## ECE8473-DL1
## Makefile - builds the targets required for Assignment 8 Part 2
################################################################################

CC = gcc -std=c11 -pedantic -Wall

all: bin/q2 

bin/q2: src/q2.c | bin
	$(CC) src/q2.c -o bin/q2 -lm

## Utility Recipies

clean:
	rm -rf ./bin/q2

bin:
	mkdir -p $@