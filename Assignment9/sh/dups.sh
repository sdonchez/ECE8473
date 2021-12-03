#!/bin/dash
################################################################################
## S.Donchez
## dups.sh -  Write a shell script to find files with duplicate contents.
## Synopsis:
## dash dups.sh [path ...]
## Search the specified paths (default ".") for files whose contents are the 
## same.
## Output is a list of all file names found, with those having duplicate 
## contents listed together on the same line.
## The basic command to find files, assuming that the shell variable $paths 
## contains either "." or the paths specified as command-line arguments, is: 
## find $paths -type f -print. To find duplicates, use sha1sum and sort by hash.
## files.sh can be used to create some test files.
## Sample run:
## $ dash dups.sh F* Z*
## F1 Z1/F5
## F2 F3 Z1/Z2/F6
## F4
## $
################################################################################

################################################################################
## findFiles - finds all files matching the path(s) specified, or within the
##             current directory if no path is specified.
## @param $@      - the path(s) to search
## @sets  $files  - the list of files found
## @sets  $countF - the number of files found
################################################################################
findFiles()
{
    if [ "$#" -eq 0 ]
    
    #default case
    then
        files=$(find . -type f -print)

    #case where a path is specified
    else
        files=$(find "$@" -type f -print)
    fi #if/else
    countF=$(echo "$files" | wc -l)
} #findFiles

################################################################################
## processFiles - builds the arrays of file names and hashes
## @param $1      - the list of files to process
## @param $2      - the number of files to process
## @sets  $hashes - the list of hashes
## @sets  $both   - the list of files and their hashes
################################################################################
processFiles()
{
    i=1
    while [ "$i" -le "$2" ]
    do
        file=$(echo "$1" | sed -n "$i"p)
        sha1out=$(sha1sum "$file")
        hashes="$hashes$(echo "$sha1out"| cut -f 1 -d ' ')$newline"
        both="$both""$sha1out""$newline"
        i=$((i+1))
    done #while
} #processFiles

################################################################################
## getUniques - finds the number of unique hashes in the list of hashes
## @param $1      - the list of hashes
## @sets  $countU - the number of unique hashes
################################################################################
getUniques()
{
    countU=$(echo "$1" | sort | uniq -c| wc -l)
} #getUniques

################################################################################
## findDups - finds all of the duplicate files in the list of files and reports
##            the sets of duplicates.
## @param $1 - the number of unique files
## @param $2 - the number of total files
## @param $3 - the list of files and their hashes
################################################################################
findDups()
{
    i=1
    j=1
    #init list of files that have been found to be duplicates (so they don't
    #get reported again).
    skips=""

    #iterate at most through all the files (also needed for in order access)
    #give up once we've used all the unique hashes
    while [ "$j" -le "$1" ] && [ "$i" -le "$2" ]
    do
        extractLine $3

        #check if the file has already been found to be a duplicate, and skip it
        #if it has
        handled=$(echo "$skips" | grep "$name" -c)
        if [ "$handled" -eq 0 ]
            then
            matchLine "$hash" "$name" "$3"

            #only increment unique count if the file is a new hash
            j=$((j+1))
        fi #if

        #always increment the total count
        i=$((i+1))
    done #while
} #findDups

################################################################################
## extractLine - extracts the name and hash from the list of files and hashes
## @param $1 - the list of files and their hashes
## @sets  $name - the name of the file
## @sets  $hash - the hash of the file
################################################################################
extractLine()
{
    line=$(echo "$1" | sed -n "$i"p)   
    hash=$(echo "$line" | cut -f 1 -d ' ')
    name=$(echo "$line" | awk '{print $2}')
} #extractLine

################################################################################
## matchLine - finds all matching files for a given hash value
## @param $1     - the hash value to match
## @param $2     - the name of the file
## @param $3     - the list of files and their hashes
## @sets  $skips - the list of files that have already been found to be
##                 duplicates (so they don't get reported again)
################################################################################
matchLine()
{
    echo -n "$2 "

    #find all files with the same hash
    matches=$(echo -n "$3" | grep -F "$1"|awk '{print $2}')
    countM=$(echo "$matches" | wc -l)

    #iterate through file names matched
    p=1
    while [ "$p" -le "$countM" ]
    do
        match=$(echo "$matches" | sed -n "$p"p)

        #don't print the input file name again
        if [ "$match" != "$2" ]
        then
            echo -n "$match "
        fi #if

        #add the file to the list of files that have already been found to be
        #duplicates
        skips="$skips""$match"

        p=$((p+1))
    done #while
    echo ""
} #matchLine

 #because this is the only truly portable way I can find to do this
newline="
"
################################################################################
## Main Program
################################################################################
findFiles "$@"
processFiles "$files" "$countF"
getUniques "$hashes"
findDups "$countU" "$countF" "$both"
exit 0