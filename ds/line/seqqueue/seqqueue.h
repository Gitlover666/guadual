#ifndef _SEQQUEUE_H
#define _SEQUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int datatype;
#define MAXSIZE 10

typedef struct seqqueue{
    datatype data[MAXSIZE];
    int front, rear;
}seq_queue, *seq_pqueue;

seq_pqueue init_seqqueue(void);
bool is_full_seqqueue(seq_pqueue q);
bool in_seqqueue(datatype data, seq_pqueue q);
bool is_empty_seqqueue(seq_pqueue q);
bool out_seqqueue(seq_pqueue q);
void show_seqqueue(seq_pqueue q);

#endif 