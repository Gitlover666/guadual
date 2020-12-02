#ifndef _LINKSTACK_H
#define _LINKSTACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "btree.h"

typedef btree_pnode datatype1;

typedef struct node
{
    datatype1 data;
    struct node *next;
} listnode, *linklist;

linklist linkstack_create();
int linkstack_empty(linklist s);
int linkstack_push(linklist s, datatype1 data);
datatype1 linkstack_pop(linklist s);
datatype1 linkstack_top(linklist s);
void linkstack_clear(linklist s);
void linkstack_free(linklist s);

#endif