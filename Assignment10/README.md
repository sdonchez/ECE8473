# ECE 8473-DL1 Assignment 10

## [Assignment Details](https://fog.misty.com/perry/osp/a10/a10.html)
Upload source files - individual files or archive (e.g. zip, tar) - to the a4 upload area in your private course links.

Shell scripts must run correctly using dash.

C Programs must compile with no warnings or errors using: `gcc -std=c11 -pedantic -Wall`

Each source file must start with a comment containing your name and a description.

### __Multithreaded Mining__

Start with a copy of your villcoin mining program from the previous assignment, and modify it to perform the hash search in parallel using multiple threads. With 4 threads this should speedup the runtime by about a factor of 4 on systems having at least 4 cores.

Each thread must search a different subset of the nonce space. Once any thread finds a proper hash the program must stop all threads and exit. If no thread finds a proper hash, print an error message and exit.

See the notes on POSIX Threads. The recommended prototype is `pthread_pipe.c` with modifications to wait for any one thread success or all failed.

To collect your villcoin points for this assignment, include the program output in a file submitted with the source code showing results where the first four bytes of the hash are zero. 

## Directory Contents
- `bin/` - Executables for the above application
- `env/` - Environment files for the IDE used to author the project (Microsoft Visual Studio 2019).
- `log/villcoin.log` - villcoin executable log showing a VillCoin found with n=4 and confirmed via sha1sum
- `obj/` - Intermediate files created by the build process.
- `src/` - Source files implementing the specifications outlined above for part 1 above.
- `Makefile` - Build file outlining dependencies for each executable.

## Build and Test Procedure
To build the c executable execute `make`.

To clean up all compilation products, execute `make clean`. 

## Notes
- All scripts have been tested and found to produce no warnings or errors with both GNU bash, version 5.0.17(1)-release (x86_64-pc-linux-gnu), and dash version 0.5.10.2-6.
- All C files were compiled using `gcc -std=c11 -pedantic -Wall` with gcc version 9.3.0 on WSL Ubuntu 20.04.