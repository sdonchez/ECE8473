////////////////////////////////////////////////////////////////////////////////
// S. Donchez
// ECE 8473-DL1
// p2.c - Extended Grep
// Start with a copy of your program from part 1 and enhance it to accept 
// command-line options according to the following synopsis:
// ./p2 [-1] [-E|-F] [-v] pattern
// Options:
// -1 stop after first match
// -E pattern is an extended regular expression
// -F pattern is a fixed string
// -v print lines which do not contain the pattern
// Note that the - E and -F options are mutually exclusive.
// For the - E option, include REG_EXTENDED in the regcomp flags.
// For the - F option, use strstr() instead of the regular expression matching 
// functions.
// Test using test2.sh.
////////////////////////////////////////////////////////////////////////////////

#define _POSIX_C_SOURCE 200809L //for POSIX-compliant getopt, OK per R.Perry

#include <regex.h>  //for regex handling
#include <stdio.h> //for streams
#include <stdbool.h> //for bool in usage, doMatch
#include <unistd.h> //for option parsing
#include <string.h> //for strstr

//From man regex(3)
#define ARRAY_SIZE(arr) (sizeof((arr)) / sizeof((arr)[0]))

regex_t regex;
char stringToMatch[BUFSIZ];
bool singleMatch = false;
bool fixedString = false;
bool invert = false;
int flags = REG_NEWLINE | REG_NOSUB;

int parseOpts(int argc, char* argv[]);

int parsePattern(int argc, char* argv[], int optind);

int doMatch();

void parseRegexError(int err);

void usage(bool toErr);

int main(int argc, char* argv[])
{
	int currentOpt;
	// confirm pattern is present, compile it
	if ((currentOpt = parseOpts(argc, argv)) < 0)
	{
		return -1;
	} // if
	if (parsePattern(argc, argv, currentOpt))
	{
		return 2;
	}
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
 * @return  current option index (which should point to the pattern)
 ******************************************************************************/
int parseOpts(int argc, char* argv[])
{
	int option = 0;
	while ((option = getopt(argc, argv, "1EFv")) != -1)
	{
		switch (option) {
		case '1':
			singleMatch = true;
			break;
		case 'E':

			// check for mutually exclusive option -F
			if (fixedString)
			{
				fprintf(stderr, "Mutually exclusive options -E, -F passed!\n");
				return -1;
			}
			flags |= REG_EXTENDED;
			break;
		case 'F':

			//check for mutually exclusive option -E
			if (flags & REG_EXTENDED)
			{
				fprintf(stderr, "Mutually exclusive options -E, -F passed!\n");
				return -1;
			}
			fixedString = true;
			break;
		case 'v':
			invert = true;
			break;
		default:

			//if we get any other input, print the usage instructions and exit
			usage(true);
			return -2;
		} // switch
	} // while
	return optind;
} // parseOpts

int parsePattern(int argc, char* argv[], int optind)
{
	if (optind == argc)
	{
		fprintf(stderr, "Error: Too few arguments provided.");
		usage(true);
		return -1;
	} // if
	else if (optind < argc - 1)
	{
		fprintf(stderr, "Error: Too many arguments provided.");
		usage(true);
		return -1;
	} // else
	else if (!fixedString)
	{
		int err = regcomp(&regex, argv[optind], flags);
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
	} // else if
	else
	{
		strcpy(stringToMatch, argv[optind]);
		return 0;
	} // else
} // parsePattern

/*******************************************************************************
 * @brief performs the matching operation on each line of stdin, printing the
 * match if one exists. Runs until EOF.
 * @return true if no match is found.
 * @return false if a match is found.
 ******************************************************************************/
int doMatch()
{
	bool notFound = true;
	char inputLine[BUFSIZ] = "";
	regmatch_t matches[1];
	int match = 0;
	bool result = true;

	// start reading stdin
	while (fgets(inputLine, BUFSIZ, stdin))
	{
		if (fixedString)
		{
			match = (strstr(inputLine, stringToMatch) != NULL);
		}
		else
		{
			match = !regexec(&regex, inputLine, ARRAY_SIZE(matches), 
				matches, 0);
		}
		// if a match is found (and we are looking for matches), print it
		if (match && !invert)
		{
			notFound = false;
			if (!invert)
			{
				printf("%s", inputLine);
			} // if

		} // if
		// if a non-match is found and we are looking for non-matches, print it.
		else if (!match && invert)
		{
			notFound = false;
			printf("%s", inputLine);
		} // else if

		// if we've already found at least one of what we're looking for, don't
		// change the result value
		result &= notFound;

		//if we are only looking for one result and we have it, stop looking.
		if (singleMatch)
		{
			if (!result)
			{
				break;
			} // if
		} // if

	} // while
	return result;
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
		"Usage: './p2 [-1] [-E|-F] [-v] pattern' \n"
		"where pattern is a valid Regex Expression \n"
		"Options:\n"
		"-1 stop after first match\n"
		"-E pattern is an extended regular expression\n"
		"-F pattern is a fixed string\n"
		"-v print lines which do not contain the pattern\n"
		"Note that the - E and -F options are mutually exclusive.\n"
	);
} // usage