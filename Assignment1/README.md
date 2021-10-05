# ECE 8473-DL1 Assignment 1

## [Assignment Details - Part 1](http://fog.misty.com/perry/osp/a1/a1.1.html)

Upload source files - individual files or archive (e.g. zip, tar) - to the a1 upload area in your private course links.

Programs must compile with no warnings or errors using:

  `gcc -std=c11 -pedantic -Wall`

Each source file must start with a comment containing your name and a description.

References: `limits.h`, `float.h`, `printf` format list

### __a1/p1.c - limits.h__

Write a C program which displays the names and values of the following constants from `limits.h`:

    CHAR_BIT, CHAR_MIN, CHAR_MAX, SCHAR_MIN, SCHAR_MAX, UCHAR_MAX

    SHRT_MIN, SHRT_MAX, USHRT_MAX

    INT_MIN, INT_MAX, UINT_MAX

    LONG_MIN, LONG_MAX, ULONG_MAX

    LLONG_MIN, LLONG_MAX, ULLONG_MAX 

and also computes at run-time (without using any predefined constants or assumptions) and displays the value of `ULONG_MAX`.

### __a1/p2.c - float.h__

Write a C program which displays the names and values of the following constants from `float.h`:

    FLT_MIN, FLT_TRUE_MIN, FLT_MAX, FLT_EPSILON

    DBL_MIN, DBL_TRUE_MIN, DBL_MAX, DBL_EPSILON

    LDBL_MIN, LDBL_TRUE_MIN, LDBL_MAX, LDBL_EPSILON

and also computes at run-time (without using any predefined constants or assumptions) and displays the value of DBL_EPSILON.

The machine precision `ε = DBL_EPSILON` is defined as the smallest double such that `1.0 + ε > 1.0, i.e. 1.0 + ε/2.0 == 1.0` 

## [Assignment Details - Part 2](http://fog.misty.com/perry/osp/a1/a1.2.html)
Upload source files - individual files or archive (e.g. zip, tar) - to the a1 upload area in your private course links.

Programs must compile with no warnings or errors using:

  `gcc -std=c11 -pedantic -Wall`

Each source file must start with a comment containing your name and a description.

References: `errno.h`, `tgmath.h`, `perror`, `strerror`, strerror notes

### __a1/p3.c - sqrt(-1)__

Write a C program which computes and displays the value of `sqrt(-1)`. Include `<errno.h>` and after calling `sqrt()` display the value of errno and also call `perror()`.

Also compute and display the value of some `tgmath.h` function (your choice) with a valid input which produces a range error, i.e. overflow. Display the value of errno and also call `perror()`.

### __a1/p4.c - error message list__

Write a C program which uses `strerror()` to get the error message associated with errno values from 0 to 200. Display each error number and message. Be careful to check for errors in the `strerror()` call and possible `NULL` return values. 

## Directory Contents
- `bin/` - Executables corresponding to each of the source files outlined above, named correspondingly.
- `env/` - Environment files for the IDE used to author the project (Microsoft Visual Studio 2019).
- `obj/` - Intermediate files created by the build process.
- `src/` - Source files authored per the assignment requirements.
- `Makefile` - Build file outlining dependencies for each executable.

## Build and Test Procedures
Executable files can be compiled by executing `make all`. They can be tested with `make test`. Alternatively, each executable can be directly executed as desired.

## Notes
- All files were compiled using `gcc -std=c11 -pedantic -Wall` with gcc version 9.3.0 on WSL Ubuntu 20.04.