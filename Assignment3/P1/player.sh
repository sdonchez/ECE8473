################################################################################
## S.Donchez
## a3/player.sh -   Write separate shell scripts which can be run interactively 
##                  for the dealer and player parts of the random number 
##                  guessing game from the previous assignment.
##
##                  The player must take an optional command-line argument -d 
##                  which causes it to display copies of its guesses and dealer 
##                  responses to stderr, i.e. echo "something..." 1>&2
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
##                  Let the player take an optional command-line argument -c to 
##                  turn on player "cheat" mode, so the player's first guess is 
##                  always correct.
################################################################################

################################################################################
## parseOps - parses options passed into program and sets flags accordingly
##
## @param   $@ - all parameters passed to function, to be looped through
## @sets    $c_flag - if the param "-c" was passed.
## @sets    $d_flag - if the param "-d" was passed.
## @note    also supports multiple params passed with a single - (i.e. -cd)
################################################################################
parseOps(){
    #set flags to false by default, then check if they are passed in
    c_flag=false
    d_flag=false
    for var in $@
    do
        if [ "$var" = "-c" ];
        then
            c_flag=true
        elif [ "$var" = "-d" ];
        then
            d_flag=true

        #allow concatenated params per the POSIX convention    
        elif [ "$var" = "-cd" ] || [ "$var" = "-dc" ];
        then
            c_flag=true
            d_flag=true
        fi #if/elif/elif
    done #for
} #parseOps

################################################################################
## setup      - configures initial values for variables used to determine 
##              guesses
##
## @param $1 -  boolean that indicates if the player should cheat
## @sets        $high to 101 (1 more than the maximum guess)    
## @sets        $low to 0 (1 less than the minimum guess)
## @sets        #range to the difference between $low and $high
## @sets        guess to the output of the awk command if $1 is true
################################################################################  
setup(){
    low=0
    high=101
    range=$((high - low))
    if [ "$1" = true ];
    then
        guess=$(echo hi | awk '{ srand(); print int(1+100*rand()); }')
    fi #if
} #setup

################################################################################
## makeGuess -  constructs a guess based on the current range values
## 
## @param $1 -  boolean that indicates if the player is cheating
## @param $2 -  boolean that indicates if the player should print debug output
## @sets        $c_flag to false if it was previously true
## @sets        $guess to the middle of the current range, provided the player
##              isn't making a first guess while cheating
## @echoes      the value of $guess, with no context, to stdout
## @echoes      the value of $guess, with context, to stderr if $2 is true
################################################################################
makeGuess(){

    #check if we are cheating
    if [ $1 = true ];
    then
        #if we are cheating
        #guess is already set by setup, just clear the flag so we make a real 
        #guess next time, just in case the dealer is in secure mode
        #newer versions of bash have a pass by reference that would be great
        #here, but it isn't POSIX compliant
        c_flag=false
    else
        #if we aren't cheating, guess the middle of the range
        guess=$(((${low} + ${high})/2))
    fi #if/else

    #echo the guess out to stdout for the pipe
    echo "${guess}"

    #if the d flag is set, echo the guess out to stderr for debugging
    if [ $2 = true ];
    then
        echo "guess = ${guess}" >&2
    fi #if
} #makeGuess

################################################################################
## parseReponse -   parses the dealer's response to the player's guess
##
## @param $1 -      the string containing the dealer's response
## @param $2 -      boolean indicating if the player is in debug mode
## @sets            $high to the current guess if the dealer indicates the guess
##                  is too high
## @sets            $low to the current guess if the dealer indicates the guess
##                  is too low
## @returns         0 if the player guesses correctly
################################################################################
parseResponse()
{
    echo "Response:" $1
    # check the dealer output
    if [ "$1" = "higher" ];
    then
        low=${guess}
    elif [ "$1" = "lower" ];
    then
        high=${guess}

    # or exit if we guessed right
    elif [ "$1" = "correct" ]
    then

        #if in debug mode, print output
        if [ "$2" = true ];
        then
            echo "Correct!" >&2
        fi #if
        exit 0
    else
         echo "invalid input, please state 'higher', 'lower', or 'correct'" >&2
    fi # if/elif/elif/else
}
################################################################################
## Main Program
################################################################################
#parse command line arguments
parseOps $@

#initialize values
setup $c_flag

# while the dealer isn't cheating, keep playing
while [ $range -ge 2 ]
do
    #produce a guess and share it with the dealer
    makeGuess $c_flag $d_flag

    #read in and process the dealer's response
    read direction
    parseResponse $direction $d_flag

    #recalculate the range so we can ensure the dealer isn't cheating
    range=$((${high} - ${low}))
done # while

#if we break the loop without exiting, the dealer is cheating!
echo "Dealer is cheating, I quit!" >&2
exit 1