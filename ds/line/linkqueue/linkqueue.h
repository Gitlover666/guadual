#ifndef _LINKQUEUE_H
#define _LINKQUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int datatype;
#define MAXSIZE 10

typedef struct linkqueuenode
{
    datatype data;
    struct linkqueuenode *next;
}linkqueue_node, *linkqueue_pnode;

typedef struct linkqueue
{
    linkqueue_pnode front, rear;
} link_queue, *link_pqueue;

link_pqueue init_linkqueue(void);
bool in_linkqueue(datatype data, link_pqueue q);
bool is_empty_linkqueue(link_pqueue q);
bool out_linkqueue(link_pqueue q);
void show_linkqueue(link_pqueue q);

#endif