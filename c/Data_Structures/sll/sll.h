#ifndef _SLL_H_
#define _SLL_H_

#include <sll_node.h>

#include <errno.h>

typedef struct sll_s {
	sll_node_t *head;
	sll_node_t *tail;
	int _size;
} sll_t;

/** Core operations */
void sll_init (sll_t *sll);
int sll_length (sll_t *sll);

/** Insert operations */
int sll_insert_at_front (sll_t *sll, void *data);
int sll_insert_at_end (sll_t *sll, void *data);
int sll_insert_at_position (sll_t *sll, void *data, int pos);

/** Remove operations */
void *sll_remove_at_front (sll_t *sll);
void *sll_remove_at_end (sll_t *sll);
void *sll_remove_at_position (sll_t *sll, int pos);

/** Print operations */
void sll_print (sll_t *sll, void(*printfn)(void *));

#endif // _SLL_H_
