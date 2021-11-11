// S.Donchez
// rand.h - Source from assignment 3 part 2, without main function and seperated
// into header and source. Produces predictable "random" values based on a
// given seed.
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <stdio.h> //for printf operations
#include <string.h> //for strlen


extern long seed; //in rand.c

/*******************************************************************************
 * initialScramble -    performs obfuscation of input value to generate initial
 *                      seed
 * @param init  inital value used to generate seed
 * @returns     none
 ******************************************************************************/
void initialScramble(long init);

/*******************************************************************************
 * nextInt -    wrapper function for next to generate a 32 bit integer output
 * @returns     32 bit psuedo-random number
 ******************************************************************************/
int nextInt();

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
long hashCode(char* s);