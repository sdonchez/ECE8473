# ECE 8473-DL1 Assignment 7

## [Assignment Details](https://fog.misty.com/perry/osp/a7/a7.html)
Upload source files - individual files or archive (e.g. zip, tar) - to the a7 upload area in your private course links.

C programs must compile with no warnings or errors using: gcc -std=c11 -pedantic -Wall

Shell scripts must run correctly using dash.

Each source file must start with a comment containing your name and a description. 

### __p1.c - Basic Grep__

Write a program, similar to grep, using regcomp() and regexec() to search for a regular expression pattern in lines read from standard input using fgets().

Program synopsis:

  `./p1 pattern`

  Simple search for regular expression pattern in lines from standard input.

  Exit status:

    0  One or more matches were found
    1  No matches were found
    2  Syntax error in pattern

Use regcomp flags: REG_NEWLINE | REG_NOSUB

Test using [test1.sh](./sh/test1.sh). 

### __p2.c - Extended Grep__

Start with a copy of your program from part 1 and enhance it to accept command-line options according to the following synopsis:

  `./p2 [-1] [-E|-F] [-v] pattern`
 
  Options:
 
    -1  stop after first match
    -E  pattern is an extended regular expression
    -F  pattern is a fixed string
    -v  print lines which do not contain the pattern

Note that the `-E` and `-F` options are mutually exclusive.

For the `-E` option, include `REG_EXTENDED` in the regcomp flags.

For the `-F` option, use `strstr()` instead of the regular expression matching functions.

Test using [test2.sh](./sh/test2.sh). 

## Directory Contents
- `bin/` - Executables for the above applications
- `env/` - Environment files for the IDE used to author the project (Microsoft Visual Studio 2019).
- `obj/` - Intermediate files created by the build process.
- `sh/` - test scripts provided with the assignment.
- `src/` - Source files implementing the specifications outlined above for parts 1 and 2.
- `Makefile` - Build file outlining dependencies for each executable.

## Build and Test Procedure
To build both executables, execute `make all`.

To clean up all compilation products, execute `make clean`. 

To run both test scripts, execute `make test`.

## Notes
- All scripts have been tested and found to produce no warnings or errors with both GNU bash, version 5.0.17(1)-release (x86_64-pc-linux-gnu), and dash version 0.5.10.2-6.
- All C files were compiled using `gcc -std=c11 -pedantic -Wall` with gcc version 9.3.0 on WSL Ubuntu 20.04.