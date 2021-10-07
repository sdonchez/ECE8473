// adapted from glibc-2.34/string/tester.c

#include <stdio.h>
#include <string.h>

#ifndef SYSTEM // use my_ versions
#define strlen  my_strlen
#define strcpy  my_strcpy
#define strncpy my_strncpy
#define strcat  my_strcat
#define strncat my_strncat
#define strchr  my_strchr
#define strrchr my_strrchr
#define memchr  my_memchr
#define memcpy  my_memcpy
#define memset  my_memset
size_t my_strlen( const char s[]);
char *my_strcpy( char * restrict s1, const char * restrict s2);
char *my_strncpy( char * restrict s1, const char * restrict s2, size_t n);
char *my_strcat( char * restrict s1, const char * restrict s2);
char *my_strncat( char * restrict s1, const char * restrict s2, size_t n);
char *my_strchr( const char *s, int c);
char *my_strrchr( const char *s, int c);
void *my_memchr( const void *v, int c, size_t size);
void *my_memcpy( void * restrict v1, const void * restrict v2, size_t size);
void *my_memset( void *v, int c, size_t size);
#endif

#define	STREQ(a, b)	((strcmp)((a), (b)) == 0)

const char *it = "<UNSET>";	/* Routine name for message routines. */
size_t errors = 0;
int verbose = 0;

/* Complain if condition is not true.  */
static void
check (int thing, int number)
{
  if (!thing)
  {
    printf ("%s flunked test %d\n", it, number);
    ++errors;
  }
  else if( verbose) printf ("%s passed test %d\n", it, number);
}

/* Complain if first two args don't strcmp as equal.  */
static void
equal (const char *a, const char *b, int number)
{
  check (a != NULL && b != NULL && STREQ (a, b), number);
}

char one[50];
char two[50];
char *cp;

#define SIMPLE_COPY(fn, n, str, ntest) \
  do {									      \
    int __n;								      \
    char *cp;								      \
    for (__n = 0; __n < (int) sizeof (one); ++__n)			      \
      one[__n] = 'Z';							      \
    fn (one, str);							      \
    for (cp = one, __n = 0; __n < n; ++__n, ++cp)			      \
      check (*cp == '0' + (n % 10), ntest);				      \
    check (*cp == '\0', ntest);						      \
  } while (0)

static void
test_strcpy (void)
{
  int i;
  it = "strcpy";
  check (strcpy (one, "abcd") == one, 1); /* Returned value. */
  equal (one, "abcd", 2);		/* Basic test. */

  (void) strcpy (one, "x");
  equal (one, "x", 3);			/* Writeover. */
  equal (one+2, "cd", 4);		/* Wrote too much? */

  (void) strcpy (two, "hi there");
  (void) strcpy (one, two);
  equal (one, "hi there", 5);		/* Basic test encore. */
  equal (two, "hi there", 6);		/* Stomped on source? */

  (void) strcpy (one, "");
  equal (one, "", 7);			/* Boundary condition. */

  for (i = 0; i < 16; i++)
    {
      (void) strcpy (one + i, "hi there");	/* Unaligned destination. */
      equal (one + i, "hi there", 8 + (i * 2));
      (void) strcpy (two, one + i);		/* Unaligned source. */
      equal (two, "hi there", 9 + (i * 2));
    }

  SIMPLE_COPY(strcpy, 0, "", 41);
  SIMPLE_COPY(strcpy, 1, "1", 42);
  SIMPLE_COPY(strcpy, 2, "22", 43);
  SIMPLE_COPY(strcpy, 3, "333", 44);
  SIMPLE_COPY(strcpy, 4, "4444", 45);

  /* Simple test using implicitly coerced `void *' arguments.  */
  const void *src = "frobozz";
  void *dst = one;
  check (strcpy (dst, src) == dst, 46);
  equal (dst, "frobozz", 47);
}

static void
test_strcat (void)
{
  it = "strcat";
  (void) strcpy (one, "ijk");
  check (strcat (one, "lmn") == one, 1); /* Returned value. */
  equal (one, "ijklmn", 2);		/* Basic test. */

  (void) strcpy (one, "x");
  (void) strcat (one, "yz");
  equal (one, "xyz", 3);			/* Writeover. */
  equal (one+4, "mn", 4);			/* Wrote too much? */

  (void) strcpy (one, "gh");
  (void) strcpy (two, "ef");
  (void) strcat (one, two);
  equal (one, "ghef", 5);			/* Basic test encore. */
  equal (two, "ef", 6);			/* Stomped on source? */

  (void) strcpy (one, "");
  (void) strcat (one, "");
  equal (one, "", 7);			/* Boundary conditions. */
  (void) strcpy (one, "ab");
  (void) strcat (one, "");
  equal (one, "ab", 8);
  (void) strcpy (one, "");
  (void) strcat (one, "cd");
  equal (one, "cd", 9);
}

