////////////////////////////////////////////////////////////////////////////////
// S.Donchez
// ECE 8473-DL1
// villcoin.c - VillCoin Mining 
//  Similar to bitcoin, villcoin is Villanova's digital cryptocurrency, which 
// can be cashed in for points on a course assignment. To achieve maximum points
// on this assignment you must mine a villcoin such that the first four bytes of
// the hash are zero.
// Write a C program using SHA1() to create a villcoin with n leading zero 
// bytes, where n is an optional command - line argument, with default n=1.
// A villcoin consists of a data string and a hash. The hash is SHA1(data) in 
// hex.The data string is a concatenation of your userid, a 32-bit random 
// value from rand(), and a 32-bit nonce. The random value is set just once at
// the beginning of main().
// Mining consists of finding a nonce so that the first n bytes of the resulting
// hash are zero. Start with nonce=0 and keep incrementing until a proper hash 
// is found; if the nonce wraps around back to 0 without success, print an error
// message and exit.
// The exact format of the data stringand program output is up to you, but the 
// program output should not be excessive(don't show all 4 billion possible 
// hashes) and the final output must show the data string and hash so that the 
// result can be confirmed using openssl sha1 or sha1sum.
// To collect your villcoin assignment points, include the program output in a 
// file submitted with the source code.
////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <openssl/sha.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#define USERID "sdonchez"

int parseN(int argc, char* argv[]);

void genHash(const char* constant, uint32_t nonce, unsigned char* output);

bool isValidCoin(unsigned int n, const unsigned char* hash);

void printHashLine(const char* userId, const char* rand, uint32_t nonce,
	const unsigned char* hash);


int main(int argc, char* argv[])
{
	//generate random value and convert to hex string
	srand(time(0));
	uint32_t randVal = rand();
	char randHex[100];
	sprintf(randHex, "%08x", randVal);

	//piece together constant part of data string
	char* userId = USERID;
	char constant[100];
	strcat(constant, userId);
	strcat(constant, "|");
	strcat(constant, randHex);
	strcat(constant, "|");

	//parse and init n
	int n = parseN(argc, argv);
	if (n < 1)
	{
		return -1;
	} // if

	//init nonce
	uint32_t nonce = 0;

	// print constant conditions
	printf("n = %i, rand = %x\n", n, randVal);

	unsigned char hash[SHA_DIGEST_LENGTH];

	do //while (!isValidCoin(n, hash) && nonce);
	{
		genHash(constant, nonce, hash);
		if (nonce < 5)
		{
			printHashLine(userId, randHex, nonce, hash);
		} // if
		else if (nonce == 5)
		{
			printf("...\n");
		} // else if
		nonce++;
	} while (!isValidCoin(n, hash) && nonce);

	//print result unless we already did so
	if (nonce > 5)
	{
		//nonce - 1 since we've already incremented it
		printHashLine(userId, randHex, nonce - 1, hash);
	} //if
	if (!nonce)
	{
		fprintf(stderr, "Failed to find a valid VillCoin with the given n \n");
		return -2;
	} //if

	return 0;
}

/*******************************************************************************
 * @brief parses the value of N passed as a parameter, if it exists.
 * @param argc - number of arguments in executable call.
 * @param argv - text of executable arguments.
 * @return value of n passed in, provided it's valid.
 *         -1 if an invalid input is provided.
 *          1 if no input is provided.
 ******************************************************************************/
int parseN(int argc, char* argv[])
{
	unsigned int retval = 0;
	if (argc < 2)
	{
		retval =  1; //default case
	} // if
	else
	{
		retval = atoi(argv[1]);
	} // else
	
	//less than one means every hash matches (or undefined behavior for <0)
	//greater than SHA_DIGEST_LENGTH means nothing will ever match.
	if ((retval < 1) || (retval > SHA_DIGEST_LENGTH))
	{
		fprintf(stderr, "Invalid value of n provided. Value must be between 1 "
			"and 31. Received %i\n", retval);
		retval = -1;
	} // if
	return retval;
} // parseN

/*******************************************************************************
 * @brief generates a hash value based on the default data (userId and random
 *        value), as well as the nonce value.
 * @param constant - the concatenated userId and random value, both with "|"
 *                   appended.
 * @param nonce    - the incrementing nonce value for the current iteration.
 * @param output   - the string to store the hash into.
 ******************************************************************************/
void genHash(const char* constant, uint32_t nonce, unsigned char* output)
{
	//convert nonce to string
	char nonceStr[9];
	sprintf(nonceStr, "%08x", nonce);
	nonceStr[8] = '\0';

	//combine nonce with constant value
	char data[strlen(constant) + strlen(nonceStr) + 1];
	data[0] = '\0';
	strcat(data, constant);
	strcat(data, nonceStr);

	//perform hash
	SHA1((unsigned char*) data, strlen(data), output);
}

/*******************************************************************************
 * @brief checks to determine if a given hash meets the requirements to be a
 *        valid VillCoin (has a set of n leading bytes equal to 0.
 * @param n    - number of bytes required to be 0.
 * @param hash - hash to validate.
 * @return true if a valid VillCoin hash.
 *         false otherwise.
 ******************************************************************************/
bool isValidCoin(unsigned int n, const unsigned char* hash)
{
	//convert hash to friendly string
	char hashStr[2 * SHA_DIGEST_LENGTH] = "";
	char tempStr[3] = "";
	for (int i = 0; i < SHA_DIGEST_LENGTH; ++i)
	{
		sprintf(tempStr, "%02x", hash[i]);
		strcat(hashStr, tempStr);
	} // for

	//init prefix to match (leading 0s)
	char prefix[n + 1];
	for (int i = 0; i < 2 * n; i++)
	{
		prefix[i] = '0';
	} // for
	prefix[2 * n] = '\0';

	//perform match check
	return (!strncmp(hashStr, prefix, 2 * n));
} // isValidCoin

/**
 * @brief prints a nicely formatted line indicating the inputs to the hashing
 *        function and its resulting hash output.
 * @param userId - userId used in hash.
 * @param rand   - constant "random" value used in hash.
 * @param nonce  - current nonce value.
 * @param hash   - hash output.
*/
void printHashLine(const char* userId, const char* rand, uint32_t nonce,
	const unsigned char* hash)
{
	//print input data
	printf("%s|%s|%08x ", userId, rand, nonce);

	//print hash one byte at a time
	for (int i = 0; i < SHA_DIGEST_LENGTH; ++i)
	{
		printf(" %02x", hash[i]);
	}
	printf("\n");
} // printHashLine