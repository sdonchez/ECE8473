////////////////////////////////////////////////////////////////////////////////
// Stephen Donchez
// p1.c - table encrypt
// Write a C program to implement table encryption, described below. The program
// usage is: ./p1 [n] < plaintext > ciphertext
// Where n is the table row length, default = 5.
//
// The program must read all of standard input into a character array, remove 
// all whitespace from the input, and then pad the input with 'o' characters if 
// necessary to make the length a multiple of n.Then print the ciphertext 
// followed by a single newline to standard output.
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h> //for printf, BUFSIZ
#include "TableEncryption.h" //custom functions

int main(int argc, char* argv[])
{
	//determine n
	int tableWidth = setN(argc, argv);

	//read input
	char toEncrypt[BUFSIZ];
	readFromStdIn(toEncrypt);

	//strip whitespace
	char stripped[strlen(toEncrypt)];
	stripWhitespace(toEncrypt, stripped);

	//pad to multiple of n
	char padded[strlen(stripped) + tableWidth];
	padToMultOfN(stripped, padded, tableWidth);

	//perform encryption
	char encrypted[strlen(padded)];
	tableEncrypt(padded, encrypted, tableWidth);

	//print result to stdout, followed by newline
	printf("%s\n", encrypted);

	return 0;
} // main