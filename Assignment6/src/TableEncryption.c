////////////////////////////////////////////////////////////////////////////////
// S.Donchez
// rand.h - Implementation of common functions for parts 1 and 2 of Assignment 6
////////////////////////////////////////////////////////////////////////////////

#include "TableEncryption.h"

/*******************************************************************************
 * setN -	determines the value of N based on the input, or applies the default
 *			if no input is given.
 * @param  int   argc     - the number of arguments passed to the function.
 * @param  char* argv[] - the array of arguments passed to the function.
 * @returns int value of n.
 ******************************************************************************/
int setN(int argc, char* argv[])
{
	int tableWidth;
	//check if there's a value specified for n. If so, make sure it is valid.
	if (argc == 2)
	{
		if (!isdigit(*argv[1]))
		{
			fprintf(stderr, 
				"Invalid value for n. Expected positive number, received %s",
				argv[1]);
			return -1;
		} // if
		tableWidth = atoi(argv[1]);
	}// if

	//otherwise fall back to default
	else
	{
		tableWidth = 5;
	} // else

	return tableWidth;
} //setN

/*******************************************************************************
 * readFromStdin -  reads from stdin and appends each line to the destination
 *					until EOF is reached
 * @param char* dest - the destination to return the input to.
 * @returns none
 ******************************************************************************/
void readFromStdIn(char* dest)
{
	char input[BUFSIZ];

	//until EOF, read a line into the input buffer
	while (fgets(input, BUFSIZ, stdin))
	{
		//append the new line to the destination
		strcat(dest, input);
	} // while

} // readFromStdIn

/*******************************************************************************
 * stripWhitespace - removes all whitespace (including newline) characters.
 * @param const char* untrimmed - the original string to be stripped of all
 *		whitespace characters.
 * @param       char* trimmed   - the stripped result of the operation.
 * @returns none
 ******************************************************************************/
void stripWhitespace(const char* untrimmed, char* trimmed)
{
	char* trimmedItr;
	trimmedItr = trimmed;

	//iterate through the source string, and add each nonwhitespace character to
	//the destination string
	for (int i = 0; i < strlen(untrimmed); i++)
	{
		if (!isspace(untrimmed[i]))
		{
			*trimmedItr = untrimmed[i];
			trimmedItr++;
		} // if
	} // for

	*trimmedItr = '\0';

	return;
} //stripWhitespace

/*******************************************************************************
 * padToMultOfN   - pads the input string to be m*n characters long, where m is
 *					any positive integer.
 * @param const char* unpadded - the original string to be padded.
 * @param       char* padded  - the padded result of the operation.
 * @returns none
 ******************************************************************************/
void padToMultOfN(const char* unpadded, char* padded, int n)
{
	int unpaddedLen = strlen(unpadded);

	//find out how many characters exist beyond (m-1)*n
	int extra = unpaddedLen % n;

	//start out with the original string
	strcpy(padded, unpadded);

	//pad as necessary
	if (extra)
	{
		int paddedLen = unpaddedLen;

		//add (n - extra) 'o' characters such that paddedLen = m*n
		for (; paddedLen < unpaddedLen + (n - extra); paddedLen++)
		{
			padded[paddedLen] = 'o';
		} // for
		padded[paddedLen] = '\0';
	} // if

	return;
} //padToMultOfN

/*******************************************************************************
 * tableEncrypt - performs the table encryption operation on the given input.
 * @param const char* unencrypted - the original string to be encrypted.
 * @param       char* encrypted   - the encrypted result of the operation.
 * @returns none
 ******************************************************************************/
void tableEncrypt(const char* unencrypted, char* encrypted, int n)
{

	//temp variable to iterate through destination
	char* encryptedItr;
	encryptedItr = encrypted;

	//total times to loop through input: n times
	for (int i = 0; i < n; i++)
	{
		//number of characters to pick out on each loop: (length of input / n)
		for (int j = 0; j < (strlen(unencrypted) / n); j++)
		{
			//grab corresponding character from each row of table
			*encryptedItr = unencrypted[i + (j * n)];
			encryptedItr++;
		} // for
	} // for
	*encryptedItr = '\0';

	return;
} // tableEncrypt

/*******************************************************************************
 * tableDecrypt - performs the table decryption operation on the given input.
 * @param const char* encrypted - the original string to be decrypted.
 * @param       char* trimmed   - the decrypted result of the operation.
 * @returns none
 ******************************************************************************/
void tableDecrypt(const char* encrypted, char* decrypted, int n)
{
	//temp variable to iterate through destination

	char* decryptedItr;
	decryptedItr = decrypted;

	//decrypt is inverse of encrypt, need to loop (length of input / n) times
	int decryptMult = strlen(encrypted) / n;
	for (int i = 0; i < decryptMult; i++)
	{
		// pick n characters per loop
		for (int j = 0; j < n; j++)
		{
			//grab corresponding character from each column of table
			*decryptedItr = encrypted[i + (j * decryptMult)];
			decryptedItr++;
		} // for
	} // for
	*decryptedItr = '\0';

	return;
} //tableDecrypt