# ECE 8473-DL1 Assignment 3

## [Assignment Details](https://fog.misty.com/perry/osp/a3/a3.html)
Upload source files - individual files or archive (e.g. zip, tar) - to the a3 upload area in your private course links.

Shell scripts must run correctly using dash.

C Programs must compile with no warnings or errors using: `gcc -std=c11 -pedantic -Wall`

Each source file must start with a comment containing your name and a description.

### __Interactive Dealer and Player__

Write separate shell scripts which can be run interactively for the dealer and player parts of the random number guessing game from the previous assignment.

The player must take an optional command-line argument `-d` which causes it to display copies of its guesses and dealer responses to stderr, i.e. `echo "something..." 1>&2`

Once the scripts are working separately, run them together connected with a pipe and a named pipe (FIFO) so that the output from the player goes into the dealer, and the output of the dealer goes into the player. Run the player with `-d` option otherwise you won't see anything.

To create a FIFO named pipe: `mknod pipe p`
or: `mkfifo pipe`

Once the basic scripts are working, implement the following features:

-    Let the dealer take an optional command-line argument `-c` to turn on dealer "cheat" mode, to test the player response to dealer cheating.

-    Let the player take an optional command-line argument `-c` to turn on player "cheat" mode, so the player's first guess is always correct.

-    Let the dealer take an optional command-line argument `-s` to turn on dealer "secure" mode, to thwart player cheating. 

### __java.util.Random in C__

Write a C version of `rand.java` which produces identical output when run with the same command-line argument:
```
$ ls -C rand.*
rand.java
$ javac rand.java
$ ls -C rand.*
rand.class  rand.java
$ java rand ""
a = , init = 0, seed = 25214903917
-1155484576
-723955400
1033096058
-1690734402
-1557280266
1327362106
-1930858313
502539523
-1728529858
-938301587
$ java rand "A"
a = A, init = 65, seed = 25214903852
-1180493255
1368098006
1120652222
-1385156998
-1259499892
-1820793210
1712143702
1451474037
-1454981188
772491012
$ java rand "abcd12345"
a = abcd12345, init = 85517439386929, seed = 85499015603036
677047303
-1258808911
-39407339
-702359958
-1034100902
-119211861
2035536757
-516702251
1926036152
-197175227
```

## Directory Contents
- `bin/` - Executable implementing the Pseudo Random Number Generator (PRNG) outlined above.
- `env/` - Environment files for the IDE used to author the project (Microsoft Visual Studio 2019).
- `java/` - Reference file `rand.java` which serves as the basis for `rand.c`
- `obj/` - Intermediate files created by the build process.
- `src/` - Source file for the PRNG authored per the assignment requirements.
- `Makefile` - Build file outlining dependencies for each executable.

## Build and Test Procedures
All Part 1 files can be executed directly as written in either dash or bash.

Part 2 files can be compiled by executing `make all`. They can be tested with `make test`. Alternatively, each executable can be directly executed as desired.

## Notes
- All scripts have been tested and found to produce no warnings or errors with both GNU bash, version 5.0.17(1)-release (x86_64-pc-linux-gnu), and dash version 0.5.10.2-6.
- All C files were compiled using `gcc -std=c11 -pedantic -Wall` with gcc version 9.3.0 on WSL Ubuntu 20.04.