################################################################################
## S. Donchez
## Makefile - provides facilities for building and testing Assignment 6 Assets
################################################################################

CC = gcc -std=c11 -pedantic -Wall -I./include/ -L./lib/

all: p1 p2

p1: libTableEncrypt src/p1.c
	$(CC) src/p1.c -o bin/p1 -lTableEncrypt

p2: libTableEncrypt src/p2.c
	$(CC) src/p2.c -o bin/p2 -lTableEncrypt

libTableEncrypt: src/TableEncryption.c
	$(CC) src/TableEncryption.c -c -o lib/libTableEncrypt.a
	
clean:
	rm -f bin/p1; rm -f bin/p2;