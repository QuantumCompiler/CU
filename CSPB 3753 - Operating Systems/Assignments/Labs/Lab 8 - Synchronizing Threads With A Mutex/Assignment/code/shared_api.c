// starter code for creating an API to a shared resource
// Add your comments and documentation, also make sure the code 
// uses only one formatting style
//
// Author: You
// Date: this semester
//
// Usage:
//      shared_api <filename> ... 
//
///////////////////////////////////////////////////////////////////////////////
#include <shared_api.h>


////////////////////////////////////////////////////////////////////////////////
// This is an API to a shared data structure. It must handle overlapped usage
// by multiple threads.  Data for the list of files should be dynamically 
// allocated to accommodate the list of files given in Initialize().  You will 
// need to keep track of an open file and return the next line from that file.
// If you have reached the end of the file, close the current file and open the 
// next file in the list and return a line from that file.  Continue until all
// lines from all files have been returned.  Return NULL if no more lines.
// Release all the memory allocated to support the shared resource and make
// sure there are not memory leaks (use valgrind).
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// Add your comments and documentation
//
// Must implement the following API routines.  You may create helper functions, 
// but keep them hidden (static) only described in the API code not the header.
////////////////////////////////////////////////////////////////////////////////

int Initialize(char ** filename_list, int n_filenames);

char *GetNextLine();

int Terminate();

