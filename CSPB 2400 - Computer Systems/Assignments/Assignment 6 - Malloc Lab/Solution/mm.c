/* 
 * mm-implicit.c -  Simple allocator based on implicit free lists, 
 *                  first fit placement, and boundary tag coalescing. 
 *
 * Each block has header and footer of the form:
 * 
 *      31                     3  2  1  0 
 *      -----------------------------------
 *     | s  s  s  s  ... s  s  s  0  0  a/f
 *      ----------------------------------- 
 * 
 * where s are the meaningful size bits and a/f is set 
 * iff the block is allocated. The list has the following form:
 *
 * begin                                                          end
 * heap                                                           heap  
 *  -----------------------------------------------------------------   
 * |  pad   | hdr(8:a) | ftr(8:a) | zero or more usr blks | hdr(8:a) |
 *  -----------------------------------------------------------------
 *          |       prologue      |                       | epilogue |
 *          |         block       |                       | block    |
 *
 * The allocated prologue and epilogue blocks are overhead that
 * eliminate edge conditions during coalescing.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <memory.h>
#include "mm.h"
#include "memlib.h"

/*********************************************************
 * NOTE TO STUDENTS: Before you do anything else, please
 * provide your team information in the following struct.
 ********************************************************/
team_t team = {
  /* Team name */
  " Quantum Compiler ",
  /* First member's full name */
  " Taylor Larrechea ",
  /* First member's email address */
  " taylor.larrechea@colorado.edu" ,
  /* Second member's full name (leave blank if none) */
  " N/A ",
  /* Second member's email address (leave blank if none) */
  " N/A "
};

/////////////////////////////////////////////////////////////////////////////
// Constants and macros
//
// These correspond to the material in Figure 9.43 of the text
// The macros have been turned into C++ inline functions to
// make debugging code easier.
//
/////////////////////////////////////////////////////////////////////////////
#define WSIZE       4       /* word size (bytes) */  
#define DSIZE       8       /* doubleword size (bytes) */
#define CHUNKSIZE  (1<<12)  /* initial heap size (bytes) */
#define OVERHEAD    8       /* overhead of header and footer (bytes) */

static inline int MAX(int x, int y) {
  return x > y ? x : y;
}

//
// Pack a size and allocated bit into a word
// We mask of the "alloc" field to insure only
// the lower bit is used
//
static inline uint32_t PACK(uint32_t size, int alloc) {
  return ((size) | (alloc & 0x1));
}

//
// Read and write a word at address p
//
static inline uint32_t GET(void *p) { return  *(uint32_t *)p; }
static inline void PUT( void *p, uint32_t val)
{
  *((uint32_t *)p) = val;
}

//
// Read the size and allocated fields from address p
//
static inline uint32_t GET_SIZE( void *p )  { 
  return GET(p) & ~0x7;
}

static inline int GET_ALLOC( void *p  ) {
  return GET(p) & 0x1;
}

//
// Given block ptr bp, compute address of its header and footer
//
static inline void *HDRP(void *bp) {

  return ( (char *)bp) - WSIZE;
}
static inline void *FTRP(void *bp) {
  return ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE);
}

//
// Given block ptr bp, compute address of next and previous blocks
//
static inline void *NEXT_BLKP(void *bp) {
  return  ((char *)(bp) + GET_SIZE(((char *)(bp) - WSIZE)));
}

static inline void* PREV_BLKP(void *bp){
  return  ((char *)(bp) - GET_SIZE(((char *)(bp) - DSIZE)));
}

/////////////////////////////////////////////////////////////////////////////
//
// Global Variables
//

static char *heap_listp;  /* pointer to first block */
static char *save_p;

//
// function prototypes for internal helper routines
//
static void *extend_heap(uint32_t words);
static void place(void *bp, uint32_t asize);
static void *find_fit(uint32_t asize);
static void *coalesce(void *bp);
static void printblock(void *bp); 
static void checkblock(void *bp);

