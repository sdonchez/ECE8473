////////////////////////////////////////////////////////////////////////////////
// S.Donchez
// ECE 8473-DL1
// q2.c - simulation using two quantum bits
// Write a C program using an array of four doubles to simulate computations on 
// two quantum bits.
// Implement the following four functions :
// void X(double a[], int k) // NOT on qubit k
// void CX(double a[], int c, int k) // controlled-NOT on qubit k controlled by 
// qubit c
// void Z(double a[], int k) // phase-flip on qubit k
// void H(double a[], int k) // Hadamard on qubit k
// Assume that c, k are elements of { 0,1 }and c != k.Error checking is not 
// required.
// In the main program, first initialize the amplitudes to distinct values, e.g.
// double s30 = 1 / sqrt(30), a[4] = { 1 * s30, 2 * s30, 3 * s30, 4 * s30 };
// then test using all possible function calls.For each function call, perform 
// the operation twice; the output should show that the second call undoes the 
// first since these functions are their own inverses.
// The program does not have to check the results, just display the results.
// Then the main program must reset the amplitudes to{ 1, 0, 0, 0 }and perform a
// superdense coding simulation.The value to be encoded(default = 0) comes from 
// the command-line argv[1] if present.Show the intermediate state amplitude 
// values after each operation.
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h> // for printf, fprintf
#include <math.h> // for pow, sqrt 
#include <stdlib.h> // for atoi, rand, srand
#include <time.h> // for time() (srand seed)

//From man regex(3)
#define ARRAY_SIZE(arr) (sizeof((arr)) / sizeof((arr)[0]))

void X(double a[], int k); // NOT on qubit k

void CX(double a[], int c, int k); // controlled NOT on qubit k, controlled by c

void H(double a[], int k); // Hadamard on qubit k

void Z(double a[], int k); // phase-flip on qubit k

void exhaustiveTestQubits(double a[], int numEls);

void superdense_coding(double a[], int toEncode);

void printArray(double b[], int numEls, char* functionName);

void elementSwap(double a[], int i, int j);

int parseEncodingValue(int argc, char* argv[]);

size_t measure(double a[], size_t numQubits);

void collapseQubits(double a[], size_t numQubits, size_t collapseToState);

// generated to allow flexibility in number of qubits, while conforming to 
// function prototypes in assignment
size_t numEls;

//value for superdense coding simulation
int toEncode = -1;

int main(int argc, char* argv[])
{
	//init array for exhaustive test
	double s30 = 1 / sqrt(30);
	double a[4] = { 1*s30, 2*s30, 3*s30, 4*s30};

	//see comment above
	numEls = ARRAY_SIZE(a);

	//perform exhaustive test of all operations
	exhaustiveTestQubits(a, 2);

	//get value to encode
	int retval = parseEncodingValue(argc, argv);
	if (retval < 0) return retval;

	//run superdense coding simulation
	superdense_coding(a, toEncode);

	return 0;
} // main

/*******************************************************************************
 * @brief performs a NOT operation on a given qubit.
 * @param a - array representing several qubits.
 * @param k - qubit to be operated on in a.
 ******************************************************************************/
void X(double a[], int k)
{
	size_t currEl = 0;
	//iterate through array n/2 times, swapping each appropriate pair of values
	for (size_t i = 0; i < (numEls >> 1); i++)
	{
		elementSwap(a, currEl, currEl + (1 << k));
		//we need to select 2^k consecutive elements, then skip 2^k elements
		//(their matches), and repeat

		//if we haven't just operated on 2^k consecutive elements, keep going
		if ((currEl + 1) % (1 << k))
		{
			currEl++;
		} // if

		//otherwise, skip the next 2^k elements, plus the other half of the
		//pair just swapped
		else
		{
			currEl += (1 << k) + 1;
		} // else
	}
} // X

/*******************************************************************************
 * @brief performs a controlled NOT on a given qubit, provided a control
 * qubit is set to 1. Note that it is assumed that c!= k.
 * @param a - array representing several qubits.
 * @param c - control qubit in a (contents must be 1 for NOT to occur).
 * @param k - qubit to be operated on in a .
 ******************************************************************************/
void CX(double a[], int c, int k)
{

	//effectively do the same as X above, but only actually do the swap if bit
	//c is set. Still increment the loop correctly.
	size_t currEl = 0;
	for (size_t i = 0; i < (numEls >> 1); i++)
	{
		//if the c'th bit of i is non-zero, that means bit c is set for a[i]
		//and the flip should ocurr
		if (currEl & (1 << c))
		{
			elementSwap(a, currEl, currEl + (1 << k));
		}

		//we need to select 2^k consecutive elements, then skip 2^k elements
		//(their matches), and repeat

		//if we haven't just operated on 2^k consecutive elements, keep going
		if ((currEl + 1) % (1 << k))
		{
			currEl++;
		} // if

		//otherwise, skip the next 2^k elements, plus the other half of the
		//pair just swapped
		else
		{
			currEl += (1 << k) + 1;
		} // else
	}
} // CX