static void
test_strncat (void)
{
  /* First test it as strcat, with big counts, then test the count
     mechanism.  */
  it = "strncat";
  (void) strcpy (one, "ijk");
  check (strncat (one, "lmn", 99) == one, 1);	/* Returned value. */
  equal (one, "ijklmn", 2);		/* Basic test. */

  (void) strcpy (one, "x");
  (void) strncat (one, "yz", 99);
  equal (one, "xyz", 3);		/* Writeover. */
  equal (one+4, "mn", 4);		/* Wrote too much? */

  (void) strcpy (one, "gh");
  (void) strcpy (two, "ef");
  (void) strncat (one, two, 99);
  equal (one, "ghef", 5);			/* Basic test encore. */
  equal (two, "ef", 6);			/* Stomped on source? */

  (void) strcpy (one, "");
  (void) strncat (one, "", 99);
  equal (one, "", 7);			/* Boundary conditions. */
  (void) strcpy (one, "ab");
  (void) strncat (one, "", 99);
  equal (one, "ab", 8);
  (void) strcpy (one, "");
  (void) strncat (one, "cd", 99);
  equal (one, "cd", 9);

  (void) strcpy (one, "ab");
  (void) strncat (one, "cdef", 2);
  equal (one, "abcd", 10);			/* Count-limited. */

  (void) strncat (one, "gh", 0);
  equal (one, "abcd", 11);			/* Zero count. */

  (void) strncat (one, "gh", 2);
  equal (one, "abcdgh", 12);		/* Count and length equal. */

  (void) strncat (one, "ij", (size_t)-1);	/* set sign bit in count */
  equal (one, "abcdghij", 13);
}

static void
test_strncpy (void)
{
  /* Testing is a bit different because of odd semantics.  */
  it = "strncpy";
  check (strncpy (one, "abc", 4) == one, 1);	/* Returned value. */
  equal (one, "abc", 2);			/* Did the copy go right? */

  (void) strcpy (one, "abcdefgh");
  (void) strncpy (one, "xyz", 2);
  equal (one, "xycdefgh", 3);			/* Copy cut by count. */

  (void) strcpy (one, "abcdefgh");
  (void) strncpy (one, "xyz", 3);		/* Copy cut just before NUL. */
  equal (one, "xyzdefgh", 4);

  (void) strcpy (one, "abcdefgh");
  (void) strncpy (one, "xyz", 4);		/* Copy just includes NUL. */
  equal (one, "xyz", 5);
  equal (one+4, "efgh", 6);			/* Wrote too much? */

  (void) strcpy (one, "abcdefgh");
  (void) strncpy (one, "xyz", 5);		/* Copy includes padding. */
  equal (one, "xyz", 7);
  equal (one+4, "", 8);
  equal (one+5, "fgh", 9);

  (void) strcpy (one, "abc");
  (void) strncpy (one, "xyz", 0);		/* Zero-length copy. */
  equal (one, "abc", 10);

  (void) strncpy (one, "", 2);		/* Zero-length source. */
  equal (one, "", 11);
  equal (one+1, "", 12);
  equal (one+2, "c", 13);

  (void) strcpy (one, "hi there");
  (void) strncpy (two, one, 9);
  equal (two, "hi there", 14);		/* Just paranoia. */
  equal (one, "hi there", 15);		/* Stomped on source? */
}

static void
test_strlen (void)
{
  it = "strlen";
  check (strlen ("") == 0, 1);		/* Empty. */
  check (strlen ("a") == 1, 2);		/* Single char. */
  check (strlen ("abcd") == 4, 3);	/* Multiple chars. */
}

static void
test_strchr (void)
{
  it = "strchr";
  check (strchr ("abcd", 'z') == NULL, 1);	/* Not found. */
  (void) strcpy (one, "abcd");
  check (strchr (one, 'c') == one+2, 2);	/* Basic test. */
  check (strchr (one, 'd') == one+3, 3);	/* End of string. */
  check (strchr (one, 'a') == one, 4);		/* Beginning. */
  check (strchr (one, '\0') == one+4, 5);	/* Finding NUL. */
  (void) strcpy (one, "ababa");
  check (strchr (one, 'b') == one+1, 6);	/* Finding first. */
  (void) strcpy (one, "");
  check (strchr (one, 'b') == NULL, 7);		/* Empty string. */
  check (strchr (one, '\0') == one, 8);		/* NUL in empty string. */
}

