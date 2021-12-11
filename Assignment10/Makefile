################################################################################
## S.Donchez
## ECE8473-DL1
## Makefile - builds the targets required for Assignment 10
################################################################################

CC = gcc -std=c11 -pedantic -Wall

all: bin/villcoin 

bin/villcoin: src/villcoin.c | bin
	$(CC) src/villcoin.c -o bin/villcoin -lcrypto -pthread

## Utility Recipies

clean:
	rm -rf ./bin/villcoin

bin:
	mkdir -p $@