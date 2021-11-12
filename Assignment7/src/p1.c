////////////////////////////////////////////////////////////////////////////////
// S. Donchez
// ECE 8473-DL1
// p1.c - Basic Grep
//  Write a program, similar to grep, using regcomp() and regexec() to search 
// for a regular expression pattern in lines read from standard input using 
// fgets().
// 
// Program synopsis:
// ./p1 pattern
// Simple search for regular expression pattern in lines from standard input.
// Exit status:
// 0  One or more matches were found
// 1  No matches were found
// 2  Syntax error in pattern
// Use regcomp flags : REG_NEWLINE | REG_NOSUB
// Test using test1.sh.
////////////////////////////////////////////////////////////////////////////////

#include <regex.h>  //for regex handling
#include <stdio.h> //for streams
#include <stdbool.h> //for bool in usage, doMatch

//From man regex(3)
#define ARRAY_SIZE(arr) (sizeof((arr)) / sizeof((arr)[0]))

regex_t regex;

int parseArgs(int argc, char* argv[]);

int doMatch();

void parseRegexError(int err);

void usage(bool toErr);

int main(int argc, char* argv[])
{
	// confirm pattern is present, compile it
	if (parseArgs(argc, argv))
	{
		return 2;
	} // if

	// read from stdin and perform matching operations
	if (doMatch())
	{
#ifdef _DEBUG
		fprintf(stderr, "No matches found in input for pattern %s\n", argv[1]);
#endif
		return 1;
	} // if
	else
	{
#ifdef _DEBUG
		fprintf(stderr, "Matches found in input for pattern %s\n", argv[1]);
#endif
		return 0;
	} // else

} // main


/*******************************************************************************
 * @brief checks the number of arguments passed, and, provided there are exactly
 * two, compiles the second one as a regex pattern.
 * @param argc - the number of arguments passed into the program
 * @param argv - the array of arguments passed into the program
 * @return -1 if an invalid number of arguments is provided
 * @return  1 if an invalid regex expression is passed
 * @return  0 otherwise
 ******************************************************************************/
int parseArgs(int argc, char* argv[])
{
	if (argc < 2)
	{
		fprintf(stderr, "Error: Too few arguments provided.");
		usage(true);
		return -1;
	} // if
	else if(argc > 2)
	{
		fprintf(stderr, "Error: Too many arguments provided.");
		usage(true);
		return -1;
	} // else
	else
	{
		int flags = REG_NEWLINE | REG_NOSUB;
		int err = regcomp(&regex, argv[1], flags);
		if (err)
		{
			parseRegexError(err);
			return 1;
		} // if
#ifdef _DEBUG
		fprintf(stderr, 
			"Regex expression parsed, enter input to be evaluated: \n");
#endif
		return 0;
	} // else
} // parseArgs

/*******************************************************************************
 * @brief performs the matching operation on each line of stdin, printing the
 * match if one exists. Runs until EOF.
 * @return true if no match is found.
 * @return false if a match is found.
 ******************************************************************************/
int doMatch()
{
	bool noMatch = true;
	char inputLine[BUFSIZ] = "";
	regmatch_t matches[1];

	// start reading stdin
	while (fgets(inputLine, BUFSIZ, stdin))
	{
		// if a match is found, print it
		if (!regexec(&regex, inputLine, ARRAY_SIZE(matches), matches, 0))
		{
			noMatch = false;
			printf("%s", inputLine);
		} // if
	} // while
	return noMatch;
} // doMatch

/*******************************************************************************
 * @brief parses and prints an error from the integer output of one of the
 * regex.h functions. 
 * @param err - the error value returned by the regex.h function.
 ******************************************************************************/
void parseRegexError(int err)
{
	char errString[BUFSIZ] = "";
	regerror(err, &regex, errString, BUFSIZ);
	fprintf(stderr, "%s", errString);
} // parseRegexError

/*******************************************************************************
 * @brief prints out the usage instructions for the program, either to stdout or
 * stderr depending on the use case.
 * @param toErr - indicates if the usage instructions should be printed to
 * stdErr.
 ******************************************************************************/
void usage(bool toErr)
{
	FILE* out = toErr ? stderr : stdout;
	fprintf(out,
		"Usage: './p1 pattern', where pattern is a valid Regex Expression");
} // usage