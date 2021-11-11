////////////////////////////////////////////////////////////////////////////////
// S.Donchez
// a1/p1.c - See comments for individual parts, below. 
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>  //For text input/output
#include <limits.h> //For constant definitions
#define DISP(x, y) printf(#x " = " y "\n", x)

int main(void)
{

	/**************************************************************************
	 * Part 1 - Write a C program which displays the names and values of the 
	 * following constants from limits.h: 
	 * CHAR_BIT, CHAR_MIN, CHAR_MAX, SCHAR_MIN, SCHAR_MAX, UCHAR_MAX
	 * SHRT_MIN, SHRT_MAX, USHRT_MAX
	 * INT_MIN, INT_MAX, UINT_MAX
	 * LONG_MIN, LONG_MAX, ULONG_MAX
	 * LLONG_MIN, LLONG_MAX, ULLONG_MAX
	 **************************************************************************/

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

	/***************************************************************************
	 * Part 2 - and also computes at run-time (without using any predefined
	 *  constants or assumptions) and displays the value of ULONG_MAX.
	 **************************************************************************/

	unsigned long maxLongUnsigned = 0UL - 1UL;
	printf("Maximum unsigned long value: %lu\n", maxLongUnsigned);

	return 0;
} // main