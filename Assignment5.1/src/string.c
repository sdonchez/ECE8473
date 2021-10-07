////////////////////////////////////////////////////////////////////////////////
// S. Donchez
// string.c - For each of the functions in string.c rewrite the initial 
// implementation so that the provided test program tester.c encounters no errors.
// 
// The functions are from the C library string.h but with name prefix my_ so 
// they won't interfere with use of the standard functions.
// 
// The test program was adapted from the GNU C library 
// glibc - 2.34 / string / tester.c
// 
// Do not use any temporary arrays(no extra static, auto, or dynamic arrays).
// 
// For each function, the implementation must be self - contained and may not 
// invoke any other functions.
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h> // for size_t

/*******************************************************************************
 * my_strlen -	Implements the strlen standard function. The strlen() function 
 *				calculates the length of the string s, excluding the terminating
 *				null byte ('\0').
 * @param const char s[] - string for which the length is to be determined
 * @returns size_t		 - containing the number of bytes in the string
 ******************************************************************************/
size_t my_strlen( const char s[]) 
{ 
	int count;

	// iterate through string looking for terminator
	for (count = 0; s[count] != '\0'; count++);
	
	//because of zero index, position of null terminator is equal to length
	return count;
} // strlen

/*******************************************************************************
 * my_strcpy  - Implements the strcpy standard function. The strcpy() function 
 *				copies the string pointed to by src, including the terminating 
 *				null byte ('\0'), to the buffer pointed to by dest. The strings
 *				may not overlap, and the destination string dest must be large
 *				enough to receive the copy. Beware of buffer overruns!
 * @param char * restrict s1 - the destination to be copied to
 * @param chat * restrict s2 - the source to be copied from
 * @returns	char*			 - pointer to the destination string
 ******************************************************************************/
char *my_strcpy( char * restrict s1, const char * restrict s2) 
{ 
	//make sure the destination pointer is defined
	if (s1 == NULL)
	{
		return NULL;
	} // if 

	//store the location of the destination pointer since we will increment it
	char* retval = s1;

	//while the source pointer doesn't point to a null terminator, copy it to
	//the destination pointer and increment both pointers
	while (*s2 != '\0')
	{
		*s1 = *s2;

		s1++;
		s2++;
	} // while

	//append null terminator
	*s1 = '\0';

	return retval;
}
 // my_strcpy

/*******************************************************************************
 * my_strncpy - Implements the strncpy standard function. The strncpy() function
 *				copies at most n bytes of the string pointed to by src to the 
 *				buffer pointed to by dest. The strings may not overlap, and the 
 *				destination string dest must be large enough to receive the 
 *				copy. Warning: If there is no null byte among the first n 
 *				bytes of src, the string placed in dest will not be 
 *				null-terminated.
 *
 *				If the length of src is less than n, strncpy() writes additional
 *				null bytes to dest to ensure that a total of n bytes are 
 *				written.
 * @param char * restrict s1 - the destination to be copied to
 * @param chat * restrict s2 - the source to be copied from
 * @param size_t n			 - the number of bytes to copy
 * @returns	char*			 - pointer to the destination string
 ******************************************************************************/
char *my_strncpy( char * restrict s1, const char * restrict s2, size_t n) 
{ 
	//make sure the destination pointer is defined
	if (s1 == NULL)
	{
		return NULL;
	} //if

	//define the loop iterator since we need it to persist outside the loop
	size_t i;

	//copy each byte of the source into the destination until we find the
	//null terminator
	for (i = 0; i < n && s2[i] != '\0'; i++)
	{
		s1[i] = s2[i];
	} // for

	//fill any left over space with the null terminator
	for (; i < n; i++)
	{
		s1[i] = '\0';
	} // for

	return s1;
} // my_strncpy

/*******************************************************************************
 * my_strcat  - implements the strcat standard function. The strcat() function 
 *				appends the src string to the dest string, overwriting the 
 *				terminating null byte ('\0') at the end of dest, and then adds a
 *				terminating null byte. The strings may not overlap, and the dest
 *				string must have enough space for the result. If dest is not 
 *				large enough, program behavior is unpredictable; buffer overruns
 *				are a favorite avenue for attacking secure programs.
 * @param char * restrict s1 - the destination to be copied to
 * @param chat * restrict s2 - the source to be copied from
 * @returns	char*			 - pointer to the destination string
 ******************************************************************************/
char *my_strcat( char * restrict s1, const char * restrict s2) 
{ 
	//make sure the destination pointer is defined
	if (s1 == NULL)
	{
		return NULL;
	}

	char* retval = s1;

	//find null terminator in s1 to determine where we start copying
	for (; *s1 != '\0'; ++s1);
		//no body since the goal is the iterator

	//copy source into destination byte by byte until we see the null terminator
	while (*s2 != '\0')
	{
		*s1 = *s2;

		s1++;
		s2++;
	} // while 

	//append the null terminator
	*s1 = '\0';

	return retval;
} // my_strcat

/*******************************************************************************
 * my_strncat  - implements the strncat standard function. The strncat() 
 *				function appends n bytes of the src string to the dest string, 
 *				overwriting the	terminating null byte ('\0') at the end of dest,
 *				and then adds a	terminating null byte. The strings may not 
 *				overlap, and the dest string must have enough space for the 
*				result. If dest is not large enough, program behavior is 
*				unpredictable; buffer overruns are a favorite avenue for 
*				attacking secure programs. For strncat, src does not need to be 
*				null-terminated if it contains n or more bytes.
 * @param char * restrict s1 - the destination to be copied to
 * @param chat * restrict s2 - the source to be copied from
 * @param size_t n			 - the number of bytes to copy
 * @returns	char*			 - pointer to the destination string
 ******************************************************************************/
