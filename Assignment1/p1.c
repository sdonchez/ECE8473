////////////////////////////////////////////////////////////////////////////////
// S.Donchez
// A1/P1.c
// 
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>  //For text input/output
#include <limits.h> //For constant definitions
#define DISP(x, y) printf(#x " = " y "\n", x)

int main(void)
{
	/*
	* Write a C program which displays the names and values of the following 
	* constants from limits.h: 
	* CHAR_BIT, CHAR_MIN, CHAR_MAX, SCHAR_MIN, SCHAR_MAX, UCHAR_MAX
	*
	* SHRT_MIN, SHRT_MAX, USHRT_MAX
	*
	* INT_MIN, INT_MAX, UINT_MAX
	*
	* LONG_MIN, LONG_MAX, ULONG_MAX
	*
	* LLONG_MIN, LLONG_MAX, ULLONG_MAX 
	*/

	printf("Integer Values: \n\n");
	printf("Char Types: \n");
	DISP(CHAR_BIT, "%hhi");
	DISP(CHAR_MIN, "%hhi");
	DISP(CHAR_MAX, "%hhi");
	DISP(SCHAR_MIN, "%hhi");
	DISP(SCHAR_MAX, "%hhi");
	DISP(UCHAR_MAX, "%hhu");
	printf("\n");

	printf("Short Types: \n");
	DISP(SHRT_MIN, "%hi");
	DISP(SHRT_MAX, "%hi");
	DISP(USHRT_MAX, "%hu");
	printf("\n");

	printf("Integer Types: \n");
	DISP(INT_MIN, "%i");
	DISP(INT_MAX, "%i");
	DISP(UINT_MAX, "%u");
	printf("\n");

	printf("Long Types: \n");
	DISP(LONG_MIN, "%li");
	DISP(LONG_MAX, "%li");
	DISP(ULONG_MAX, "%lu");
	printf("\n");

	printf("Long Long Types: \n");
	DISP(LLONG_MIN, "%lli");
	DISP(LLONG_MAX, "%lli");
	DISP(ULLONG_MAX, "%llu");
	printf("\n");

	unsigned long maxLongUnsigned = (unsigned long)0 - (unsigned long)1;
	printf("Maximum unsigned long value: %lu\n", maxLongUnsigned);

	return 0;
}