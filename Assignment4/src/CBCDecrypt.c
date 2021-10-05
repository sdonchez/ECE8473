////////////////////////////////////////////////////////////////////////////////
// S.Donchez
// CBCDecrypt.c - Your a4 - data / CBC.bin file contains a secret message 
// encrypted using Cipher Block Chaining.
//
// The CBC pseudo - random numbers were obtained using nextInt() from the 
// previous assignment, initialized with your userid, e.g.
// initialScramble(hashCode("alice")); (replace alice with your userid)
//
// Write a C program using getchar() and putchar(), similar to getchar.c, to 
// perform CBC decryption so you can read the secret message.
//
// At the end of the message there is a confirmation code which must be 
// submitted to prove that your program worked.The submission address is shown 
// in your private course links.
////////////////////////////////////////////////////////////////////////////////

#include "rand.h"

char* username = "sdonchez";

int prevEncrypted = 0;
int currentEncrypted;
int currentDecrypted;
int currentKey;


int main(int argc, char* argv[])
{
	//initialize PRNG
	long init = hashCode(username);
	initialScramble(init);

	while (1) //until EOF
	{

		//get current character and make sure it isn't EOF
		currentEncrypted = getchar();
		if (currentEncrypted < 0)
		{

			//if it it EOF, break the loop
			break;
		} // if

		//get the key from the PRNG
		currentKey = nextInt();

		//decrypt per CBC algorithm
		currentDecrypted = currentEncrypted - prevEncrypted - currentKey;
		
		//write the decrypted char to std out
		putchar(currentDecrypted);

		//save the input for use in the next round
		prevEncrypted = currentEncrypted;
	} // while

	return 0;
} // main