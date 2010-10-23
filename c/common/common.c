#include <common.h>

int comparePtrs (void *p, void *q)
{
	return (p == q);
}

void swapInt(int *p, int *q)
{
	/** NOTE: if the same pointers are passed, the numbers become zero right after the first xor */
	if (p == q)
		return;

#define P *p
#define Q *q
	P = P ^ Q;
	Q = P ^ Q;	/** p ^ q ^ q = p */
	P = P ^ Q;	/** now q = prev value of p, so,  p ^ q ^ p = q */
#undef P
#undef Q
}

void swapChar(char *p, char *q)
{
	/** NOTE: if the same pointers are passed, the values become zero right after the first xor */
	if (p == q)
		return;

#define P *p
#define Q *q
	P = P ^ Q;
	Q = P ^ Q;	/** p ^ q ^ q = p */
	P = P ^ Q;	/** now q = prev value of p, so,  p ^ q ^ p = q */
#undef P
#undef Q
}

void swapPtr(void **p, void **q)
{
	/** NOTE: if the same pointers are passed, the values become zero right after the first xor */
	if (p == q)
		return;

#define P (long)*p
#define Q (long)*q
	*p = (void *)(P ^ Q);
	*q = (void *)(P ^ Q);	/** p ^ q ^ q = p */
	*p = (void *)(P ^ Q);	/** now q = prev value of p, so,  p ^ q ^ p = q */
#undef P
#undef Q
}

void printAsInt(void *object)
{
	printf("%d", (int)object);
}

void printAsUInt(void *object)
{
	printf("%u", (unsigned int)object);
}

void printAsLong(void *object)
{
	printf("%ld", (long)object);
}

void printAsULong(void *object)
{
	printf("%lu", (unsigned long)object);
}

void printAsString(void *object)
{
	printf("%s", (char *)object);
}

void printPtr(void *object)
{
	printf("%p", object);
}
