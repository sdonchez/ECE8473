# ECE 8473-DL1 Assignment 2

## [Assignment Details](https://fog.misty.com/perry/osp/a2/a2.html)

Upload source files - individual files or archive (e.g. zip, tar) - to the a2 upload area in your private course links.

Shell scripts must run correctly using dash.

Each script must start with a comment containing your name and a description.

Reference: Weeks #3-4 utilities

### __a2/p1.sh - random private link value__

Write a shell script which generates a 144-bit random value and writes it to standard output using a modified base-64 format (with any `+` and `/` replaced with `-` and `.`). This is the type of value used for the course private links.

Use the basic Unix commands, and utilities from weeks #3-4. Use pipelines. Do not use any loops and do not create any temporary files. Do not write any C code or invoke the compiler, and do not use `awk`, `perl`, or `python`.

Sample runs:

    $ dash p1.sh
    pmJR3tXdaohHZ.TgWJ8YqTcA
    $ dash p1.sh
    nA78NZgTtLX3gKx-IlryyP3l
    $ dash p1.sh
    v9uDY702Ji8qRs0iGe8OlIit
    $ dash p1.sh
    JqLzM0P-Xh5QfpZ9y.DSJYjQ
    $

### __a2/p2.sh - random collisions__

Write a shell script which generates n random 16-bit values. The number of values `n` to generate comes from the command-line argument `$1` if present, otherwise use `n=1000`.

Initially just display the generated values in hex to standard output. Then modify the script to use sort and uniq to display the number of collisions (repeated values) and colliding values, sorted in increasing number of occurrences.

Use the basic Unix commands, and utilities from weeks #3-4. Use pipelines. Do not use any loops and do not create any temporary files. Do not write any C code or invoke the compiler, and do not use `awk`, `perl`, or `python`.

Sample runs:

    $ dash p2.sh 5
        1 2af1
        1 4517
        1 496e
        1 9a70
        1 c976
    $ dash p2.sh | tail -n 3
        2 c1c5
        2 ef1c
        2 fc35
    $ dash p2.sh | tail -n 3
        1 ffc8
        2 a495
        2 eb1e
    $

### __a2/p3.sh - random number guessing game__

Write a shell script which plays both parts (dealer and player) of the random number guessing game and displays the results.

In this game the dealer chooses a random integer in the range `[1,100]` and the player uses a binary search to try to guess the value. The binary search uses two limits, low and high delimiting the range of values remaining to be searched. Initially, `low=0` and `high=101`. The player's guess is always `guess=(low+high)/2`.

For each guess the dealer responds by indicating whether the correct answer is "higher" or "lower" then the guess, or that the guess is "correct". If the correct answer is higher, the player sets low=guess; if the correct answer is lower, the player sets high=guess; otherwise the guess is correct and the game is over. If the dealer provides an inconsistent response the player should notice that high-low<2 and in that case declare that the dealer is cheating and the game is over.

It is recommended to use a shell function to implement the dealer checking the player's guess, and implement the player in the main part of the script.

Use only built-in shell commands and arithmetic. Use shell variables and a loop. Do not use any external programs, utilities, or files, except for this awk command to generate the initial random integer:

`answer=$(echo hi | awk '{ srand(); print int(1+100*rand()); }')`

Note that `awk srand()` is equivalent to C `srand(time(0))`, and `awk rand()` is equivalent to C `rand()/(RAND_MAX+1.0)`

Sample runs:

    $ dash p3.sh
    guess = 50, higher
    guess = 75, lower
    guess = 62, higher
    guess = 68, lower
    guess = 65, correct!
    $ dash p3.sh
    guess = 50, lower
    guess = 25, lower
    guess = 12, lower
    guess = 6, higher
    guess = 9, correct!
    $ dash p3.sh
    guess = 50, higher
    guess = 75, lower
    guess = 62, lower
    guess = 56, lower
    guess = 53, lower
    guess = 51, lower
    Dealer is cheating, I quit!
    $

## Directory Contents
- Shell Scripts - 3 shell scripts corresponding to the requirements outlined above, named accordingly.

## Build and Test Procedures
All shell scripts can be directly executed in either dash or bash.

## Notes
- All scripts have been tested and found to produce no warnings or errors with both GNU bash, version 5.0.17(1)-release (x86_64-pc-linux-gnu), and dash version 0.5.10.2-6.