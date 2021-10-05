////////////////////////////////////////////////////////////////////////////////
// S.Donchez
// SubsCipher.c -  Your a4-data/subs.txt file contains a secret message 
// encrypted using a substitution cipher.
// 
// Decrypt using subs.sh after changing the substitution table to correspond to 
// your userid.
//
//
// Write a C program to compute your substitution table using the following 
// algorithm to shuffle(permute) the set of characters A...Z0...9:
//
// initialScramble(hashCode("alice")); // replace alice with your userid
//
// char a[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
// 
// for n = 36, 35, ..., 2  // strlen(a) downto 2
// 
// unsigned int i = nextInt();  i = i % n;  // i = random index from 0 to n-1
// 
// swap a[i] and a[n - 1]
// 
// At the end of the message there is a confirmation code which must be 
// submitted to prove that your program worked.The submission address is shown 
// in your private course links.
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "rand.h"
#include "swap.h"

char* username = "sdonchez";
char a[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
int cipherLength;
unsigned int toSwap;

int main(int argc, char* argv[])
{
	//initialize PRNG
	long init = hashCode(username);
	initialScramble(init);

	//determine length of array
	cipherLength = strlen(a);

	//print original array for reference
	printf("  in: %s\n", a);

	//iterate through array and perform substitution per algorithm
	for (int n = cipherLength; n >= 2; n--)
	{
		toSwap = nextInt();
		toSwap = toSwap % n;
		swapElements(a, toSwap, n-1);
	} // for

	//print substituted array
	printf("subs: %s\n", a);

	return 0;
} // main