# ECE 8473-DL1 Assignment 4

## [Assignment Details](https://fog.misty.com/perry/osp/a4/a4.html)
Upload source files - individual files or archive (e.g. zip, tar) - to the a4 upload area in your private course links.

Shell scripts must run correctly using dash.

C Programs must compile with no warnings or errors using: `gcc -std=c11 -pedantic -Wall`

Each source file must start with a comment containing your name and a description.

Input files are available in the a4-data/ directory of your private course link.

Reference: fortune

### __CBC decrypt (20 points)__

Your `a4-data/CBC.bin` file contains a secret message encrypted using Cipher Block Chaining.

The CBC pseudo-random numbers were obtained using nextInt() from the previous assignment, initialized with your userid, e.g. `initialScramble(hashCode("alice"));` (replace alice with your userid)

Write a C program using `getchar()` and `putchar()`, similar to `getchar.c`, to perform CBC decryption so you can read the secret message.

At the end of the message there is a confirmation code which must be submitted to prove that your program worked. The submission address is shown in your private course links.

### __Substitution Cipher (30 points)__

Your `a4-data/subs.txt` file contains a secret message encrypted using a substitution cipher.

Decrypt using `subs.sh` after changing the substitution table to correspond to your userid.

Example

Write a C program to compute your substitution table using the following algorithm to shuffle (permute) the set of characters `A...Z0...9`:

    initialScramble(hashCode("alice")); // replace alice with your userid

    char a[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    for n = 36, 35, ..., 2  // strlen(a) downto 2
    
    unsigned int i = nextInt();  i = i % n;  // i = random index from 0 to n-1

    swap a[i] and a[n-1]

At the end of the message there is a confirmation code which must be submitted to prove that your program worked. The submission address is shown in your private course links.

###  __Transposition Cipher (50 points)__

Your `a4-data/trans.bin` file contains a secret message encrypted with a transposition cipher using `trans.c`.

Write a C program using `fread()` and `fwrite()`, similar to `trans.c`, to perform decryption so you can read the secret message.

At the end of the message there is a confirmation code which must be submitted to prove that your program worked. The submission address is shown in your private course links. 

## Directory Contents
- `bin/` - Executables for the above applications
- `data/` - copies of the encrypted data hosted in the `a4-data/` directory.
- `env/` - Environment files for the IDE used to author the project (Microsoft Visual Studio 2019).
- `include/` - header files implementing custom user libraries (the PRNG from assignment 3 and a simple swap function).
- `lib/` - compiled library outputs for the PRNG and swap functions.
- `log/a4-check.log` - contents of the a4-check private link demonstrating successful decryption.
- `obj/` - Intermediate files created by the build process.
- `sh/subs.sh` - `subs.sh` file as provided to perform the substitution cipher operations.
    - Note: this file is unmodified, it does not contain the output of the substitution executable. See "testing" below.
- `sh/doSubs.sh` - test script that substitutes the output of the substitution executable into `subs.sh`, and then calls it to perform the substitution.
- `src/` - Source files implementing the specifications outlined above.
- `Makefile` - Build file outlining dependencies for each executable.

## Build and Test Procedure
To build all three executables (as well as the necessary custom libraries), execute `make all`.

To run all three decryption routines, execute `make test`.

The `CBCDecrypt` and `TransCipher` executables can be directly executed to provide the decrypted output. The `SubsCipher` executable doesn't provide the decrypted output, only the cipher key. To generate the decrypted output, execute `make  testSubs`, which will execute the `sh/doSubs.sh` script to automate the editing and execution of `subs.sh` from the output of `SubsCipher`.

To clean up all compilation products, execute `make clean`. __Note: This will also reset the contents of `sh\subs.sh` to their original state.__

## Notes
- All scripts have been tested and found to produce no warnings or errors with both GNU bash, version 5.0.17(1)-release (x86_64-pc-linux-gnu), and dash version 0.5.10.2-6.
- All C files were compiled using `gcc -std=c11 -pedantic -Wall` with gcc version 9.3.0 on WSL Ubuntu 20.04.