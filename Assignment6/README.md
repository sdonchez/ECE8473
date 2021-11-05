# ECE 8473-DL1 Assignment 4

## [Assignment Details](https://fog.misty.com/perry/osp/a6/a6.html)
Upload source files - individual files or archive (e.g. zip, tar) - to the a4 upload area in your private course links.

Shell scripts must run correctly using dash.

C Programs must compile with no warnings or errors using: `gcc -std=c11 -pedantic -Wall`

Each source file must start with a comment containing your name and a description.

Input files are available in the a4-data/ directory of your private course link.

Reference: fortune

### __p1.c - Table Encrypt (50 points)__

 Write a C program to implement table encryption, described below. The program usage is:

  `./p1 [n] < plaintext > ciphertext `

where n is the table row length, default = 5.

The program must read all of standard input into a character array, remove all whitespace from the input, and then pad the input with 'o' characters if necessary to make the length a multiple of n. Then print the ciphertext followed by a single newline to standard output. 

### __p2.c - Table Decrypt (25 points)__

 Write a C program to implement table decryption. The program usage is:

  `./p2 [n] < ciphertext > plaintext`

where n is the table row length, default = 5.

The program must read all of standard input into a character array, and remove all whitespace from the input. Then print the plaintext followed by a single newline to standard output. 

###  __p3.sh - table decrypt, unknown n (25 points)__

Write a shell script which uses your program from part 2 to decrypt a ciphertext where n is unknown by trying all values from 2 to 20.

For each value of n, run your decrypt program and count how many valid words appear in the output. Sort the outputs in order of increasing number of valid words.

Use `fgrep -i -o -f words.txt` to search for matching words (words.txt was created by selecting words at least 4 characters long from the Solaris 5.10 spell check dictionary).  (50 points)__

### __Assignment Notes__

- Write functions for removing whitespace and adding the padding.

- Whitespace is any character for which isspace() from ctype.h returns true.

- Required error detection: for encrypt and decrypt, n ≤ 0; for decrypt, input length not a multiple of n. Return non-zero exit status and optionally print error message. 

## Directory Contents
- `bin/` - Executables for the above applications
- `data/` - copies of the test data provided by the assignment
- `env/` - Environment files for the IDE used to author the project (Microsoft Visual Studio 2019).
- `include/` - header file implementing custom user library (the encryption helper functions).
- `lib/` - compiled library outputs for the encryption helper functions.
- `obj/` - Intermediate files created by the build process.
- `sh/p3.sh/` - Shell script assigned as part 3 of the above
- `src/` - Source files implementing the specifications outlined above for parts 1 and 2.
- `Makefile` - Build file outlining dependencies for each executable.

## Build and Test Procedure
To build both executables (as well as the necessary custom library), execute `make all`.

To clean up all compilation products, execute `make clean`. 

## Notes
- All scripts have been tested and found to produce no warnings or errors with both GNU bash, version 5.0.17(1)-release (x86_64-pc-linux-gnu), and dash version 0.5.10.2-6.
- All C files were compiled using `gcc -std=c11 -pedantic -Wall` with gcc version 9.3.0 on WSL Ubuntu 20.04.