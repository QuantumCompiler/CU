///////////////////////////////////////////////////////////////////////////////
// Author: Taylor Larrechea
// Date: 09-26-2024	
///////////////////////////////////////////////////////////////////////////////

#ifndef DEBUG_3753

// Define DEBUG_PRINT macro
#if DEBUG > 0
#define DEBUG_PRINT(fmt, ...) \
    do { \
        fprintf(stderr, "DEBUG: [%d] %s:%d:%s(): " fmt, getpid(), __FILE__, \
                __LINE__, __func__, ##__VA_ARGS__); \
    } while (0)
#else
#define DEBUG_PRINT(fmt, ...) do {} while (0)
#endif

#endif // DEBUG_3753
