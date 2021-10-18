# ECE 8473-DL1 Assignment 5.2

## [Assignment Details](https://fog.misty.com/perry/osp/a5.2/a5.2.html)
Upload source files - individual files or archive (e.g. zip, tar) - to the a5.2 upload area in your private course links.

Programs must compile with no warnings or errors using: `gcc -std=c11 -pedantic -Wall`

Each source file must start with a comment containing your name and a description.
Declarations for the examples: `char s[BUFSIZ], *p;`

### Implement the following string functions and main test program: (20 pts)

#### __`char *strdog( const char s1[], char s2[])`__

Prepends s1 to s2 and returns s2.

A relative of strcat, strdog inserts s1 at the beginning of s2. It does this by moving the characters of s2 over to make room for s1, then copying the characters from s1 into the beginning of s2.

Example:

`strcpy( s, "efg"); p = strdog( "abc", s);`

`s` now contains "abcefg" and `p == s`.

Do not use any temporary arrays (no extra static, auto, or dynamic arrays).

Do not use any loops; use functions from `string.h` to perform the operations.

#### __`char *strrm( char s1[], const char s2[])`__

Removes the set of s2 characters from s1 and returns s1.

Example:

`strcpy( s, "AABZBAADZDAA"); p = strrm( s, "ZA");`

`s` now contains "BBDD" and `p == s.`

Do not use any temporary arrays (no extra static, auto, or dynamic arrays).

#### __`char *strcrm( char s1[], const char s2[])`__

Removes the complement of the set of s2 characters from s1 and returns s1.

The "complement of s2" consists of all characters which are not contained in s2.

Example:

`strcpy( s, "AABZBAADZDAA"); p = strcrm( s, "ZA");`

`s` now contains "AAZAAZAA" and `p == s`.

Do not use any temporary arrays (no extra static, auto, or dynamic arrays).

#### __main__

Write a main program which performs one non-trivial test for each of the string functions above, checks the result and return value, and indicates whether the function passed or failed the test. 

## Directory Contents
- `bin/tester` - Executable for the test suite
- `env/` - Environment files for the IDE used to author the project (Microsoft Visual Studio 2019).
- `include/strfxns.h` - header files implementing custom user library for the non-standard string functions
- `lib/libstrfxns.a` - compiled library outputs for the non-standard string functions
- `obj/` - Intermediate files created by the build process.
- `src/` - Source files implementing the specifications outlined above.
- `Makefile` - Build file outlining dependencies for each executable.

## Build and Test Procedure
To build both the library and the testsuite executable (as well as the necessary custom libraries), execute `make all`.

To run all three decryption routines, execute `make test`.

The library can be built without building the testsuite by executing `make library`

To clean up all compilation products, execute `make clean`.

## Notes
- All C files were compiled using `gcc -std=c11 -pedantic -Wall` with gcc version 9.3.0 on WSL Ubuntu 20.04.