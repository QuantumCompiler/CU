#ifndef SPLIT_CMDLINE
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
#include <stdio.h>
#include <string.h>


// [short description of the function purpose and parameters]
char **split_command_line(char *cmdline);

#endif // SPLIT_CMDLINE
