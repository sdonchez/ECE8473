################################################################################
## S.Donchez
## a3/dealer.sh -   Write separate shell scripts which can be run interactively 
##                  for the dealer and player parts of the random number 
##                  guessing game from the previous assignment. 
##
##                  Once the scripts are working separately, run them together 
##                  connected with a pipe and a named pipe (FIFO) so that the 
##                  output from the player goes into the dealer, and the output 
##                  of the dealer goes into the player. Run the player with -d 
##                  option otherwise you won't see anything. 
##
##                  Once the basic scripts are working, implement the following 
##                  features:
##
##                  Let the dealer take an optional command-line argument -c to 
##                  turn on dealer "cheat" mode, to test the player response to 
##                  dealer cheating.
##
##                  Let the dealer take an optional command-line argument -s to 
##                  turn on dealer "secure" mode, to thwart player cheating.
################################################################################

################################################################################
## parseOps - parses options passed into program and sets flags accordingly
##
## @param   $@ - all parameters passed to function, to be looped through
## @sets    $c_flag - if the param "-c" was passed.
## @sets    $s_flag - if the param "-s" was passed.
## @note    also supports multiple params passed with a single - (i.e. -cs)
################################################################################
parseOps(){
    #set flags to false by default, then check if they are passed in
    c_flag=false
    s_flag=false
    for var in $@
    do
        if [ "$var" = "-c" ];
        then
            c_flag=true
        elif [ "$var" = "-s" ];
        then
            s_flag=true

        #allow concatenated params per the POSIX convention    
        elif [ "$var" = "-cs" ] || [ "$var" = "-sc" ];
        then
            c_flag=true
            s_flag=true
        fi #if/elif/elif
    done #for
} #parseOps

################################################################################
## generateValue -  generates the answer value for the player to check.
##
## @param $1        boolean that indicates if the dealer shoud use secure mode
## @sets            $answer to a random value between 1 and 100
################################################################################
generateValue(){
    #if secure flag is true, generate a truly pseudo-random number
    if [ $1 = true ];
    then 
        answer=$(dd ibs=1 count=1 < /dev/urandom 2> /dev/null|od -d -An|cut -b2-)
        answer=$((answer % 100 + 1))

    #otherwise use Awk, which the player can replicate
    else
        answer=$(echo hi | awk '{ srand(); print int(1+100*rand()); }')
    fi #if/else

} #generateValue


################################################################################
## checkGuess - checks the player's guess and returns a value indicating if the
##              guess was higher or lower than the answer.
##
## @param $1    values guessed by the player
## @echoes      "correct" - if the player guessed correctly
##              "higher" - if the player's guess was too low
##              "lower" - if the player's guess was too high
## @sets        $done to true if the player guessed correctly
################################################################################
checkGuess(){
    guess=$1
    # if the guess equals the answer, the player wins!
    if [ ${guess} -eq ${answer} ];
    then
        echo "correct"
        done=true

    # if the guess is less than the answer, check the right half of the tree
    #   on the next iteration
    elif [ ${guess} -lt ${answer} ];
    then
        echo "higher"

    # otherwise check the left half
    else
        echo "lower"
    fi #if/elif/else
} #checkGuess

################################################################################
## cheat -      intentionally provides the wrong answer to the player
##
## @param $1    values guessed by the player
## @echoes      "correct" - if the player guessed correctly
##              "higher" - if the player's guess was too high
##              "lower" - if the player's guess was too low
## @sets        $done to true if the player guessed correctly
################################################################################
cheat(){
    guess=$1
    # if the guess equals the answer, the player wins!
    if [ ${guess} -eq ${answer} ];
    then
        echo "correct"
        done=true

    # if the guess is more than the answer, lie and tell the player to guess
    # higher
    elif [ ${guess} -gt ${answer} ];
    then
        echo "higher"

    # otherwise lie and tell the player to guess lower
    else
        echo "lower"
    fi #if/elif/else
} #cheat

################################################################################
## main program
################################################################################
#parse command line arguments
parseOps $@

#generate a value for the player to guess
generateValue ${s_flag}

#set the exit check to false
done=false

#respond to player input
while read guess
do
    #check if the dealer is supposed to cheat, then provide player feedback
    if [ ${c_flag} = true ];
    then
        cheat ${guess}
    else
        checkGuess ${guess}
    fi #if/else

    #check if the player has guessed correctly and exit if they have
    if [ ${done} = true ]; 
    then
        break
    fi #if
done #while
exit 0