char *my_strncat( char * restrict s1, const char * restrict s2, size_t n) 
{ 
	//make sure the destination pointer is defined
	if (s1 == NULL)
	{
		return NULL;
	} // if

	//create a pointer to the start of the destination (since we increment s1)
	char* retval = s1;

	//define the loop iterator since we need it to persist outside the loop
	size_t i;

	//find null terminator in s1 to determine where we start copying
	for (; *s1 != '\0'; ++s1);
		//no body since the goal is the iterator

	//copy up to n bytes of s2, or until we hit the null terminator
	for (i = 0; i < n && s2[i] != '\0'; i++)
	{
		s1[i] = s2[i];
	} // for

	//append null terminator
	s1[i] = '\0';

	return retval;
} // my_strncat

/*******************************************************************************
 * my_strchr  - implements the strchr standard function. The strchr() function 
 *				returns a pointer to the first occurrence of the character c in 
 *				the string s.
 *				Here "character" means "byte"; these functions do not work with 
 *				wide or multibyte characters.
 * @param const char *s - a pointer to the string to be searched
 * @param int		  c - the character (single byte) to be searched for in s
 * @returns char *		- a pointer to the location of the character in s
 ******************************************************************************/
char *my_strchr( const char *s, int c) 
{
	//default case should no match be found
	char* retval = NULL;
	for (int i = 0; ; i++)
	{
		//if there's a match, set retval to point to it and break the loop
		if (s[i] == c)
		{
			retval = (char*) (s + i);
			break;
		} // if

		//if we run out of characters, break leaving retval null
		else if (s[i] == '\0')
		{
			break;
		} //else if
	} // for

	return retval;
} // my_strchr

/*******************************************************************************
 * my_strchr  - implements the strrchr standard function. The strrchr() function
 *				returns a pointer to the last occurrence of the character c in
 *				the string s.
 *				Here "character" means "byte"; these functions do not work with
 *				wide or multibyte characters.
 * @param const char *s - a pointer to the string to be searched
 * @param int		  c - the character (single byte) to be searched for in s
 * @returns char *		- a pointer to the location of the character in s
 ******************************************************************************/
char *my_strrchr( const char *s, int c) 
{
	//default case should no match be found
	char* retval = NULL;
	int count;

	//find the null terminator to use as start of search
	for (count = 0; s[count] != '\0'; count++);
		//no body since the goal is the iterator

	//iterate through string from back to front
	for (int i = count; i >= 0 ; i--)
	{
		//if there's a match, update retval to point to it and break the loop
		if (s[i] == c)
		{
			retval = (char*)(s + i);
			break;
		} // if
	} // for

	return retval;
} // my_strrchr

/*******************************************************************************
 * my_memchr  - implements the memchr standard function. The memchr() function 
 *				scans the initial n bytes of the memory area pointed to by s for
 *				the first instance of c. Both c and the bytes of the memory 
 *				area pointed to by s are interpreted as unsigned char.
 * @param const void *v - a void pointer to the region in memoty to search
 * @param int		  c - the character (byte) to search for
 * @param size_t   size - the size of the area to search
 * @returns void *		- pointer to the location of the character in v
 ******************************************************************************/
void *my_memchr( const void *v, int c, size_t size) {
	//default case should no match be found
	char* retval = NULL;

	//convert void pointer to a char* pointer so it can be operated on
	//(per function description)
	const unsigned char* mem = v;

	//iterate through size bytes of the region searching for the character
	for (int i = 0; i < size; i++)
	{
		//if found, update retval to point to it and break the loop
		if ( *(mem + i) == (unsigned char) c)
		{
			retval = (void *)(mem + i);
			break;
		} // if
	} // for

	return retval;
} // my_memchr

/*******************************************************************************
 * my_memcpy  - implements the memcpy standard function. The memcpy() function 
 *				copies n bytes from memory area src to memory area dest. The 
 *				memory areas must not overlap.
 * @param		void* restrict v1 - the destination region in memory
 * @param const void* restrict v2 - the source location in memory
 * @param		size_t		 size - the number of bytes to copy
 * @returns     void *            - location of the destination in memory
 ******************************************************************************/
void *my_memcpy( void * restrict v1, const void * restrict v2, size_t size) 
{ 
	//cast void pointers to unsigned char so they can be operated on
	unsigned char* dest = v1;
	const unsigned char* src = v2;

	//ensure the destination pointer is defined
	if (dest == NULL)
	{
		return NULL;
	} // if

	//copy size bytes from the source to the destination
	for (int i = 0; i <size; i++)
	{
		dest[i] = src[i];
	} // for

	return v1;
} // my_memcpy

/*******************************************************************************
 * my_memset  - implements the memset standard function. The  memset() function 
 *				fills the first n bytes of the memory area pointed to by s with
 *				the constant byte c.
 * @param void*     v - a pointer to the start of the region in memory to fill
 * @param int       c - the byte to fill the destination with
 * @param size_t size - the number of bytes to fill
 * @returns void *	  - pointer to the start of the destination region
 ******************************************************************************/
void *my_memset( void *v, int c, size_t size) 
{ 
	//cast void pointer to unsigned char so we can operate on them
	unsigned char* mem = v;

	//iterate through size bytes of memory and set them to the char c
	for (size_t i = 0; i < size; i++)
	{
		mem[i] = c;
	} // for

	return v;
} // my_memset

