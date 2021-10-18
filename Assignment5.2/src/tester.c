////////////////////////////////////////////////////////////////////////////////
// Stephen Donchez
// tester.c - Tests the implementation of an additional set of non-standard 
// string functions.
// 
// Write a main program which performs one non-trivial test for each of the 
// string functions above, checks the result and return value, and indicates 
// whether the function passed or failed the test.
////////////////////////////////////////////////////////////////////////////////
#include "strfxns.h" //Custom header for these functions
#include <stdio.h>

/*******************************************************************************
 * checkResult - compares the expected output and return value to the expected
 *				 values to determine if the test passes or fails.
 ******************************************************************************/
int checkResult(const char* actualRetVal, const char* expectedRetVal,
	const char expectedOutput[], const char functionName[]);

int main(int argc, char* argv[])
{
	//Statistical variables
	int numtests = 3;
	int errors = 0;

	//create test strings
	char testString[50];
	char charset[50];
	char expected[50];
	char *result;

	//test strdog
	(void)strcpy(testString, "ABCDEFGHIJKL");
	(void)strcpy(charset, "wxyz");
	(void)strcpy(expected, "wxyzABCDEFGHIJKL");

	result = strdog(charset, testString);
	errors += checkResult(result, testString, expected, "strdog");

	//test strrm
	(void) strcpy(testString, "ABCDEFGHIJKL");
	(void) strcpy(charset, "ALZJ");
	(void) strcpy(expected, "BCDEFGHIK");

	result = strrm(testString, charset);
	errors += checkResult(result, testString, expected, "strrm");

	//test strcrm
	(void)strcpy(testString, "ABCDEFGHIJKL");
	(void)strcpy(charset, "CIHZ");
	(void)strcpy(expected, "CHI");

	result = strcrm(testString, charset);
	errors += checkResult(result, testString, expected, "strrm");

	//print statistics
	printf("Testsuite Completed. %i Succeeded, %i Failed.\n", numtests - errors,
		errors);
} // main

/*******************************************************************************
 * checkResult - compares the expected output and return value to the expected
 *				 values to determine if the test passes or fails.
 * @param const char*  actualRetVal   - the actual return value from the method.
 *									    Also effectively the output string.
 * @param const char*  expectedRetVal - the expected return value from the
 *									    method.
 * @param const char[] expectedOutput - the expected output string (see note)
 * @param const char[] functionName   - the name of the function (for use in
 *										status printout
 * @note expectedRetVal cannot be used as the expected string output since it is
 *		 a pointer to the input of the method, which will point to the actual
 *		 output value upon successful execution.
 ******************************************************************************/
int checkResult(const char* actualRetVal, const char* expectedRetVal,
	const char expectedOutput[], const char functionName[])
{
	int retVal = 0;

	//if the return value doesn't match, the test fails
	if (actualRetVal != expectedRetVal)
	{
		printf("Test of %s Failed. Return value does not match.", functionName);
		printf("Expected Value: %p, Actual Value: %p\n", (void*) expectedRetVal,
			(void*) actualRetVal);
		retVal = 1;
	} // if

	//if the output string doesn't match, the test fails.
	if (strcmp(actualRetVal, expectedOutput))
	{
		printf("Test of %s Failed. Output does not match.", functionName);
		printf("Expected Value: %s, Actual Value: %s\n",
			expectedOutput, actualRetVal);
		retVal = 1;
	} // if

	//if the test doesn't fail, it passes
	if (!retVal)
	{
		printf("Test of %s Passed!\n", functionName);
	} // if

	return retVal;
} // checkResults