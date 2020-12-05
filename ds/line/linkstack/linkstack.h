#ifndef _LINKSTACK_H
#define _LINKSTACK_H

#include <stdio.h>
#include <stdlib.h>

typedef int datatype;

typedef struct node {
    datatype data;
    struct node *next;
}listnode, *linklist;

linklist linkstack_create();
int linkstack_empty(linklist s);
int linkstack_push(linklist s, datatype data);
datatype linkstack_pop(linklist s);
datatype linkstack_top(linklist s);
void linkstack_clear(linklist s);
void linkstack_free(linklist s);



#endif