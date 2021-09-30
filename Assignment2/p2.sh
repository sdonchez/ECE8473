################################################################################
## S.Donchez 
## a2/p2.sh -  Write a shell script which generates n random 16-bit values. The 
## number of values n to generate comes from the command-line argument $1 if 
## present, otherwise use n=1000.
##
## Initially just display the generated values in hex to standard output. Then
## modify the script to use sort and uniq to display the number of collisions 
## (repeated values) and colliding values, sorted in increasing number of 
## occurrences.
##
## Use the basic Unix commands, and utilities from weeks #3-4. Use pipelines. 
## Do not use any loops and do not create any temporary files. Do not write any
## C code or invoke the compiler, and do not use awk, perl, or python. 
################################################################################

#default number of values to generate is 1000
num=1000

#if there's a passed argument, set it as the number of values to generate
if [ $# -ne 0 ];
then
    num=$1
fi # if

## generate the output (see below)
dd ibs=2 count=${num} < /dev/urandom 2> /dev/null| od -x -An| cut -b2-|
tr ' ' '\n'|sort|uniq -c|sort

#dd to get values from /dev/urandom
    #ibs=2 chunks the random data into 2 byte blocks
    #count generates the requested number of values
    #redirect stderr to the null device to get rid of statistical data
#od to convert data to hex (-od), without addresses (-An)
#cut to get rid of the empty space at the beginning of the od output
#tr to convert spaces in od output to newlines (so we get one per line)
#sort to sort the values so that unique can find duplicates
#uniq to find duplicates
    #-c to indicate how many duplicates are found
#sort (again) to sort by number of duplicates