////////////////////////////////////////////////////////////////////////////////
// S.Donchez
// strfxns.h - header file containing declarations of an additional set of 
// non-standard string functions. See individual method comments for details.
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <string.h> //for standard string functions per assignment description
#include <stdbool.h> //for strcrm flag

/*******************************************************************************
 * strdog - Prepends s1 to s2 and returns s2.
 *			A relative of strcat, strdog inserts s1 at the beginning of s2. It
 *			does this by moving the characters of s2 over to make room for s1,
 *			then copying the characters from s1 into the beginning of s2.
 *			Example:
 *			strcpy( s, "efg"); p = strdog( "abc", s);
 *			s now contains "abcefg" and p == s.
 *			Do not use any temporary arrays (no extra static, auto, or dynamic
 *			arrays). Do not use any loops; use functions from string.h to
 *			perform the operations.
 * @param const char s1[] - string to be inserted at the beginning of output
 * @param		char s2[] - string to be prepended to
 * @return		char*	  - pointer to resultant string
 ******************************************************************************/
char* strdog(const char s1[], char s2[]);

/*******************************************************************************
 * strrm -  Removes the set of s2 characters from s1 and returns s1.
 *			Example:
 *			strcpy( s, "AABZBAADZDAA"); p = strrm( s, "ZA");
 *			s now contains "BBDD" and p == s.
 *			Do not use any temporary arrays (no extra static, auto, or dynamic
 *			arrays).
 * @param       char s1[] - string to have characters removed from
 * @param const char s2[] - array of characters to be removed
 * @returns		char *	  - a pointer to the newly trimmed string
 ******************************************************************************/
char* strrm(char s1[], const char s2[]);

/*******************************************************************************
 * strcrm - Removes the complement of the set of s2 characters from s1 and
 *			returns s1.
 *			Example:
 *			strcpy( s, "AABZBAADZDAA"); p = strcrm( s, "ZA");
 *			s now contains "AAzAAzAA" and p == s.
 *			Do not use any temporary arrays (no extra static, auto, or dynamic
 *			arrays).
 * @param       char s1[] - string to have characters removed from
 * @param const char s2[] - array of characters to be kept
 * @returns		char *	  - a pointer to the newly trimmed string
 ******************************************************************************/
char* strcrm(char s1[], const char s2[]);