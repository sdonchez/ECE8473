////////////////////////////////////////////////////////////////////////////////
// S.Donchez
// rand.h - Declarations of common functions for parts 1 and 2 of Assignment 6
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string.h> //for strcpy, etc.
#include <ctype.h> //for isspace, isdigit
#include <stdio.h> //for printf, BUFSIZ
#include <stdlib.h> //for atoi

/*******************************************************************************
 * setN -	determines the value of N based on the input, or applies the default
 *			if no input is given.
 * @param  int   argc     - the number of arguments passed to the function.
 * @param  char* argv[] - the array of arguments passed to the function.
 * @returns int value of n.
 ******************************************************************************/
int setN(int argc, char* argv[]);

/*******************************************************************************
 * readFromStdin -  reads from stdin and appends each line to the destination
 *					until EOF is reached
 * @param char* dest - the destination to return the input to.
 * @returns none
 ******************************************************************************/
void readFromStdIn(char* dest);

/*******************************************************************************
 * stripWhitespace - removes all whitespace (including newline) characters.
 * @param const char* untrimmed - the original string to be stripped of all
 *		whitespace characters.
 * @param       char* trimmed   - the stripped result of the operation.
 * @returns none
 ******************************************************************************/
void stripWhitespace(const char* untrimmed, char* trimmed);

/*******************************************************************************
 * padToMultOfN   - pads the input string to be m*n characters long, where m is
 *					any positive integer.
 * @param const char* unpadded - the original string to be padded.
 * @param       char* padded  - the padded result of the operation.
 * @returns none
 ******************************************************************************/
void padToMultOfN(const char* unpadded, char* padded, int n);

/*******************************************************************************
 * tableEncrypt - performs the table encryption operation on the given input.
 * @param const char* unencrypted - the original string to be encrypted.
 * @param       char* encrypted   - the encrypted result of the operation.
 * @returns none
 ******************************************************************************/
void tableEncrypt(const char* unencrypted, char* encrypted, int n);

/*******************************************************************************
 * tableDecrypt - performs the table decryption operation on the given input.
 * @param const char* encrypted - the original string to be decrypted.
 * @param       char* trimmed   - the decrypted result of the operation.
 * @returns none
 ******************************************************************************/
void tableDecrypt(const char* encrypted, char* decrypted, int n);
