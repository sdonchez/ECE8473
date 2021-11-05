////////////////////////////////////////////////////////////////////////////////
// Stephen Donchez
// p2.c - table decrypt
//  Write a C program to implement table decryption. The program usage is:
// ./ p2[n] < ciphertext > plaintext
// where n is the table row length, default = 5.
// 
// The program must read all of standard input into a character array, and 
// remove all whitespace from the input.Then print the plaintext followed by a 
// single newline to standard output.
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h> //for printf, BUFSIZ
#include "TableEncryption.h" //custom functions
#include <string.h> //for strlen

int main(int argc, char* argv[])
{
	//determine n
	int tableWidth = setN(argc, argv);

	//read input
	char toDecrypt[BUFSIZ];
	readFromStdIn(toDecrypt);

	//check if message length is a multiple of n, if not then abort
	if ((strlen(toDecrypt) - 1) % tableWidth)
	{
		fprintf(stderr, "Error: String length is not a multiple of n.\n");
		return 2;
	}

	//strip whitespace
	char stripped[strlen(toDecrypt)];
	stripWhitespace(toDecrypt, stripped);

	//decrypt message
	char decrypted[strlen(stripped)];
	tableDecrypt(stripped, decrypted, tableWidth);

	//print result to stdout, followed by newline
	printf("%s\n", decrypted);

	return 0;
} // main