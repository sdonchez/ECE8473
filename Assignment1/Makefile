CC = gcc -std=c11 -pedantic -Wall

all: p1 p2 p3 p4

p1: src/p1.c
	$(CC) src/p1.c -o bin/p1

p2: src/p2.c
	$(CC) src/p2.c -o bin/p2

p3: src/p3.c
	$(CC) src/p3.c -o bin/p3 -lm

p4: src/p4.c
	$(CC) src/p4.c -o bin/p4

test: all
	./bin/p1
	./bin/p2
	./bin/p3
	./bin/p4

clean:
	rm -f bin/p1 bin/p2 bin/p3 bin/p4