//
// mm_init - Initialize the memory manager 
//
/* mm_init - Initializes the memory manager
  Input:
    None
  Algorithm:
    * Request a block of memory to start the heap
    * Initialize the heap with the prologue block, which includes padding, a prologue header, and a prologue footer,
      and an epilogue header which is a block of size 0 to mark the end of the heap
    * Extend the heap with a free block of CHUNKSIZE bytes
  Output:
    Returns 0 if initialization was successful, -1 otherwise
*/
int mm_init(void) {
  //
  // You need to provide this
  //
  // Initialize the heap starting point
  if ((heap_listp = mem_sbrk(4*WSIZE)) == (void *)-1) {  // Attempt to create the initial empty heap
    return -1;  // Return -1 if there was a problem extending the heap
  }
  PUT(heap_listp, 0);  // Alignment padding
  PUT(heap_listp + (1*WSIZE), PACK(DSIZE, 1));  // Prologue header
  PUT(heap_listp + (2*WSIZE), PACK(DSIZE, 1));  // Prologue footer
  PUT(heap_listp + (3*WSIZE), PACK(0, 1));  // Epilogue header
  heap_listp += (2*WSIZE);  // Move heap_listp past the prologue block for future heap operations
  // Store the pointer in a global variable for future use (if needed)
  save_p = heap_listp;
  // Extend the heap with a free block of initial size (CHUNKSIZE)
  if (extend_heap(CHUNKSIZE/WSIZE) == NULL) {  // Extend heap fails when it returns NULL
    return -1;  // Return -1 if unable to extend the heap properly
  }
  return 0;  // Return 0 if initialization was successful
}

//
// extend_heap - Extend heap with free block and return its block pointer
//
/* extend_heap - Extend the heap with a new free block
  Input:
    words - the number of words to extend the heap by
  Algorithm:
    * Calculate the number of bytes to extend the heap, rounding up if necessary to maintain alignment
    * Request additional space in the heap
    * Set the header and footer of the new free block
    * Mark the new end of the heap with an epilogue header
    * Coalesce if the previous block was free
  Output:
    Returns a pointer to the newly freed block after coalescing or NULL if the memory extension failed
*/
static void *extend_heap(uint32_t words) {
  //
  // You need to provide this
  //
  char *bp;
  size_t size;
  // Adjust block size to maintain alignment
  size = (words % 2) ? (words + 1) * WSIZE : words * WSIZE;  // Ensure the block size is aligned to double word (8-byte boundary)
  // Extend the heap by the adjusted block size
  if ((long)(bp = mem_sbrk(size)) == -1) {  // Attempt to grow the heap
    return NULL;  // Return NULL if the memory system was unable to provide more space
  }
  // Set header and footer of new free block
  PUT(HDRP(bp), PACK(size, 0));  // Free block header
  PUT(FTRP(bp), PACK(size, 0));  // Free block footer
  // New epilogue header at the end of the heap
  PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1));  // New epilogue header
  // Coalesce if the previous block was free
  return coalesce(bp);  // Coalesce the newly freed block with surrounding free blocks, if possible
}

//
// Practice problem 9.8
//
// find_fit - Find a fit for a block with asize bytes 
//
/* find_fit - Find a free block that fits the requested size using next-fit search algorithm
  Input:
    asize - the adjusted block size needed including the header and footer
  Algorithm:
    * Start searching from the position where the last allocation occurred (next-fit strategy)
    * Check each block from the start point to the end of the list for a block large enough and not allocated
    * If no suitable block is found by the end of the list, restart from the beginning of the list to the initial start point
    * Return the first block that fits the criteria
  Output:
    Returns a pointer to the block if a fitting block is found, NULL otherwise
*/
static void *find_fit(uint32_t asize) {
  //
  // You need to provide this
  //
  char *bp = save_p;  // Start from the last allocation point
  // First pass: search from the last allocation point to the end of the list
  for (save_p = bp; GET_SIZE(HDRP(save_p)) > 0; save_p = NEXT_BLKP(save_p)) {  // Traverse blocks until the end marker
    if (!GET_ALLOC(HDRP(save_p)) && (asize <= GET_SIZE(HDRP(save_p)))) {  // Check if block is free and large enough
        return save_p;  // Return the block pointer if it fits
    }
  }
  // Second pass: search from the start of the heap to the initial start point
  for (save_p = heap_listp; save_p < bp; save_p = NEXT_BLKP(save_p)) {  // Traverse from the beginning of the heap to last start
    if (!GET_ALLOC(HDRP(save_p)) && (asize <= GET_SIZE(HDRP(save_p)))) {  // Check if block is free and fits the required size
        return save_p;  // Return the block pointer if it fits
    }
  }
  return NULL;  // Return NULL if no suitable block is found (no fit)
}

