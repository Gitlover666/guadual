#ifndef _ALINKLIST_H
#define _ALINKLIST_H

#include <stdio.h>
#include <stdlib.h>

typedef int datatype;

typedef struct node {
    datatype data;
    struct node * next;
}listnode, *linklist;

linklist Alinklist_create();
void Alinklist_show(linklist H);
void Alinklist_jose(linklist H, int k, int m);

#endif

