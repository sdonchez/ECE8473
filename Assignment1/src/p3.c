////////////////////////////////////////////////////////////////////////////////
// S.Donchez
// a1/p3.c - see comments for respective parts, below
////////////////////////////////////////////////////////////////////////////////
#include <errno.h>
#include <string.h>
#include <errno.h>
#include <tgmath.h>
#include <stdio.h>
#include <float.h>

void errHandler(char* lName, char* sName, int error);

int main()
{

	/***************************************************************************
	* Part 1: Write a C program which computes and displays the value of
	* sqrt(-1). Include <errno.h> and after calling sqrt() display the value of
	* errno and also call perror(). 
	***************************************************************************/

	double x = sqrt(-1);

	//save the value of errno in case it gets changed before we need it
	int sqrtErr = errno;
	printf("The square root of -1 is: %g.\n", x);
	errHandler("square root", "sqrt", sqrtErr);
	

	/***************************************************************************
	* Part 2: Also compute and display the value of some tgmath.h function 
	* (your choice) with a valid input which produces a range error, i.e. 
	* overflow. Display the value of errno and also call perror(). 
	***************************************************************************/
	errno = 0;
	double result = pow(FLT_MAX, 10);

	//save the value of errno in case it gets changed before we need it
	int powErr = errno;
	printf("The value of %g squared is %g\n", FLT_MAX, result);
	errHandler("square", "pow", powErr);
	
} // main

/*******************************************************************************
 * errHandler - handles the error as required by the assignment. Indicates that 
 * 				an error has ocurred, provides the error number, and calls 
 * 				perror to provide the error details. Implements robust errno 
 * 				handling to deal with errors ocurring during function 
 * 				execution.
 * @param lName  	(string) the long name of the operation which caused the 
 * 					error, as used in the error indication printout.
 * @param sName 	(string) the short name of the operation which caused the 
 * 					error, generally the name of the function in which it 
 * 					ocurred.
 * @param error 	(int) the value of errno as a result of the function in 
 * 					question
 * 
 * @return 			none
 ******************************************************************************/
void errHandler(char* lName, char* sName, int error)
{
	if (error)
	{
		printf("While computing the %s, an error was encountered. ", lName);
		printf("The error has an error number of %i\n", error);
		
		//In case errno changed, save it so we can restore it
		int tmpErr = errno;

		//reset errno to its value after the sqrt call for perror
		errno = error;
		perror(sName);

		//provided errno hasn't changed, put it back to what it was pre-change.
		if (errno == error)
		{
			errno = tmpErr;
		} // if
	} // if
} // errHandler