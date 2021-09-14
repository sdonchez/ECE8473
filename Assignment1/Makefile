CC = gcc -std=c11 -pedantic -Wall

all: p1 p2 p3 p4

p1: p1.c
	$(CC) p1.c -o p1

p2: p2.c
	$(CC) p2.c -o p2

p3: p3.c
	$(CC) p3.c -o p3 -lm

p4: p4.c
	$(CC) p4.c -o p4

clean:
	rm -f p1 p2 p3 p4