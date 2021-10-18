////////////////////////////////////////////////////////////////////////////////
// Stephen Donchez
// strfxns.c - Implements an additional set of non-standard string functions.
// See individual method comments for details.
////////////////////////////////////////////////////////////////////////////////
#include "strfxns.h" //Custom header for these functions

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
char* strdog(const char s1[], char s2[])
{
	size_t s1Len = strlen(s1);

	//shift the contents of s2 over by the length of s1, including the null 
	//terminator
	memmove(s2 + s1Len, s2, strlen(s2) + 1);

	//copy s1 into the space originally occupied by s2
	memcpy(s2, s1, s1Len);

	return s2;
} // strdog

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
char* strrm(char s1[], const char s2[])
{
	size_t lenS1 = strlen(s1);

	//iterate through set of characters to be removed
	for (int remChar = 0; remChar < strlen(s2); remChar++)
	{
		//iterate through set of characters in target string
		for (int strChar = 0; strChar < lenS1;)
		{

			//if there's a match, shift the remainder of the string left by 1
			//space and decrement the total length
			if (s1[strChar] == s2[remChar])
			{
				memmove(s1 + strChar, s1 + strChar + 1, lenS1 - strChar);
				lenS1--;
			} // if

			//otherwise look at the next character (only if not a match since
			//otherwise the character shifted into the current position doesn't
			//get checked).
			else
			{
				strChar++;
			} // else
		} // for
	} // for

	//append the null terminator and return
	s1[lenS1] = '\0';
	return s1;
} // strrm

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
char* strcrm(char s1[], const char s2[])
{
	size_t lenS1 = strlen(s1);
	bool found;

	//iterate through string to be trimmed
	for (int strChar = 0; strChar < lenS1;)
	{

		//default to no match
		found = false;

		//iterate through list of characters to keep
		for (int keepChar = 0; keepChar < strlen(s2); keepChar++)
		{

			//if we find a match, set found to true and break inner loop
			if (s1[strChar] == s2[keepChar])
			{
				found = true;

				//no need to keep looking if we've already found it
				break;
			} // if
		} // for

		//if we haven't found a match, shift the rest of the string 1 to the
		//left and decrement the length
		if (!found)
		{
			memmove(s1 + strChar, s1 + strChar + 1, lenS1 - strChar);
			lenS1--;
		} // if

		//otherwise look at the next character (only if not a match since
		//otherwise the character shifted into the current position doesn't
		//get checked).
		else
		{
			strChar++;
		} // else
	} // for

	//append the null terminator and return
	s1[lenS1] = '\0';
	return s1;
} // strcrm