// 
// mm_free - Free a block 
//
/* mm_free - Frees a block of allocated memory.
  Input:
    bp - pointer to the block to be freed
  Algorithm:
    * Retrieve the size of the block from its header
    * Mark the block as free by setting both the header and footer to reflect the size of the block without an allocation flag
    * Coalesce the newly freed block with adjacent free blocks to minimize fragmentation
  Output:
    None (void function)
*/
void mm_free(void *bp) {
  //
  // You need to provide this
  //
  size_t size = GET_SIZE(HDRP(bp));  // Retrieve the size from the block's header
  PUT(HDRP(bp), PACK(size, 0));  // Set the header to indicate that the block is free
  PUT(FTRP(bp), PACK(size, 0));  // Set the footer to match the header
  coalesce(bp);  // Merge this free block with adjacent free blocks
}

//
// coalesce - boundary tag coalescing. Return ptr to coalesced block
//
/* coalesce - Coalesce free blocks around a given block to form a larger free block.
  Input:
    bp - pointer to the block to coalesce
  Algorithm:
    * Determine the allocation status of the previous and next blocks
    * Based on the allocation status, decide whether to merge with the previous block, next block, both, or none
    * Adjust the block's header and footer as well as the adjacent headers and footers if necessary
    * Update the global pointer 'save_p' if it lies within a coalesced block
  Output:
    Returns a pointer to the beginning of the newly coalesced block
*/
static void *coalesce(void *bp) {
  //
  // You need to provide this
  //
  size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp)));  // Check if the previous block is allocated
  size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));  // Check if the next block is allocated
  size_t size = GET_SIZE(HDRP(bp));  // Get the current block size
  if (prev_alloc && next_alloc) {  // Case 1: Both previous and next blocks are allocated
    return bp;  // No coalescing needed
  }
  else if (prev_alloc && !next_alloc) {  // Case 2: Only the next block is free
    size += GET_SIZE(HDRP(NEXT_BLKP(bp)));  // Add the size of the next block to the current block
    PUT(HDRP(bp), PACK(size, 0));  // Update the header of the current block
    PUT(FTRP(bp), PACK(size, 0));  // Update the footer of the current block
  }
  else if (!prev_alloc && next_alloc) {  // Case 3: Only the previous block is free
    size += GET_SIZE(HDRP(PREV_BLKP(bp)));  // Add the size of the previous block to the current block
    PUT(FTRP(bp), PACK(size, 0));  // Update the footer of the current block
    PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));  // Update the header of the previous block
    bp = PREV_BLKP(bp);  // Move the block pointer to the beginning of the newly coalesced block
  }
  else {  // Case 4: Both previous and next blocks are free
    size += GET_SIZE(HDRP(PREV_BLKP(bp))) + GET_SIZE(FTRP(NEXT_BLKP(bp)));  // Sum up the sizes of previous, current, and next blocks
    PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));  // Update the header of the previous block
    PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));  // Update the footer of the next block
    bp = PREV_BLKP(bp);  // Update block pointer to the start of the newly coalesced block
  }
  // If the next-fit pointer falls within the coalesced block, move it to the start of the coalesced block
  if ((save_p >= (char *)bp) && (save_p < (char *)NEXT_BLKP(bp))) {
    save_p = bp;
  }
  return bp;  // Return the newly coalesced block
}

//
// mm_malloc - Allocate a block with at least size bytes of payload 
//
/* mm_malloc - Allocates a block of memory of at least 'size' bytes.
  Input:
    size - the number of bytes to allocate
  Algorithm:
    * Ignore spurious requests (size 0)
    * Adjust block size to include overhead and alignment requirements
    * Search the free list for a fit using the first-fit or next-fit strategy (find_fit function)
    * If no fit is found, extend the heap with a new free block
    * Place the requested block in the fitting spot (handled by the place function)
  Output:
    Returns a pointer to the allocated memory block or NULL if the allocation fails
*/
void *mm_malloc(uint32_t size) {
  //
  // You need to provide this
  //
  size_t asize;       // Adjusted block size to include overhead and to meet alignment requirements
  size_t extendsize;  // Amount by which to extend the heap if no fit is found
  char *bp;
  if (size == 0) {
    return NULL;  // Ignore spurious requests
  }
  // Adjust block size to include overhead and alignment
  if (size <= DSIZE) { 
    asize = 2 * DSIZE;  // Minimum block size to include overhead and alignment
  } else {
    asize = DSIZE * ((size + (DSIZE) + (DSIZE - 1)) / DSIZE);  // Align to double word (8-byte) boundary
  }
  // Search the free list for a suitable block
  if ((bp = find_fit(asize)) != NULL) {
    place(bp, asize);  // Place the requested block
    return bp;  // Return the pointer to the beginning of the allocated block
  }
  // No fit found. Get more memory and place the block
  extendsize = MAX(asize, CHUNKSIZE);  // Never extend by less than the chunk size
  if ((bp = extend_heap(extendsize / WSIZE)) == NULL) {
    return NULL;  // If unable to extend the heap, return NULL
  }
  place(bp, asize);  // Place the block at the start of the newly extended heap
  return bp;  // Return the pointer to the newly allocated block
}