/*******************************************************************************
 * @brief performs a Hadamard operation on the given qubit.
 * @param a - array representing several qubits.
 * @param k - qubit to operate on.
 * @note as far as the author can tell, the general pattern for performing a
 *       Hadamard operation is as follows:
 *       For a given index in the array, the new value is equal to the old value
 *       (inverted if the kth bit of the index is 1), plus the (unmodified) 
 *		 value of the element in position (i +/- 2^k), where the operator is
 *       similarly determined by the value of the kth bit of the index.
 ******************************************************************************/
void H(double a[], int k)
{
	//normalization factor to ensure that the sum of the probabilities remains
	//1. Also crucial to the function's ability to be a self-inverse.
	double normFactor = 1 / sqrt(2);

	//init a temp array since we will need old values
	double t[numEls];

	//create temp copies of elements
	for (size_t i = 0; i < numEls; i++)
	{
		t[i] = a[i];
	}

	//iterate through array, setting values per description above.
	for (size_t i = 0; i < numEls; i++)
	{
		if (i & (1<<k))
		{
			a[i] = normFactor * (-t[i] + t[i-(1<<k)]);
		} // if
		else
		{
			a[i] = normFactor * (t[i] + t[i + (1 << k)]);
		} // else
	} // for

#ifdef _DEBUG
	//check that the resultant sum of probabilities is still 1
	double check = 0.0;
	for (int i = 0; i < numEls; i++) check += pow(a[i], 2);
	printf("checkVal: %g\n", check);
#endif
} // H

/*******************************************************************************
 * @brief performs a phase flip (inverts) a given qubit.
 * @param a - array representing several qubits.
 * @param k - qubit to operate on in a.
 ******************************************************************************/
void Z(double a[], int k)
{
	for (size_t i = 0; i < numEls; i++)
	{
		//perform phase flip on all cases where bit k is set
		if (i & (1 << k))
		{
			a[i] = -a[i];
		} // if
	} // for
} // Z

/*******************************************************************************
 * @brief performs an exhaustive test of both X and CX for a given set of 
 * probabilities contained in a. Performs each operation on each bit twice, to 
 * demonstrate that they are self-inverses.
 * @param a - array representing several qubits
 * @param numQubits - number of qubits represented in a. (required for 
 *                    printArray function).
 ******************************************************************************/
void exhaustiveTestQubits(double a[], int numQubits)
{
	printf("Starting Exhaustive Tests:\n");
	printArray(a, numQubits, "a");

	//Test X on qubit 0
	X(a, 0);
	printArray(a, numQubits, "X(a,0)");

	X(a, 0);
	printArray(a, numQubits, "X(a,0)");

	//Test X on qubit 1
	X(a, 1);
	printArray(a, numQubits, "X(a,1)");

	X(a, 1);
	printArray(a, numQubits, "X(a,1)");

	//Test CX on qubit 1, controlled by bit 0
	CX(a, 0, 1);
	printArray(a, numQubits, "CX(a,0,1)");

	CX(a, 0, 1);
	printArray(a, numQubits, "CX(a,0,1)");

	//Test CX on qubit 0, controlled by bit 1
	CX(a, 1, 0);
	printArray(a, numQubits, "CX(a,1,0)");

	CX(a, 1, 0);
	printArray(a, numQubits, "CX(a,1,0)");

	//Test H on qubit 0
	H(a, 0);
	printArray(a, numQubits, "H(a,0)");

	H(a, 0);
	printArray(a, numQubits, "H(a,0)");

	//Test H on qubit 1
	H(a, 1);
	printArray(a, numQubits, "H(a,1)");

	H(a, 1);
	printArray(a, numQubits, "H(a,1)");

	//Test Z on qubit 0
	Z(a, 0);
	printArray(a, numQubits, "Z(a,0)");

	Z(a, 0);
	printArray(a, numQubits, "Z(a,0)");

	//Test Z on qubit 1
	Z(a, 1);
	printArray(a, numQubits, "Z(a,1)");

	Z(a, 1);
	printArray(a, numQubits, "Z(a,1)");
} // exhaustiveTestQubits

/*******************************************************************************
 * @brief performs a superdense coding simulation per the assignment
 * instructions.
 * @param a        - array representing 2 qubits.
 * @param toEncode - value to encode into qubit for transmission.
 * @link http://fog.misty.com/perry/qc/SDC/notes.html (n=2)
 ******************************************************************************/
