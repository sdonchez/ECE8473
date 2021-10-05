////////////////////////////////////////////////////////////////////////////////
// S.Donchez
// swap.c - Implements a simple swap function for two elements in an array.
////////////////////////////////////////////////////////////////////////////////

#include "swap.h"

/*******************************************************************************
 * swapElements - swaps two elements in a given array.
 * @param array - the array sontaining the two elements
 * @param posA	- the first position in the array to be swapped
 * @param posB	- the second position in the array to be swapped
 * @returns		  none
 ******************************************************************************/
void swapElements(char array[], int posA, int posB)
{
	char temp;
	temp = array[posA];
	array[posA] = array[posB];
	array[posB] = temp;
} // swapElements