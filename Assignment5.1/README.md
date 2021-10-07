# ECE 8473-DL1 Assignment 5.1

## [Assignment Details](https://fog.misty.com/perry/osp/a5.1/a5.1.html)
Upload source files - individual files or archive (e.g. zip, tar) - to the a5.1 upload area in your private course links.

Programs must compile with no warnings or errors using: gcc -std=c11 -pedantic -Wall

Each source file must start with a comment containing your name and a description.
### string.h functions (80 points)

For each of the functions in string.c rewrite the initial implementation so that the provided test program tester.c encounters no errors.

The functions are from the C library string.h but with name prefix my_ so they won't interfere with use of the standard functions.

The test program was adapted from the GNU C library glibc-2.34/string/tester.c

Do not use any temporary arrays (no extra static, auto, or dynamic arrays).

For each function, the implementation must be self-contained and may not invoke any other functions.

Sample runs:
```
$ make
gcc -std=c11 -pedantic -Wall -g -c tester.c
gcc -std=c11 -pedantic -Wall -g -c string.c
gcc -std=c11 -pedantic -Wall -g -o tester tester.o string.o
$ ./tester | tail -2
memset flunked test 7
165 errors.
$ ./tester -v | grep passed
strlen passed test 1
strcpy passed test 7
strchr passed test 1
strchr passed test 7
strrchr passed test 1
strrchr passed test 7
memchr passed test 1
memchr passed test 7
memcpy passed test 8
$ make system
gcc -std=c11 -pedantic -Wall -g -w -o system -DSYSTEM tester.c
$ ./system
No errors.
$ 
```

## Directory Contents
- `bin/` - Executables for the above applications.
- `env/` - Environment files for the IDE used to author the project (Microsoft Visual Studio 2019).
- `obj/` - Intermediate files created by the build process.
- `src/` - Source files implementing the specifications outlined above.
- `Makefile` - Build file outlining dependencies for each executable.

## Build and Test Procedure
To build both the system and custom test implementations, execute `make`. The tester for the custom libraries only can be built with `make tester`, and the system libraries with `make system`.

To clean up all compilation products, execute `make clean`.

## Notes
- All C files were compiled using `gcc -std=c11 -pedantic -Wall` with gcc version 9.3.0 on WSL Ubuntu 20.04.
- Makefile has been updated to accommodate directory structure.