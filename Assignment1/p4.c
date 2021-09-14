////////////////////////////////////////////////////////////////////////////////
// S.Donchez
// A1/P4.c
// 
////////////////////////////////////////////////////////////////////////////////
#include <string.h>
#include <errno.h>
#include <stdio.h>

int main()
{

	/***************************************************************************
	* Write a C program which uses strerror() to get the error message 
	* associated with errno values from 0 to 200. Display each error number and
	* message.Be careful to check for errors in the strerror() call and possible
	* NULL return values.
	***************************************************************************/
	char* errString;
	for (int error = 0; error <= 200; error++)
	{
		errString = strerror(error);
		int strErr = errno;
		if (errString == NULL)
		{
			printf("\nstrerror returned null! \n");
			errString = "";
		}
		if (strErr)
		{
			printf("Error looking up error message for errno = %i", error);
			return strErr;
		}
		else
			printf("Error Number: %3i; Error Message: %s\n", error, errString);
	}
}