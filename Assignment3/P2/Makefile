CC = gcc -std=c11 -pedantic -Wall

all: rand

rand: src/rand.c
	$(CC) src/rand.c -o bin/rand

clean:
	rm -f bin/rand