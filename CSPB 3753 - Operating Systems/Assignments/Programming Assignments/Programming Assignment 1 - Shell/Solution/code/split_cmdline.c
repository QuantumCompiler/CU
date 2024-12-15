///////////////////////////////////////////////////////////////////////////////
// Author: Taylor Larrechea
// Date: 09-26-2024
///////////////////////////////////////////////////////////////////////////////

/*
	This file contains the functions to split the command line input into tokens.
*/

// Includes

#include "split_cmdline.h"

/*  split_cli - Splits the input command line into tokens
        Input:
            cmdline - Input command string from the CLI.
            delim - Delimiter used to split the string into tokens (e.g., " " or "|").
        Algorithm:
            * Check if the command line input is NULL, return NULL if so.
            * Allocate memory for the tokens array.
                * If allocation fails, free the command line and return NULL.
            * Use strtok_r to split the command by the delimiter.
                * For quoted strings, skip over spaces inside quotes.
                * Reallocate tokens array dynamically if more space is needed.
            * Null-terminate the tokens array.
        Output:
            Returns an array of tokens split by the provided delimiter.
*/
char **split_cli(char *cmdline, char *delim) {
    // Initialize the number of arguments
    int n_arg = 0;
#if DEBUG > 0
    DEBUG_PRINT("Splitting command line:\n");
#endif
    // If the input is NULL, return NULL
    if (cmdline == NULL) {
        perror("Error reading command line.\n");
        return NULL;
    }
#if DEBUG > 0
    DEBUG_PRINT("[%s]\n", cmdline);
#endif
    // Allocate memory for the tokens array
    int max_arg = 100;
    char **tokens = malloc(sizeof(char*) * max_arg);
    if (tokens == NULL) {
        perror("Memory allocation failed\n");
        free(cmdline);
        return NULL;
    }
    // Use strtok_r to split the command line into tokens
    char *save_ptr;
    char *token = strtok_r(cmdline, delim, &save_ptr);
    while (token != NULL) {
        if (DEBUG > 0) {
            printf("token[%s], saved ptr[%s]\n", token, save_ptr);
        }
        // Handle quoted strings
        if ((*token == '\'') || (*token == '"')) {
            char quote_char = token[0];  // Get the quote character
            token++;  // Skip the opening quote
            char *closing_quote = strchr(token, quote_char);
            while (closing_quote == NULL) {
                save_ptr[-1] = ' ';  // Concatenate the next token
                char *next_token = strtok_r(NULL, delim, &save_ptr);
                if (DEBUG > 0) {
                    printf("token[%s], saved ptr[%s]\n", token, save_ptr);
                }
                if (next_token == NULL) {
                    DEBUG_PRINT("*** ERROR - no closing quote\n");
                    free(tokens);
                    free(cmdline);
                    return NULL;
                }
                closing_quote = strchr(token, quote_char);  // Find the closing quote
            }
            *closing_quote = '\0';  // Remove the closing quote
            DEBUG_PRINT("Quoted string: [%s]\n", token);
        }
        // Add the token to the tokens array
        tokens[n_arg++] = token;
        // Reallocate if the tokens array exceeds its current size
        if (n_arg >= max_arg) {
            max_arg += 10;
            char **new_tokens = realloc(tokens, sizeof(char*) * max_arg);
            if (new_tokens == NULL) {
                perror("Memory reallocation failed\n");
                free(tokens);
                free(cmdline);
                return NULL;
            } else {
                tokens = new_tokens;
            }
        }
        // Get the next token
        token = strtok_r(NULL, delim, &save_ptr);
    }
    // Null-terminate the tokens array
    tokens[n_arg] = NULL;
#if DEBUG > 0
    DEBUG_PRINT(" %d tokens\n", n_arg);
#endif
    return tokens;
}