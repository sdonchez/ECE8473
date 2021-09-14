////////////////////////////////////////////////////////////////////////////////
// S.Donchez
// A1/P3.c
// 
////////////////////////////////////////////////////////////////////////////////
#include <errno.h>
#include <string.h>
#include <errno.h>
#include <tgmath.h>
#include <stdio.h>
#include <float.h>

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
	if (sqrtErr)
	{
		printf("While computing the square root, an error was encountered. ");
		printf("The error has an error number of %i\n", sqrtErr);
		
		//In case errno changed, save it so we can restore it
		int tmpErr = errno;

		//reset errno to its value after the sqrt call for perror
		errno = sqrtErr;
		perror("sqrt");

		//provided errno hasn't changed, put it back to what it was pre-change.
		if (errno == sqrtErr)
		{
			errno = tmpErr;
		}
	}

	/***************************************************************************
	* Part 2: Also compute and display the value of some tgmath.h function 
	* (your choice) with a valid input which produces a range error, i.e. 
	* overflow. Display the value of errno and also call perror(). 
	***************************************************************************/

	errno = 0;
	double result = pow(FLT_MAX, 10);
	printf("The value of %g squared is %g\n", FLT_MAX, result);

	//save the value of errno in case it gets changed before we need it
	int powErr = errno;
	if (powErr)
	{
		printf("While computing the square, an error was encountered. ");
		printf("The error has an error number of %i\n", powErr);

		//In case errno changed, save it so we can restore it
		int tmpErr = errno;

		//reset errno to its value after the sqrt call for perror
		errno = powErr;
		perror("pow");

		//provided errno hasn't changed, put it back to what it was pre-change.
		if (errno == powErr)
		{
			errno = tmpErr;
		}
	}
	
}