# ECE 8473-DL1 Assignment 9

## [Assignment Details](https://fog.misty.com/perry/osp/a9/a9.html)
Upload source files - individual files or archive (e.g. zip, tar) - to the a4 upload area in your private course links.

Shell scripts must run correctly using dash.

C Programs must compile with no warnings or errors using: `gcc -std=c11 -pedantic -Wall`

Each source file must start with a comment containing your name and a description.

### __VillCoin Mining__

Similar to bitcoin, VillCoin is Villanova's digital cryptocurrency, which can be cashed in for points on a course assignment. To achieve maximum points on this assignment you must mine a VillCoin such that the first four bytes of the hash are zero.

Write a C program using `SHA1()` to create a VillCoin with n leading zero bytes, where `n` is an optional command-line argument, with default `n=1`.

A VillCoin consists of a data string and a hash. The hash is `SHA1(data)` in hex. The data string is a concatenation of your userid, a 32-bit random value from `rand()`, and a 32-bit nonce. The random value is set just once at the beginning of `main()`.

Mining consists of finding a nonce so that the first `n` bytes of the resulting hash are zero. Start with nonce=0 and keep incrementing until a proper hash is found; if the nonce wraps around back to 0 without success, print an error message and exit.

The exact format of the data string and program output is up to you, but the program output should not be excessive (don't show all 4 billion possible hashes) and the final output must show the data string and hash so that the result can be confirmed using `openssl sha1` or `sha1sum`.

To collect your VillCoin assignment points, include the program output in a file submitted with the source code.

### __Find Duplicates__

Write a shell script to find files with duplicate contents.

Synopsis:

  `dash dups.sh [path ...]`

Search the specified paths (default "`.`") for files whose contents are the same.
Output is a list of all file names found, with those having duplicate contents
listed together on the same line.

The basic command to find files, assuming that the shell variable `$paths` contains either "`.`" or the paths specified as command-line arguments, is: `find $paths -type f -print`. To find duplicates, use `sha1sum` and sort by hash.

`files.sh` can be used to create some test files.

Sample run:
```
$ dash dups.sh F* Z*
F1 Z1/F5
F2 F3 Z1/Z2/F6
F4
$
```

## Directory Contents
- `bin/` - Executables for the above application
- `data/` - copies of the test files generated by `/sh/files.sh`
- `env/` - Environment files for the IDE used to author the project (Microsoft Visual Studio 2019).
- `log/villcoin.log` - villcoin executable log showing a VillCoin found with n=4 and confirmed via sha1sum
- `obj/` - Intermediate files created by the build process.
- `sh/dups.sh/` - Shell script assigned as part 2 of the above
- `sh/files.sh/` - Shell script provided to generate test files
- `src/` - Source files implementing the specifications outlined above for part 1 above.
- `Makefile` - Build file outlining dependencies for each executable.

## Build and Test Procedure
To build the c executable execute `make`.

To clean up all compilation products, execute `make clean`. 

## Notes
- All scripts have been tested and found to produce no warnings or errors with both GNU bash, version 5.0.17(1)-release (x86_64-pc-linux-gnu), and dash version 0.5.10.2-6.
- All C files were compiled using `gcc -std=c11 -pedantic -Wall` with gcc version 9.3.0 on WSL Ubuntu 20.04.