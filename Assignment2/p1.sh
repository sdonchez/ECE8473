################################################################################
## S. Donchez
## a2/p1.sh -  Write a shell script which generates a 144-bit random
## value and writes it to standard output using a modified base-64 format (with 
## any '+' and '/' replaced with '-' and '.'). This is the type of value used 
## for the course private links.
##
## Use the basic Unix commands, and utilities from weeks #3-4. Use pipelines. 
## Do not use any loops and do not create any temporary files. Do not write any
## C code or invoke the compiler, and do not use awk, perl, or python. 
################################################################################

dd ibs=1 count=18 < /dev/urandom  2> /dev/null | base64 | tr '+/' '-.'

## dd lets us pull just 18 bytes
## /dev/urandom gives pseudo-random values
## 2> /dev/null throws away unwanted statistical info that is printed to stderr
## base64 converts the bytes to base 64
## tr substitutes + and / with - and . respectivelyd