//
//
// Practice problem 9.9
//
// place - Place block of asize bytes at start of free block bp 
//         and split if remainder would be at least minimum block size
//
/* place - Place a requested block in the beginning of a free block found by `find_fit`.
  Input:
    bp - pointer to the block where the allocation should occur
    asize - the adjusted block size needed, including the header and footer
  Algorithm:
    * Retrieve the current block size from the block's header
    * Decide whether to split the block based on the size difference between the current block size and the requested size
    * If splitting is possible, adjust headers and footers to reflect the allocated part and the remaining free part
    * If not, allocate the entire block
  Output:
    None (void function)
*/
static void place(void *bp, uint32_t asize) {
  size_t csize = GET_SIZE(HDRP(bp));  // Get the current block size from the header
  if ((csize - asize) >= (2*DSIZE)) {  // Check if the remaining part of the block is large enough to be split
    PUT(HDRP(bp), PACK(asize, 1));  // Set the header of the new allocated block
    PUT(FTRP(bp), PACK(asize, 1));  // Set the footer of the new allocated block
    bp = NEXT_BLKP(bp);  // Move the pointer to the beginning of the remaining free block
    PUT(HDRP(bp), PACK(csize - asize, 0));  // Set the header of the new free block
    PUT(FTRP(bp), PACK(csize - asize, 0));  // Set the footer of the new free block
  }
  else {  // Not enough space to split the block
    PUT(HDRP(bp), PACK(csize, 1));  // Allocate the entire block by setting the block as allocated
    PUT(FTRP(bp), PACK(csize, 1));  // Update the footer to match the header
  }
}

//
// mm_realloc -- implemented for you
//
void *mm_realloc(void *ptr, uint32_t size)
{
  void *newp;
  uint32_t copySize;

  newp = mm_malloc(size);
  if (newp == NULL) {
    printf("ERROR: mm_malloc failed in mm_realloc\n");
    exit(1);
  }
  copySize = GET_SIZE(HDRP(ptr));
  if (size < copySize) {
    copySize = size;
  }
  memcpy(newp, ptr, copySize);
  mm_free(ptr);
  return newp;
}

//
// mm_checkheap - Check the heap for consistency 
//
void mm_checkheap(int verbose) 
{
  //
  // This provided implementation assumes you're using the structure
  // of the sample solution in the text. If not, omit this code
  // and provide your own mm_checkheap
  //
  void *bp = heap_listp;
  
  if (verbose) {
    printf("Heap (%p):\n", heap_listp);
  }

  if ((GET_SIZE(HDRP(heap_listp)) != DSIZE) || !GET_ALLOC(HDRP(heap_listp))) {
	printf("Bad prologue header\n");
  }
  checkblock(heap_listp);

  for (bp = heap_listp; GET_SIZE(HDRP(bp)) > 0; bp = NEXT_BLKP(bp)) {
    if (verbose)  {
      printblock(bp);
    }
    checkblock(bp);
  }
     
  if (verbose) {
    printblock(bp);
  }

  if ((GET_SIZE(HDRP(bp)) != 0) || !(GET_ALLOC(HDRP(bp)))) {
    printf("Bad epilogue header\n");
  }
}

static void printblock(void *bp) 
{
  uint32_t hsize, halloc, fsize, falloc;

  hsize = GET_SIZE(HDRP(bp));
  halloc = GET_ALLOC(HDRP(bp));  
  fsize = GET_SIZE(FTRP(bp));
  falloc = GET_ALLOC(FTRP(bp));  
    
  if (hsize == 0) {
    printf("%p: EOL\n", bp);
    return;
  }

  printf("%p: header: [%d:%c] footer: [%d:%c]\n",
	 bp, 
	 (int) hsize, (halloc ? 'a' : 'f'), 
	 (int) fsize, (falloc ? 'a' : 'f')); 
}

static void checkblock(void *bp) 
{
  if ((uintptr_t)bp % 8) {
    printf("Error: %p is not doubleword aligned\n", bp);
  }
  if (GET(HDRP(bp)) != GET(FTRP(bp))) {
    printf("Error: header does not match footer\n");
  }
}

