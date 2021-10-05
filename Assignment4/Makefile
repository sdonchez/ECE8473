################################################################################
## S. Donchez
## Makefile - provides facilities for building and testing Assignment 4 Assets
################################################################################

CC = gcc -std=c11 -pedantic -Wall -I./include/ -L./lib/

all: CBCDecrypt SubsCipher TransCipher

# Main Program Executables
CBCDecrypt: rand src/CBCDecrypt.c
	$(CC) src/CBCDecrypt.c -lrand -o bin/CBCDecrypt

SubsCipher: rand swap src/SubsCipher.c
	$(CC)  src/SubsCipher.c -lrand -lswap -o bin/SubsCipher

TransCipher: rand swap src/TransCipher.c
	$(CC)  src/TransCipher.c -lrand -lswap -o bin/TransCipher

# Libraries
buildLibs: rand swap

rand: src/rand.c
	$(CC) src/rand.c -c -o lib/librand.a

swap: src/swap.c
	$(CC) src/swap.c -c -o lib/libswap.a

# Test Suite
test: all testSubs
	./bin/CBCDecrypt < ./data/CBC.bin
	./bin/TransCipher < ./data/trans.bin

testSubs: SubsCipher
	@chmod +x ./sh/*.sh
	@# save the unmodified subs so we can restore it in clean
	@cp ./sh/subs.sh ./sh/subs.bak
	cd ./sh; ./doSubs.sh
	@cd ..


# Utility Recipies
clean:
	rm -f bin/CBCDecrypt bin/SubsCipher bin/TransCipher 
	rm -f lib/librand.a lib/libswap.a
	@# if we have a backup of subs (unmodified), then replace the modified
	@# copy with the original.
	if [ -f ./sh/subs.bak ]; then \
		mv ./sh/subs.bak ./sh/subs.sh; \
	fi