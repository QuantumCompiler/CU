///////////////////////////////////////////////////////////////////////////////
// Author: Taylor Larrechea
// Date: 09-26-2024	
///////////////////////////////////////////////////////////////////////////////

/*
    This file contains the external libraries and constants used in the shellLab shell.

    This file should be imported in every other file in the shellLab shell pertaining to c or h files.
*/

// Libraries
#include "debug_3753.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define _GNU_SOURCE

// Constants used in code
#define DEBUG 0 // set this to 1 if you want help debugging this code
#define BUFFER_GROWTH_SIZE 16
#define TABLE_GROWTH_SIZE  8
#define COMMAND_BUFFER_GROWTH_SIZE 16
#define ARG_TABLE_GROWTH_SIZE 4
#define PIPE_SYMBOL "|"
#define BACKGROUND_SYMBOL "&"

// Special Commands to process
#define CHANGE_DIRECTORY  "cd"
#define EXIT  "done"