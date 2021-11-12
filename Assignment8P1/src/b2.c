////////////////////////////////////////////////////////////////////////////////
// S.Donchez
// ECE 8473-DL1
// b2.c - simulation using two classical bits
// Write a C program using an array of two integers to simulate computations on
// two classical bits.
// Implement the following two functions :
// void X(int b[], int k) - NOT on bit k
// void CX(int b[], int c, int k) - controlled-NOT on bit k controlled by bit c
// The controlled - NOT performs a NOT on bit k only if bit c is 1.
// Assume that c, k are elements of { 0,1 }and c != k. Error checking is not 
// required.
// In the main program, perform an exhaustive test using all possible 
// combinations of bit values and function calls.For each function call, perform 
// the operation twice; the output should show that the second call undoes the 
// first since these functions are their own inverses.
// The program does not have to check the results, just display the results.
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>

void X(int b[], int k);

void CX(int b[], int c, int k);

void exhaustiveTestBits(int b[], int numEls);

void printArray(int b[], int numEls, char* functionName);

int main()
{

	//init b to [ 0, 0 ]
	int b[2] = { 0, 0 };
	exhaustiveTestBits(b, 2);

	//update b to [ 0, 1 ]
	b[0] = 1;
	exhaustiveTestBits(b, 2);

	//update b to [ 1, 1 ]
	b[1] = 1;
	exhaustiveTestBits(b, 2);

	//update b to [ 1, 0 ]
	b[0] = 0;
	exhaustiveTestBits(b, 2);

} // main

/*******************************************************************************
 * @brief performs a NOT operation on a given classical bit
 * @param b - array of classical bits
 * @param k - index of bit to be operated on in b
 ******************************************************************************/
void X(int b[], int k)
{
	b[k] = !b[k];
} // X

/*******************************************************************************
 * @brief performs a controlled NOT on a given classical bit, provided a control
 * bit is set to 1. Note that it is assumed that c!= k.
 * @param b - array of classical bits
 * @param c - index of control bit in b (contents must be 1 for NOT to occur)
 * @param k - index of bit to be operated on in b
 ******************************************************************************/
void CX(int b[], int c, int k)
{
	if (b[c])
	{
		b[k] = !b[k];
	} // if
} // CX

/*******************************************************************************
 * @brief performs an exhaustive test of both X and CX for a given set of values
 * contained in b. Performs each operation on each bit twice, to demonstrate
 * that they are self-inverses.
 * @param b - array of classical bits to be operated on
 * @param numEls - number of elements in b (required for printArray function).
 ******************************************************************************/
void exhaustiveTestBits(int b[], int numEls)
{
	printArray(b, numEls, "b");

	//Test X on bit 0
	X(b, 0);
	printArray(b, numEls, "X(b,0)");

	X(b, 0);
	printArray(b, numEls, "X(b,0)");

	//Test X on bit 1
	X(b, 1);
	printArray(b, numEls, "X(b,1)");

	X(b, 1);
	printArray(b, numEls, "X(b,1)");

	//Test CX on bit 1, controlled by bit 0
	CX(b, 0, 1);
	printArray(b, numEls, "CX(b,0,1)");

	CX(b, 0, 1);
	printArray(b, numEls, "CX(b,0,1)");

	//Test CX on bit 0, controlled by bit 1
	CX(b, 1, 0);
	printArray(b, numEls, "CX(b,1,0)");

	CX(b, 1, 0);
	printArray(b, numEls, "CX(b,1,0)");
} //exhaustiveTestBits

/*******************************************************************************
 * @brief prints a nicely formatted representation of the array of classical
 * bits to show the changes that result from each function call
 * @param b - the array of classical bits
 * @param numEls - the number of elements in the array
 * @param functionName - the name of the function that last operated on b
 ******************************************************************************/
void printArray(int b[], int numEls, char * functionName)
{
	// print function name and opening brace
	printf("%s: { ", functionName);
	for (int i = 0; i < numEls - 1; i++)
	{
		// print first/middle values
		printf("%i, ", b[i]);
	} // for

	// print end of string
	printf("%i }\n", b[numEls -1]);
} // printArray