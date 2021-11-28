# ECE 8473-DL1 Assignment 8 Part 2

## [Assignment Details](https://fog.misty.com/perry/osp/a8.2/a8.2.html)
Upload source files - individual files or archive (e.g. `zip`, `tar`) - to the a8.2 upload area in your private course links.

C programs must compile with no warnings or errors using: `gcc -std=c11 -pedantic -Wall`

Shell scripts must run correctly using dash.

Each source file must start with a comment containing your name and a description. 

### __p2.c - Simulation Using Two Quantum Bits (70 points)__

 Write a C program using an array of four doubles to simulate computations on two quantum bits.

Implement the following four functions:

  `void X( double a[], int k) // NOT on qubit k`

  `void CX( double a[], int c, int k) // controlled-NOT on qubit k controlled by qubit c`

 `void Z( double a[], int k) // phase-flip on qubit k`

  `void H( double a[], int k) // Hadamard on qubit k`

Assume that `c,k ∈ {0,1}` and `c ≠ k`. Error checking is not required.

In the main program, first initialize the amplitudes to distinct values, e.g.

  `double s30 = 1/sqrt(30), a[4] = { 1*s30, 2*s30, 3*s30, 4*s30 };`

then test using all possible function calls. For each function call, perform the operation twice; the output should show that the second call undoes the first since these functions are their own inverses.

The program does not have to check the results, just display the results.

Then the main program must reset the amplitudes to `{ 1, 0, 0, 0 `} and perform a superdense coding simulation. The value to be encoded (`default = 0`) comes from the command-line `argv[1]` if present. Show the intermediate state amplitude values after each operation. 

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