#!/bin/sh
################################################################################
## S.Donchez
## p3.sh - table decrypt, unknown n
## Write a shell script which uses your program from part 2 to decrypt a 
## ciphertext where n is unknown by trying all values from 2 to 20.
##
## for each value of n, run your decrypt program and count how many valid words 
## appear in the output. Sort the outputs in order of increasing number of valid
## words.
##
## Use fgrep -i -o -f words.txt to search for matching words (words.txt was 
## created by selecting words at least 4 characters long from the Solaris 5.10 
## spell check dictionary). 
################################################################################


#read input to variable
input=$(cat)

#init loop iterator to start value
i=2

#print header
echo "n, count, exit status, msg"

#loop through all desired values of n
while [ "$i" -le "20" ]
do

    #call decrypter
    msg=$(echo $input|../bin/p2 $i 2>/dev/null)

    #get exit code
    exitCode=$?

    #determine number of real words
    words=$(echo $msg|fgrep -i -o -f ../data/words.txt)
    count=$(echo $words|wc -w)

    #add result of current iteration to output
    log=$log"$i, $count, $exitCode, $msg\n"

    #increment iterator
    i=$((i+1))
done

#echo out sorted log
echo $log|sort -k2 -n