#ifndef _SQSTACK_H
#define _SQSTACK_H

#include <stdio.h>
#include <stdlib.h>

typedef int datatype;

typedef struct{
    datatype * data;
    int maxlen;
    int top;
}sqstack;

sqstack * stack_create(int len);
int stack_empty(sqstack * s);
void stack_clear(sqstack * s);
int stack_full(sqstack * s);
int stack_push(sqstack * s, datatype value);
datatype stack_pop(sqstack * s);
datatype stack_top(sqstack * s);
void stack_free(sqstack * s);



#endif 