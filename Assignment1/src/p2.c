////////////////////////////////////////////////////////////////////////////////
// S.Donchez
// a1/p2.c - See comments for respective parts, below.
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>  //For text input/output
#include <float.h> //For constant definitions
#define DISP(x, y) printf(#x " = " y "\n", x)

int main(void)
{

	/***************************************************************************
	 * Part 1 - Write a C program which displays the names and values of the 
	 * following constants from float.h:
	 *	FLT_MIN, FLT_TRUE_MIN, FLT_MAX, FLT_EPSILON
	 *	DBL_MIN, DBL_TRUE_MIN, DBL_MAX, DBL_EPSILON
	 *	LDBL_MIN, LDBL_TRUE_MIN, LDBL_MAX, LDBL_EPSILON
	 **************************************************************************/

	printf("Float Values: \n\n");
	printf("Float Types: \n");
	DISP(FLT_MIN, "%e");
	DISP(FLT_TRUE_MIN, "%e");
	DISP(FLT_MAX, "%e");
	DISP(FLT_EPSILON, "%e");
	printf("\n");

	printf("Double Types: \n");
	DISP(DBL_MIN, "%e");
	DISP(DBL_TRUE_MIN, "%e");
	DISP(DBL_MAX, "%e");
	DISP(DBL_EPSILON, "%e");
	printf("\n");

	printf("Long Double Types: \n");
	DISP(LDBL_MIN, "%Le");
	DISP(LDBL_TRUE_MIN, "%Le");
	DISP(LDBL_MAX, "%Le");
	DISP(LDBL_EPSILON, "%Le");
	printf("\n");

	/***************************************************************************
	 * Part 2- and also computes at run - time (without using any predefined 
	 * constants or assumptions) and displays the value of DBL_EPSILON.
	 *
	 * The machine precision ? = DBL_EPSILON is defined as the smallest double
	 * such that 1.0 + ? > 1.0, i.e. 1.0 + ? / 2.0 == 1.0
	 **************************************************************************/

	double eps = 1.0;
	double epsC;
	while (1 + eps > 1)
	{
		epsC = eps;
		eps /= 2;
	} // while

	printf("Value of DBL_EPSILON is %e\n", epsC);

	return 0;
} // main