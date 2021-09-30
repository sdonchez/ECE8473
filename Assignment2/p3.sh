################################################################################
## S.Donchez 
## a2/p3.sh -   Write a shell script which plays both parts (dealer and player)
## of the random number guessing game and displays the results.
##
## In this game the dealer chooses a random integer in the range [1,100] and the
## player uses a binary search to try to guess the value. The binary search uses
## two limits, low and high delimiting the range of values remaining to be 
## searched. Initially, low=0 and high=101. The player's guess is always 
## guess=(low+high)/2.
##
## For each guess the dealer responds by indicating whether the correct answer 
## is "higher" or "lower" then the guess, or that the guess is "correct". If the
## correct answer is higher, the player sets low=guess; if the correct answer is
## lower, the player sets high=guess; otherwise the guess is correct and the 
## game is over. If the dealer provides an inconsistent response the player 
## should notice that high-low<2 and in that case declare that the dealer is 
## cheating and the game is over.
##
## It is recommended to use a shell function to implement the dealer checking 
## the player's guess, and implement the player in the main part of the script.
##
## Use only built-in shell commands and arithmetic. Use shell variables and a 
## loop. Do not use any external programs, utilities, or files, except for this 
## awk command to generate the initial random integer:
##
##  answer=$(echo hi | awk '{ srand(); print int(1+100*rand()); }')
##
## Note that awk srand() is equivalent to C srand(time(0)), and awk rand() is 
## equivalent to C rand()/(RAND_MAX+1.0)
###############################################################################

# generate a random answer between 1 and 100 for the "player" to guess
answer=$(echo hi | awk '{ srand(); print int(1+100*rand()); }')

# setup inital bounds
low=0
high=101
range=$((${high} - ${low}))


################################################################################
## checkGuess - checks the player's guess and returns a value indicating if the
##              guess was higher or lower than the answer.
##
## @param $1 -  values guessed by the player
## @returns     0 - if the player guessed correctly
##              1 - if the player's guess was too low
##              2 - if the player's guess was too high
################################################################################
checkGuess(){
    guess=$1
    # if the guess equals the answer, the player wins!
    if [ ${guess} -eq ${answer} ];
    then
        echo "correct!"
        direction=0

    # if the guess is less than the answer, check the right half of the tree
    #   on the next iteration
    elif [ ${guess} -lt ${answer} ];
    then
        echo "higher"
        direction=1

    # otherwise check the left half
    else
        echo "lower"
        direction=2
    fi #if/elif/else
}

# while the dealer isn't cheating, keep playing
while [ $range -ge 2 ]
do
    # guess the middle of the current range of values
    guess=$(((${low} + ${high})/2))

    # echo without a newline so we can append the result
    echo -n "guess = ${guess}, "

    checkGuess ${guess}

    # check the result of the function call and adjust limits accordingly
    if [ ${direction} -eq 1 ];
    then
        low=${guess}
    elif [ ${direction} -eq 2 ];
    then
        high=${guess}

    # or exit if we guessed right
    else
        exit 0
    fi # if/elif/else
    #recalculate the range so we can ensure the dealer isn't cheating
    range=$((${high} - ${low}))
done # while

#if we break the loop without exiting, the dealer is cheating!
echo "Dealer is cheating, I quit!"
exit -1