void superdense_coding(double a[], int toEncode)
{
	printf("\nStarting Superdense Coding Simulation:\n");
	//init to state 00 (a[0] = 1)
	a[1] = a[2] = a[3] = 0;
	a[0] = 1;
	printArray(a, 2, "a");

	//entanglement
	H(a, 1);
	printArray(a, 2, "H(a,1)");

	CX(a, 1, 0);
	printArray(a, 2, "CX(a,1,0)");

	//seperation

	printf("\nQubits Separated\n");

	//encoding
	printf("Alice: Input = %i\n", toEncode);

	switch (toEncode)
	{
	case 0:
		printArray(a, 2, "I");
		break;
	case 1:
		X(a, 1);
		printArray(a, 2, "X");
		break;
	case 2:
		Z(a, 1);
		printArray(a, 2, "Z");
		break;
	case 3:
		X(a, 1);
		Z(a, 1);
		printArray(a, 2, "Z*X");
	}

	//reunification
	printf("\nQubits Reunited\n");

	//decoding

	CX(a, 1, 0);
	printArray(a, 2, "CX(a,1,0)");
	
	H(a, 1);
	printArray(a, 2, "H(a,1)");

	//measurement
	printf("Bob: decoded result: %zi\n", measure(a, 2));
} // superdense_coding

/*******************************************************************************
 * @brief prints a nicely formatted representation of the array representative
 * of several qubits to show the changes that result from each function call.
 * @param b            - the array representing several qubits.
 * @param numQubits    - the number of qubits represented in the array.
 * @param functionName - the name of the function that last operated on a.
 ******************************************************************************/
void printArray(double a[], int numQubits, char* functionName)
{
	//print function name and opening brace
	printf("%s: { ", functionName);
	for (int i = 0; i < (1 << numQubits) - 1; i++)
	{
		//print first/middle values
		printf("%g, ", a[i]);
	} // for

	//print end of string
	printf("%g }\n", a[(1 << numQubits) - 1]);
} // printArray

/*******************************************************************************
 * @brief swaps two elements in an array.
 * @param a - array containing elements to swap.
 * @param i - element to be swapped
 * @param j - second element to be swapped
 ******************************************************************************/
void elementSwap(double a[], int i, int j)
{
	double t = a[i];
	a[i] = a[j];
	a[j] = t;
} //qBitSwap

/*******************************************************************************
 * @brief performs error checking and parsing on the value to be encoded as part
 *        of the superdense_coding simulation
 * @param argc - number of arguments to parse (from main)
 * @param argv - contents of arguments
 * @return int - 0 if successful
 *               -1 if too few arguments are passed
 *               -2 if too many arguments are passed
 *               -3 if the argument is out of range
 ******************************************************************************/
int parseEncodingValue(int argc, char* argv[])
{

	//if no value passed, set to 0
	if (argc < 2)
	{
		toEncode = 0;
	} // if

	//too many arguments
	else if (argc > 2)
	{
		fprintf(stderr, "Error: too many arguments for superdense coding "
			"simulation. The program will now exit!\n");
		return (-2);
	} // else if

	else toEncode = atoi(argv[1]);

	//range check
	if ((toEncode < 0) || (toEncode > 3))
	{
		fprintf(stderr, "Error: invalid value passed for superdense coding\n"
			"Value must be between 0 and 3! Program will now exit!\n");
		return (-3);
	} // if

	return 0;
} // parseEncodingValue

/*******************************************************************************
 * @brief performs a measurement of several qubits, effectively collapsing them
 *        into classical bits with values representative of the probability
 *        of each state at the time they are measured.
 * @param a         - an array representing several qubits.
 * @param numQubits - the number of qubits represented by a.
 * @return            one of the possible values of the qubits, with a
 *                    distribution proportional to their respective
 *                    probabilities.
 ******************************************************************************/
size_t measure(double a[], size_t numQubits)
{
	// compute number of elements in array
	numEls = pow(2, numQubits);

	//seed PRNG
	srand(time(0));

	//obtain random value such that 0 <= N < 1
	double randProb = rand() / (RAND_MAX + 1.0);

	//init running sum of probabilites.
	double sumProbs = 0.0;

	//iterate through probabilities
	for (size_t i = 0; i < numEls; i++)
	{
		//running sum of probabilities effectively assigns each state to a range
		//of random values sized according to its own value.
		sumProbs += pow(fabs(a[i]), 2);

		//if the value is in the range of the current index
		if (randProb < sumProbs)
		{
			// collapse array to simulate actual effect of measurment
			collapseQubits(a, numQubits, i);

			//return index value
			return i;
		} // if
	}
	// for

	//error handling
	fprintf(stderr, "Array is not normallized! aborting measurement!\n");
	return -1;
} // measure

/*******************************************************************************
 * @brief collapses a set of probabilities (an array representative of several
 *        qubits) into a given state, such as is achieved as a consequence of
 *        mesaurement.
 * @param a               - array representative of several qubits.
 * @param numQubits       - number of qubits represented in a.
 * @param collapseToState - state to collapse the qubits to (the state that will
 *                          be measured as "1").
 ******************************************************************************/
void collapseQubits(double a[], size_t numQubits, size_t collapseToState)
{
	// compute number of elements in array
	numEls = pow(2, numQubits);

	for (int i = 0; i < numEls; i++)
	{
		//state collapseToState = 1; all others = 0
		a[i] = (i == collapseToState) ? 1 : 0;
	} // for
} // collapseQubits