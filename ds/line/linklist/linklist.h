#ifndef _LINKLIST_H
#define _LINKLIST_H

#include <stdio.h>
#include <stdlib.h>

typedef int datatype;

typedef struct node {
    datatype data;
    struct node * next;
}listnode, *linklist;

linklist list_create();
linklist list_create1();
int list_head_insert(linklist H, datatype value);
int list_insert(linklist H,int pos, datatype value);
int list_order_insert(linklist H, datatype value);
int list_delete(linklist H, int pos);
linklist list_get(linklist H, int pos);
linklist list_locate(linklist H, datatype value);
void list_reverse(linklist H);
void list_sort(linklist H);
void list_show(linklist H);

#endif