static void
test_strrchr (void)
{
  it = "strrchr";
  check (strrchr ("abcd", 'z') == NULL, 1);	/* Not found. */
  (void) strcpy (one, "abcd");
  check (strrchr (one, 'c') == one+2, 2);	/* Basic test. */
  check (strrchr (one, 'd') == one+3, 3);	/* End of string. */
  check (strrchr (one, 'a') == one, 4);		/* Beginning. */
  check (strrchr (one, '\0') == one+4, 5);	/* Finding NUL. */
  (void) strcpy (one, "ababa");
  check (strrchr (one, 'b') == one+3, 6);	/* Finding last. */
  (void) strcpy (one, "");
  check (strrchr (one, 'b') == NULL, 7);	/* Empty string. */
  check (strrchr (one, '\0') == one, 8);	/* NUL in empty string. */
}

static void
test_memchr (void)
{
  it = "memchr";
  check(memchr("abcd", 'z', 4) == NULL, 1);	/* Not found. */
  (void) strcpy(one, "abcd");
  check(memchr(one, 'c', 4) == one+2, 2);	/* Basic test. */
  check(memchr(one, ~0xff|'c', 4) == one+2, 2);	/* ignore highorder bits. */
  check(memchr(one, 'd', 4) == one+3, 3);	/* End of string. */
  check(memchr(one, 'a', 4) == one, 4);	/* Beginning. */
  check(memchr(one, '\0', 5) == one+4, 5);	/* Finding NUL. */
  (void) strcpy(one, "ababa");
  check(memchr(one, 'b', 5) == one+1, 6);	/* Finding first. */
  check(memchr(one, 'b', 0) == NULL, 7);	/* Zero count. */
  check(memchr(one, 'a', 1) == one, 8);	/* Singleton case. */
  (void) strcpy(one, "a\203b");
  check(memchr(one, 0203, 3) == one+1, 9);	/* Unsignedness. */
}

static void
test_memcpy (void)
{
  int i;
  it = "memcpy";
  check(memcpy(one, "abc", 4) == one, 1);	/* Returned value. */
  equal(one, "abc", 2);			/* Did the copy go right? */

  (void) strcpy(one, "abcdefgh");
  (void) memcpy(one+1, "xyz", 2);
  equal(one, "axydefgh", 3);		/* Basic test. */

  (void) strcpy(one, "abc");
  (void) memcpy(one, "xyz", 0);
  equal(one, "abc", 4);			/* Zero-length copy. */

  (void) strcpy(one, "hi there");
  (void) strcpy(two, "foo");
  (void) memcpy(two, one, 9);
  equal(two, "hi there", 5);		/* Just paranoia. */
  equal(one, "hi there", 6);		/* Stomped on source? */

  for (i = 0; i < 5; i++)
    {
      const char *x = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
      strcpy (one, x);
      check (memcpy (one + i, "hi there", 9) == one + i,
	     7 + (i * 6));		/* Unaligned destination. */
      check (memcmp (one, x, i) == 0, 8 + (i * 6));  /* Wrote under? */
      equal (one + i, "hi there", 9 + (i * 6));
      check (one[i + 9] == 'x', 10 + (i * 6));       /* Wrote over? */
      check (memcpy (two, one + i, 9) == two,
	     11 + (i * 6));		/* Unaligned source. */
      equal (two, "hi there", 12 + (i * 6));
    }
}

static void
test_memset (void)
{
  int i;

  it = "memset";
  (void) strcpy(one, "abcdefgh");
  check(memset(one+1, 'x', 3) == one+1, 1);	/* Return value. */
  equal(one, "axxxefgh", 2);		/* Basic test. */

  (void) memset(one+2, 'y', 0);
  equal(one, "axxxefgh", 3);		/* Zero-length set. */

  (void) memset(one+5, 0, 1);
  equal(one, "axxxe", 4);			/* Zero fill. */
  equal(one+6, "gh", 5);			/* And the leftover. */

  (void) memset(one+2, 010045, 1);
  equal(one, "ax\045xe", 6);		/* Unsigned char convert. */

  /* Non-8bit fill character.  */
  memset (one, 0x101, 10);
  for (i = 0; i < 10; ++i)
    check (one[i] == '\01', 7);

}

int
main (int argc, char *argv[])
{
  int status;

  if( argc > 1 && argv[1][0] == '-' && argv[1][1] == 'v' && argv[1][2] == 0) // -v option
    verbose = 1;

  test_strlen();
  test_strcpy();
  test_strncpy();
  test_strcat();
  test_strncat();
  test_strchr();
  test_strrchr();
  test_memchr();
  test_memcpy();
  test_memset();

  if (errors == 0)
  {
    status = 0;
    puts("No errors.");
  }
  else
  {
    status = 1;
    printf("%zd errors.\n", errors);
  }

  return status;
}
