////////////////////////////////////////////////////////////////////////////////
// S.Donchez
// TransCipher.c - Your a4 - data / trans.bin file contains a secret message 
// encrypted with a transposition cipher using trans.c.
//
// Write a C program using fread() and fwrite(), similar to trans.c, to perform 
// decryption so you can read the secret message.
//
// At the end of the message there is a confirmation code which must be 
// submitted to prove that your program worked.The submission address is shown 
// in your private course links.
////////////////////////////////////////////////////////////////////////////////

#include "rand.h"
#include <stdio.h>
#include "swap.h"

#define NMAX 65536

char* username = "sdonchez";
int cipherLength;

int main(void)
{
	//initialize PRNG
	long init = hashCode(username);
	initialScramble(init);

	unsigned int len; char buf[NMAX]; len = fread(buf, 1, NMAX, stdin);

	if (len == NMAX) fprintf(stderr, "trans: warning: input buffer is full\n");

	unsigned int toSwap[len];

	//generate list of substitution values (in reverse order)
	for (int n = len; n >= 1; n--)
	{
		toSwap[n] = nextInt();
		toSwap[n] = toSwap[n] % n;
	} // for

	//perform substitutions to undo encryption
	for (int n = 1; n <= len; n++)
	{
		swapElements(buf, toSwap[n], n-1);
	} // for

	//print output
	fwrite(buf, 1, len, stdout);
} //main