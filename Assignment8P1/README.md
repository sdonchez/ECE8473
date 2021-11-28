# ECE 8473-DL1 Assignment 8 Part 1

## [Assignment Details](https://fog.misty.com/perry/osp/a8.1/a8.1.html)
Upload source files - individual files or archive (e.g. `zip`, `tar`) - to the a8.1 upload area in your private course links.

C programs must compile with no warnings or errors using: `gcc -std=c11 -pedantic -Wall`

Shell scripts must run correctly using dash.

Each source file must start with a comment containing your name and a description. 

### __b2.c - Simulation Using Two Classical Bits (30 points)__

Write a C program using an array of two integers to simulate computations on two classical bits.

Implement the following two functions:

  `void X( int b[], int k) // NOT on bit k`

  `void CX( int b[], int c, int k) // controlled-NOT on bit k controlled by bit c`

The controlled-NOT performs a NOT on bit k only if bit c is 1.

Assume that `c,k ∈ {0,1}` and `c ≠ k`. Error checking is not required.

In the main program, perform an exhaustive test using all possible combinations of bit values and function calls. For each function call, perform the operation twice; the output should show that the second call undoes the first since these functions are their own inverses.

The program does not have to check the results, just display the results.

## Directory Contents
- `bin/` - Executables for the above applications
- `env/` - Environment files for the IDE used to author the project (Microsoft Visual Studio 2019).
- `obj/` - Intermediate files created by the build process.
- `src/` - Source files implementing the specifications outlined above
- `Makefile` - Build file outlining dependencies for each executable.

## Build and Test Procedure
To build the executables, execute `make`.

To clean up all compilation products, execute `make clean`. 

## Notes
- All scripts have been tested and found to produce no warnings or errors with both GNU bash, version 5.0.17(1)-release (x86_64-pc-linux-gnu), and dash version 0.5.10.2-6.
- All C files were compiled using `gcc -std=c11 -pedantic -Wall` with gcc version 9.3.0 on WSL Ubuntu 20.04.