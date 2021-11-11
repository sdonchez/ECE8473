////////////////////////////////////////////////////////////////////////////////
// S.Donchez
// rand.c - Write a C version of rand.java which produces identical output when 
// run with the same command-line argument.
////////////////////////////////////////////////////////////////////////////////
#include <stdio.h> //for printf operations
#include <string.h> //for strlen

long seed; //seed value for "random" number generator

long multiplier = 0x5DEECE66DL; //arbitrary value used to obfuscate input
long addend = 0xBL; //arbitrary value used to obfuscate input
long mask = (1L << 48) - 1; //mask used to constrain range of seed

void initialScramble(long init);
int next(int bits);
int nextInt();
long hashCode(char* s);


int main(int argc, char* argv[])
{
    //extract user defined value from command line arguments
    char* a = argv[1];

    //generate and display seed
    long init = hashCode(a);
    initialScramble(init);

    printf("a = %s init = %li seed = %li\n", a, init, seed);

    //generate subsequent values as desired
    for (int i = 0; i < 10; ++i)
    {
        printf("%d\n", nextInt());
    }

    return 0;
}

/*******************************************************************************
 * initialScramble -    performs obfuscation of input value to generate initial
 *                      seed
 * @param init  inital value used to generate seed
 * @returns     none
 ******************************************************************************/
 void initialScramble(long init)
{
    seed = (init ^ multiplier) & mask;
} //initialScramble

/*******************************************************************************
 * next -   generates a psuedo-random output of specified length based on the
 *          current seed value, updates seed for next round.
 * @param bits  integer number of bits of output to generate
 * @returns     integer representation of arbitrary binary value of length bits
 ******************************************************************************/
 int next(int bits)
{
    seed = (seed * multiplier + addend) & mask;

    return (int)(seed >> (48 - bits));
} //next

/*******************************************************************************
 * nextInt -    wrapper function for next to generate a 32 bit integer output
 * @returns     32 bit psuedo-random number
 ******************************************************************************/
int nextInt()
{
    return next(32);
} //nextInt

/*******************************************************************************
 * hashCode -   constructs a hash of a string, in a manner comparable to Java
 * @param s     pointer to string to be converted
 * @returns     long containing the hash code
 * @note        similar to java.lang.String hashCode. The hash code for a String
*               object is computed as 
*               s[0]*31^(n-1) + s[1]*31^(n-2) + ... + s[n-1]
*               using int arithmetic, where s[i] is the ith character of the 
*               string, n is the length of the string, and ^ indicates 
*               exponentiation. (The hash value of the empty string is zero.)
* @link         https://docs.oracle.com/javase/7/docs/api/java/lang/String.html
 ******************************************************************************/
long hashCode(char* s)
{
    long h = 0; 
    for (int i = 0; i < strlen(s); i++)
    {
        h = 31 * h + s[i];
    } //for
    return h;
} //hashCode