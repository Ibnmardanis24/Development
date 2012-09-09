#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>

/** define function pointer types for common operations */
typedef int (*comparefn) (void *data1, void *data2); /** Compare function pointer */
typedef void (*printfn) (void *data);	/** Print function pointer */

/** Function pointer for memory allocators and deallocators */
typedef void *(*allocatorfn) (int size);
typedef void (*deallocatorfn) (void *ptr);
typedef void (*reallocatorfn) (void *ptr, int size);

int comparePtrs (void *p, void *q);
int compareInts (void *p, void *q);
int compareChars (void *p, void *q);

void swapInt(int *p, int *q);
void swapChar(char *p, char *q);
void swapPtr(void **p, void **q);

void printAsInt(void *object);
void printAsUInt(void *object);
void printAsLong(void *object);
void printAsULong(void *object);
void printAsChar(void *object);
void printAsString(void *object);
void printPtr(void *object);

void printNL(void);
void printSPC(void);
void printTAB(void);


/** Rudimentary memory allocator/deallocator */
extern int mem_blocks_counter;
void *allocator (int size);
void deallocator(void *ptr);
#endif

