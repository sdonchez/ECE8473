////////////////////////////////////////////////////////////////////////////////
// S.Donchez
// ECE 8473-DL1
// villcoin.c - VillCoin Mining (Threaded)
// Start with a copy of your villcoin mining program from the previous 
// assignment, and modify it to perform the hash search in parallel using 
// multiple threads. With 4 threads this should speedup the runtime by about a 
// factor of 4 on systems having at least 4 cores.
// Each thread must search a different subset of the nonce space. Once any 
// thread finds a proper hash the program must stop all threads and exit. If no 
// thread finds a proper hash, print an error message and exit.
// See the notes on POSIX Threads.The recommended prototype is pthread_pipe.c 
// with modifications to wait for any one thread success or all failed.
// To collect your villcoin points for this assignment, include the program 
//  output in a file submitted with the source code showing results where the 
// first four bytes of the hash are zero.
// 
// (From Assignment 9)
// Similar to bitcoin, villcoin is Villanova's digital cryptocurrency, which 
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
#include <pthread.h>
#include <unistd.h>

#define USERID "sdonchez"
#define NUMTHREADS 4

/**
 * @brief set of parameters passed to each instantiation of searchForMatch.
 * @param start    - the starting value for the thread to search from.
 * @param size     - the number of values to search.
 * @param constant - the constant portion of the input string (userId and rand
 *                   value).
 * @param hash     - the string to store the hash into
 * @param n        - the number of initial zero bytes
 * @param threadNo - the index of the thread (used for printouts)
 * @see searchForMatch
*/
struct threadParams {
	unsigned int start;
	unsigned int size;
	char* constant;
	unsigned char* hash;
	int n;
	int threadNo;
}; //struct threadParams

int parseN(int argc, char* argv[]);

void genHash(const char* constant, uint32_t nonce, unsigned char* output);

bool isValidCoin(unsigned int n, const unsigned char* hash);

void printHashLine(const char* constant, uint32_t nonce,
	const unsigned char* hash);

void* searchForMatch(void* tPs);

bool found = false;

int main(int argc, char* argv[])
{
	//Threading Setup
	
	// to avoid stdio buffering on the pipe, must make stdout unbuffered
	// or do fflush(stdout) after every printf()
	setbuf(stdout, 0); // make stdout unbuffered

	// redirect stdin and stdout through pipe
	int fd[2]; if (pipe(fd)) { perror("pipe"); return 1; }

	dup2(fd[0], 0); dup2(fd[1], 1); close(fd[0]); close(fd[1]);

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

	// print constant conditions
	printf("n = %i, rand = %x\n", n, randVal);

	//init hash location for each thread
	unsigned char hash[NUMTHREADS][SHA_DIGEST_LENGTH];

	//init thread structure
	struct threadParams tPs[NUMTHREADS];

	// start the threads
 	pthread_t t[NUMTHREADS];
	unsigned int size = (UINT32_MAX + 1UL)/ NUMTHREADS;

	for (int i = 0; i < NUMTHREADS; i++)
	{
		tPs[i].constant = constant;
		tPs[i].n = n;
		tPs[i].size = size;
		tPs[i].start = i * size;
		tPs[i].threadNo = i;
		tPs[i].hash = hash[i];
		if (pthread_create(&t[i], 0, searchForMatch, (void*)&tPs[i]))
		{
			perror("pthread_create");
			return 1;
		} // if
	} // for

	// wait until any one thread is finished
	//
	char msg[BUFSIZ];

	while (fgets(msg, BUFSIZ, stdin))
	{
		fputs(msg, stderr); // copy thread messages to stderr

		if (strstr(msg, "success") || strstr(msg, "No results found"))
		{
			break;
		} // if
	} // while

	// stop all threads
	for (int i = 0; i < NUMTHREADS; ++i) pthread_cancel(t[i]);
	if (!found)
	{
		fprintf(stderr, "Failed to find a valid VillCoin! \n");
		return -2;
	} // if

	return 0;
} // main

/**
 * @brief searches for hashes matching the given number of leading zero bytes
 *        in a given nonce space
 * @param tPs threadParams structure containing all of the inputs needed for the
 *        search operation
 * @return 0
 * @see struct threadParams
*/
void* searchForMatch(void* tPs)
{
	struct threadParams params = *(struct threadParams*)tPs;
	printf("f %i: start = 0x%08x, size = 0x%08x\n", params.threadNo, params.start,
		params.size);
	//init nonce
	uint32_t nonce = params.start;
	do //while (!isValidCoin(n, hash) && nonce != start + size);
	{
		genHash(params.constant, nonce, params.hash);
		nonce++;
	} while (!isValidCoin(params.n, params.hash) && 
		nonce != (params.start + params.size)); // do

	//check if valid match or just end of space
	if (nonce != (params.start + params.size))
	{
		printf("f %i: success! ", params.threadNo);
		printHashLine(params.constant, nonce - 1, params.hash);

		found = true;
	} // if
	else
	{
		printf("f %i: No results found in space %x - %x\n", params.threadNo, 
			params.start, params.start + params.size);
	} //else


	return 0;
} // searchForMatch

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
 * @param constant - the unchanging portion of the hahsh input (userId, static
 *                   rand value).
 * @param nonce    - current nonce value.
 * @param hash     - hash output.
*/
void printHashLine(const char* constant, uint32_t nonce,
	const unsigned char* hash)
{
	//print input data
	printf("%s%08x ", constant, nonce);

	//print hash one byte at a time
	for (int i = 0; i < SHA_DIGEST_LENGTH; ++i)
	{
		printf(" %02x", hash[i]);
	}
	printf("\n");
} // printHashLine