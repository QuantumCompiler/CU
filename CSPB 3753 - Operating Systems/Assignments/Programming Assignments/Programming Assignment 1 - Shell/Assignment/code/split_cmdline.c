///////////////////////////////////////////////////////////////////////////////
//  Split a command line string into tokens
///////////////////////////////////////////////////////////////////////////////
// Author:  < no credit without updated comments>
// Date:
///////////////////////////////////////////////////////////////////////////////
//
// Split the string into tokens.  The only character considered as a terminator
// is space character.  Returns an array of character pointers that is 
// dynamically allocated.
//
//      To keep things simple, we will not do any sophisticated parsing of the 
//      user’s input (e.g., no quotation matching, checks for escape characters,
//      etc..). In particular, you may assume that the user will input data in 
//      the format shown in the example below:
//          cmd_1 arg arg ... arg | ... | cmd_n arg arg ... arg &
//
///////////////////////////////////////////////////////////////////////////////

#define _GNU_SOURCE 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 0   // set this to 1 if you want help debuging this code
#include "debug_3753.h"

///////////////////////////////////////////////////////////////////////////////
// split_command_line(cmdline)
//
// Split the string into tokens.  The only character considered as a terminator
// is space character.  Returns an array of character pointers that is 
// dynamically allocated.
//
//  Parameters  : string of characters that are null byte terminated.
//  Return value: pointer to an array of pointers (null pointer terminated).
//                Caller is responsible for deallocation of token array.
//
//  Notes: - must have spaces around the pipe character and the background character
///////////////////////////////////////////////////////////////////////////////

char **split_command_line(char *cmdline) {
    int n_arg = 0;      // number of arguments added to list
	
#if DEBUG > 2
	DEBUG_PRINT("Splitting command line:");
#endif

	if (cmdline == NULL) return NULL;

#if DEBUG > 2
	DEBUG_PRINT("[%s]", cmdline);
#endif

    int max_arg = 100;   // this should be dynamic (could estimate with number of spaces)
    char **tokens = malloc(sizeof(char*)*max_arg);
    char *delim = " ";
    
    // for each token in the string
    //    save pointer to the token
    //    get the next token

    char *pch = strtok(cmdline, delim);     // initialize the tokenizer
    while (pch != NULL ) {
        tokens[n_arg++] = pch;
        pch = strtok(NULL, delim);
    }

    tokens[n_arg] = NULL;     // null terminate the list with NULL

#if DEBUG > 2
	DEBUG_PRINT(" %d tokens\n", n_arg);
#endif

    return tokens;
}


///////////////////////////////////////////////////////////////////////////////
// split_q_command_line(cmdline)
//
// Split the string into tokens.  The string is collected into space delimied 
// strings.  If a quote is encountered, it specifies that all spaces are ignored 
// as terminators until closing quote is found.  All the characters between 
// the quotes is considered one parameter. Returns an array of character pointers that is 
// dynamically allocated.
//
//  Parameters  : sequence of characters that is null byte terminated.
//  Return value: pointer to an array of pointers (null pointer terminated).
//                Caller is responsible for deallocation of token array.
//
//  Notes: - must have spaces around the pipe character and the background character
///////////////////////////////////////////////////////////////////////////////

char **split_q_command_line(char *cmdline) {
    int n_arg = 0;      // number of arguments added to list
	
#if DEBUG > 0
	DEBUG_PRINT("Splitting command line:\n");
#endif

	if (cmdline == NULL) return NULL;

#if DEBUG > 0
	DEBUG_PRINT("[%s]\n", cmdline);
#endif

    int max_arg = 100;   // this should be dynamic (could estimate with number of spaces)
    char **tokens = malloc(sizeof(char*)*max_arg);
    char *delim = " \t\n";
    
    // for each token in the string
    //    save pointer to the token
    //    get the next token

	char *save_ptr;
    char *token = strtok_r(cmdline, delim, &save_ptr);     // initialize the tokenizer
	while (token != NULL ) {
        printf("token[%s], saved ptr[%s]\n", token, save_ptr);
		if ((*token == '\'') || (*token == '"') ) {
			// Extract the quoted string (excluding the quotes)
			char quote_char = token[0];
			token++;  //remove the quote form token

			char *closing_quote = strchr(token, quote_char);  // find matching char
			while (closing_quote == NULL) {
				// If the closing quote is not found in this token,
				// concatenate the next token and continue searching
				save_ptr[-1] = ' ';  // concat the next_token on to token
				char *next_token = strtok_r(NULL, delim, &save_ptr);
				printf("token[%s], saved ptr[%s]\n", token, save_ptr); 
 				if (next_token == NULL) {
					DEBUG_PRINT("*** ERROR - no closing quote\n");
					return NULL;
				}

				closing_quote = strchr(token, quote_char);
			}

			*closing_quote = '\0';  // Remove the closing quote
			DEBUG_PRINT("Quoted string: [%s]\n", token);		
		}
		tokens[n_arg++] = token;
		token = strtok_r(NULL, delim, &save_ptr);
	}

	tokens[n_arg] = NULL;     // null terminate the list with NULL

	#if DEBUG > 0
		DEBUG_PRINT(" %d tokens\n", n_arg);
	#endif

	return tokens;
}

